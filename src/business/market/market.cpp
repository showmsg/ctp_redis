#include "GateLinkManager.h"
#include "Inifile.h"
#include "Thread.h"
#include "Logger.h"
#include "Lib.h"
#include "Redis.h"

using namespace inifile;

IniFile g_ini;
const char* CONF_INI = "../conf/config.ini";

void shutdown(int sig)
{

}
class CApp : public Thread
{
    public:
        CApp();
        virtual ~CApp(void);
        void Init();
        void Run();
    private:
        xRedisClient _xredis;
		xRedisClient m_mainxredis;	
        string m_mrklist;
        CBaseExchApi* m_pExchApi;
        int   ismrklstfrmtrade;
        string m_MrkListStore;
		CGateLinkManager* m_LinkManager;
		LinkManager    m_linkVect;
};
CApp::CApp()
{

}

CApp::~CApp()
{   
    delete m_pExchApi;
	delete m_LinkManager;
}
void CApp::Init()
{
    //	signal(30, shutdown);
    string LogPath;	
    int iRet = 0;
    g_ini.load(CONF_INI);

    string _env    = g_ini.getStringValue(SYSTEM_SECTION, "env", iRet);
    LogPath        = g_ini.getStringValue(SYSTEM_SECTION, "market_log_path", iRet);
    if(iRet != RET_OK)
    {
        LogPath = "Syslog_@@.log";
    }

    Lib::replace(LogPath, ENVNO_REPLACE_FLAG, _env);

    SET_LOG_NAME(LogPath);
    //设置日志级别
    SET_LOG_LEVEL(LOG_LEVEL_TRACE);

    //设置日志大小
    SET_LOG_SIZE(10 * 1024 * 1024);

    //设置占用磁盘空间大小
    SET_LOG_SPACE(100 * 1024 * 1024);

    LOG_INFO("####################################################################");
    LOG_INFO("#                         V1.0.0                                   #");
    LOG_INFO("####################################################################\n");
	
	int _tradenums        = g_ini.getIntValue(TRADE_SECTION, "trader_numbers", iRet);
	if(_tradenums < 1)
	{
		LOG_ERROR("Not config trader");
		exit(-1);
	}	
		
    string _tick          = g_ini.getStringValue(TRADE_SECTION, "channel_tick", iRet);
    string _channel       = g_ini.getStringValue(TRADE_SECTION, "channel_market", iRet);
    string _snapshot      = g_ini.getStringValue(TRADE_SECTION, "channel_snapshot", iRet);	
    string _mrktlist      = g_ini.getStringValue(TRADE_SECTION, "channel_marketlist", iRet);
    int _isTick           = g_ini.getIntValue(TRADE_SECTION, "channel_tick_open", iRet);
    ismrklstfrmtrade      = g_ini.getIntValue(TRADE_SECTION, "channel_marketlist_from_trade", iRet);
    m_MrkListStore        = g_ini.getStringValue(TRADE_SECTION, "market_list_path", iRet);
    Lib::replace(m_MrkListStore, ENVNO_REPLACE_FLAG, _env);
	
	//从文件中取出订阅行情列表,移除，从本地获得列表
    m_mrklist = _env + _mrktlist;
	
    LOG_INFO("#Channel# tick:[%s], snapshort:[%s], market_list:[%s]", _tick.c_str(), _snapshot.c_str(), 
            _mrktlist.c_str());
	
	int iredis_cnt       = g_ini.getIntValue(REDIS_SECTION, "rds_count", iRet);
	if(iredis_cnt < 1)
	{
		LOG_ERROR("Not config redis");
		exit(-1);
	}
	RedisNode RedisList[iredis_cnt];
	for(int j = 1; j <= iredis_cnt; j++)
	{
		int _index            = g_ini.getIntValue(REDIS_SECTION, Lib::cati("rds_index_", j), iRet); 		
		string _redishost     = g_ini.getStringValue(REDIS_SECTION, Lib::cati("rds_host_", j), iRet);
		int _port             = g_ini.getIntValue(REDIS_SECTION, Lib::cati("rds_port_", j), iRet);
		string _redispasswd   = g_ini.getStringValue(REDIS_SECTION, Lib::cati("rds_password_", j), iRet);
		int _poolsize         = g_ini.getIntValue(REDIS_SECTION, Lib::cati("rds_poolsize_", j), iRet);
		int _pooltimeout      = g_ini.getIntValue(REDIS_SECTION, Lib::cati("rds_pooltimeout_", j), iRet);
		int _isslave          = g_ini.getIntValue(REDIS_SECTION, Lib::cati("is_redis_slave_", j), iRet);
		
		LOG_INFO("#Redis# rds_host:%s, rds_port:%d, rds_pwd:%s, rds_db:%d", _redishost.c_str(), _port, _redispasswd.c_str(),
            _index);
			
		RedisList[j-1].dbindex = _index;
		RedisList[j-1].port = _port;
		RedisList[j-1].poolsize = _poolsize;
		RedisList[j-1].timeout = _pooltimeout;
		RedisList[j-1].role = _isslave;
		strncpy(RedisList[j-1].host, _redishost.c_str(), REDIS_HOST_LEN);
		strncpy(RedisList[j-1].passwd, _redispasswd.c_str(), REDIS_PWD_LEN);
	}
	
	_xredis.Init(iredis_cnt);	
	
	LOOP_CONNECT_REDIS:
    if(!_xredis.ConnectRedisCache(RedisList, iredis_cnt, CACHE_TYPE_1))
	{
		LOG_ERROR("connect redis error");
		#ifdef WIN32
		 Sleep(1000);
		#else
				 usleep(100);
		#endif
		goto LOOP_CONNECT_REDIS;
	}
	
	/*
	LOOP_CONNECT_MAIN:
	m_mainxredis.Init(iredis_cnt);	
	if(!m_mainxredis.ConnectRedisCache(RedisList, iredis_cnt, CACHE_TYPE_2))
	{
		LOG_ERROR("connect redis error");
		#ifdef WIN32
		 Sleep(1000);
		#else
				 usleep(100);
		#endif
		goto LOOP_CONNECT_MAIN;
	}
	*/
    //注册订阅行情回调		
    MdRedis mdredis;
    mdredis.xredis         = &_xredis;    
    mdredis.Env            = _env;
    mdredis.Channel        = _env + _channel;
    mdredis.Snapshot       = _env + _snapshot;
    mdredis.Tick           = _env + _tick;
    mdredis.MrktList       = _env + _mrktlist;
    mdredis.isTick         = _isTick;
    mdredis.MrktListStore  = m_MrkListStore;
	
	
	string _flowpath      = g_ini.getStringValue(TRADE_SECTION, "flow_path", iRet);	
	LOG_INFO("TradeNums:%d", _tradenums);
	for(int i = 1; i <= _tradenums; i++)
	{
		string _mrkaddress    = g_ini.getStringValue(TRADE_SECTION, Lib::cati("market_front_", i), iRet);
		string _brokerid      = g_ini.getStringValue(TRADE_SECTION, Lib::cati("trade_broker_id_", i), iRet);
		string _userid        = g_ini.getStringValue(TRADE_SECTION, Lib::cati("trade_user_id_", i), iRet);
		string _password      = g_ini.getStringValue(TRADE_SECTION, Lib::cati("trade_password_", i), iRet);
		string _group         = g_ini.getStringValue(TRADE_SECTION, Lib::cati("market_group_", i), iRet);
		
		LOG_INFO("[%d]Broker:%s,UserID:%s,Password:%s,Address:%s, flowpath:%s", i, _brokerid.c_str(), _userid.c_str()
				, _password.c_str(), _mrkaddress.c_str(), _flowpath.c_str());
		
		ApiExchLink mdlink;

		mdlink.BrokerID = _brokerid;
		mdlink.UserID   = _userid;
		mdlink.Password = _password;
		mdlink.Address  = _mrkaddress;
		mdlink.FlowPath = _flowpath;
		mdlink.MrktList = _env + _mrktlist;
		mdlink.MrktGroup= _group;
		mdlink.isTrade  = 0;
		m_linkVect.push_back(mdlink);
	}
    
    m_LinkManager = new CGateLinkManager();
	m_LinkManager->Init(m_linkVect);
    
    
	m_LinkManager->StartMarket(&mdredis);
    
    LOG_INFO("===============================================================\n");

}

void CApp::Run()
{
    while(true)
    {
        if(!ismrklstfrmtrade)
        {
            usleep(1000);
            continue;
        }
 
		RedisDBIdx dbi(&_xredis);
		VALUES vVal;    
		bool bRet = dbi.CreateDBIndex(m_mrklist.c_str(), APHash, CACHE_TYPE_1);
        if(bRet)
        {
			ArrayReply Reply;
            int64_t count = 0;
            if (!_xredis.llen(dbi, m_mrklist, count)) {
                LOG_ERROR("[%s] %s error %s",m_mrklist.c_str(), __PRETTY_FUNCTION__, dbi.GetErrInfo());
            }
            if(count == 0)
            {
//				usleep(10000);
                continue;
            }
			
			if (_xredis.lrange(dbi, m_mrklist, 0, count, Reply)) 
            {   
                ReplyData::iterator iter = Reply.begin();
                for (; iter != Reply.end(); iter++) 
                {
					vector<string> instruments = Lib::split((*iter).str, SPLIT_FLAG);
					int cnt = instruments.size();
					if(cnt < 1)
					{
						return ;
					}
					LOG_INFO("订阅行情列表: %s", m_mrklist.c_str());
					char ** Instrumnet;
					Instrumnet = (char**)malloc((sizeof(char*)) * cnt);
					for (int i = 0; i < cnt; i++) 
					{
						char * tmp = Lib::stoc(instruments[i]);
						LOG_INFO("instrumentID:%s", tmp);
						Instrumnet[i] = tmp;
					}
					m_pExchApi = m_LinkManager->GetMarket("CTP");
					if(NULL != m_pExchApi)
					{
						m_pExchApi->SubMarketData(Instrumnet, cnt);

						m_pExchApi->StoreQuot(m_MrkListStore);
					}            
					
					free(Instrumnet);
				}
			}
			
			if(!_xredis.ltrim(dbi, m_mrklist, count, -1))
            {
                LOG_ERROR("%s error %s", __PRETTY_FUNCTION__, dbi.GetErrInfo());
            }
			
        }
    }
}

int main(int argc, char const *argv[])
{
    CApp app;
    app.Init();
    app.Start();
    app.Join();

    return 0;
}
