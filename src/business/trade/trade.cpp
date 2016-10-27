#include "Logger.h"
#include "Inifile.h"
#include "GateLinkManager.h"
#include <unistd.h>
#include "Thread.h"
#include "Lib.h"

using namespace inifile;


const char* CONF_INI = "../conf/config.ini";

class CApp : public Thread
{
    public:
        CApp();
        virtual ~CApp(void);
        void Init();
        void Run();
    private:
        CBaseExchApi* m_pExchApi;
        xRedisClient _xredis;	
        IniFile g_ini;
        string clientReq;
        int m_iReqNo;
        TdRedis tdredis;
		CGateLinkManager* m_LinkManager;
		LinkManager    m_linkVect;
}; 

CApp::CApp()
{
    m_iReqNo = 1;
}

CApp::~CApp()
{
    delete m_pExchApi;
	delete m_LinkManager;

}
void CApp::Init()
{
    string LogPath;
    string FlowPath;
    int iRet = 0;
    g_ini.load(CONF_INI);
    string _env = g_ini.getStringValue(SYSTEM_SECTION, "env", iRet);
    LogPath = g_ini.getStringValue(SYSTEM_SECTION, "trade_log_path", iRet);
    if(iRet != RET_OK)
    {
        LogPath = "trade_@@.log";
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
	
	//=====================================================================
	string _tick           = g_ini.getStringValue(TRADE_SECTION, "channel_tick", iRet);
    string _channel        = g_ini.getStringValue(TRADE_SECTION, "channel_market", iRet);
    string _userstatus     = g_ini.getStringValue(TRADE_SECTION, "channel_user_status", iRet);

    string _rspaction      = g_ini.getStringValue(TRADE_SECTION, "channel_trade_rspaction", iRet);
    string _rspinsert      = g_ini.getStringValue(TRADE_SECTION, "channel_trade_rspinsert", iRet);
    string _rtnorder       = g_ini.getStringValue(TRADE_SECTION, "channel_trade_rtnorder", iRet);
    string _rtntrade       = g_ini.getStringValue(TRADE_SECTION, "channel_trade_rtntrade", iRet);
    string _clientposition = g_ini.getStringValue(TRADE_SECTION, "channel_user_clientposition", iRet);
    string _instruments    = g_ini.getStringValue(TRADE_SECTION, "channel_instrument", iRet);
    string _clientreq      = g_ini.getStringValue(TRADE_SECTION, "client_msg_queue", iRet);
    string _mrktlist       = g_ini.getStringValue(TRADE_SECTION, "channel_marketlist", iRet);
	
	LOG_INFO("#Channel# tick:%s, userstatus:%s, client_queue:%s", _tick.c_str(), _userstatus.c_str(), _clientreq.c_str());
    LOG_INFO("rspaction:%s, rspinsert:%s, clientposition:%s, instrument:%s", _rspaction.c_str(), _rspinsert.c_str(), 
            _clientposition.c_str(), _instruments.c_str());
    LOG_INFO("rtnorder:%s, rtntrade:%s", _rtnorder.c_str(), _rtntrade.c_str());
	//======================================================================
	string _flowpath      = g_ini.getStringValue(TRADE_SECTION, "flow_path", iRet);	
	LOG_INFO("TradeNums:%d", _tradenums);
	for(int i = 1; i <= _tradenums; i++)
	{
		string _tdaddress    = g_ini.getStringValue(TRADE_SECTION, Lib::cati("trade_front_", i), iRet);
		string _brokerid      = g_ini.getStringValue(TRADE_SECTION, Lib::cati("trade_broker_id_", i), iRet);
		string _userid        = g_ini.getStringValue(TRADE_SECTION, Lib::cati("trade_user_id_", i), iRet);
		string _password      = g_ini.getStringValue(TRADE_SECTION, Lib::cati("trade_password_", i), iRet);
		string _group         = g_ini.getStringValue(TRADE_SECTION, Lib::cati("market_group_", i), iRet);
		
		LOG_INFO("[%d]Broker:%s,UserID:%s,Password:%s,Address:%s, flowpath:%s", i, _brokerid.c_str(), _userid.c_str()
				, _password.c_str(), _tdaddress.c_str(), _flowpath.c_str());
		
		ApiExchLink mdlink;

		mdlink.BrokerID = _brokerid;
		mdlink.UserID   = _userid;
		mdlink.Password = _password;
		mdlink.Address  = _tdaddress;
		mdlink.FlowPath = _flowpath;
		mdlink.MrktList = _mrktlist + _env;
		mdlink.MrktGroup= _group;
		mdlink.isTrade  = 1;
		m_linkVect.push_back(mdlink);
	}
	
    clientReq = _clientreq + _env;

    tdredis.xredis           = &_xredis;
    tdredis.Env		           = _env;
    tdredis.Channel            = _channel;	
    tdredis.Tick               = _tick + _env;
    tdredis.UserStatus         = _userstatus + _env;
    tdredis.RspOrderInsert     = _rspinsert + _env;
    tdredis.RspOrderAction     = _rspaction + _env;
    tdredis.RtnOrder           = _rtnorder + _env;
    tdredis.RtnTrade           = _rtntrade + _env;
    tdredis.ClientPosition     = _clientposition + _env;
    tdredis.Instruments        = _instruments + _env;
    tdredis.ClientReq          = _clientreq + _env;
    tdredis.MrktList           = _mrktlist + _env;
		
	m_LinkManager = new CGateLinkManager();
	m_LinkManager->Init(m_linkVect);    
    
	m_LinkManager->StartTrade(&tdredis);
	
    LOG_INFO("CTP基础数据准备就绪，开始接单了");
    LOG_INFO("===============================================================\n");
}

void CApp::Run()
{
	//如果交易登录且查询基础信息完毕，可以进行报单
	
    const char* szHKey = clientReq.c_str();
    RedisDBIdx dbi(&_xredis);
    VALUES vVal;    
    bool bRet = dbi.CreateDBIndex(szHKey, APHash, CACHE_TYPE_1);
    while(true)
    {	
        if (bRet) {
            ArrayReply Reply;
            int64_t count = 0;
            if (!_xredis.llen(dbi, szHKey, count)) {
                LOG_ERROR("%s error %s", __PRETTY_FUNCTION__, dbi.GetErrInfo());
            }
            if(count == 0)
            {
                continue;
            }
            if (_xredis.lrange(dbi, szHKey, 0, count, Reply)) 
            {   
                ReplyData::iterator iter = Reply.begin();
                for (; iter != Reply.end(); iter++) 
                {
					CQspFtdcInputOrderField req;
                    memset(&req, 0, sizeof(CQspFtdcInputOrderField));
                    //交易所代码
                    strcpy(req.ExchangeID,"SHFE");
                    //会员号
                    strcpy(req.BrokerID, "9999");
                    //客户号
                    strcpy(req.InvestorID,"047811");
                    //交易用户
                    strcpy(req.UserID,"m001");
                    //合约
                    strcpy(req.InstrumentID, "zn1701");
                    //价格类型
                    req.OrderPriceType = '1';
                    //买卖方向
                    req.Direction = '0';
                    //开平标志
                    req.OffsetFlag='0';
                    //投机套保标志			
                    req.HedgeFlag = '1';
                    //价格
                    req.LimitPrice = 0.0;
                    //数量
                    req.Volume = 1;
                    //本地报单号
                    sprintf(req.UserOrderLocalID, "%010d", m_iReqNo++);
                    //			strcpy(req.UserOrderLocalID, "00000000001");
                    //有效期类型
                    req.TimeCondition = '1';
                    strcpy(req.GTDDate, "20160903");
                    // 成交量类型
                    req.VolumeCondition = '1';
                    req.ForceCloseReason = '0';

                    LOG_INFO("#client_queue_msg# %s %s", clientReq.c_str(), (*iter).str.c_str());
					m_pExchApi = m_LinkManager->GetTrade(req.UserID, true);
                    if(NULL != m_pExchApi && !m_pExchApi->ReqOrderInsert(0, req))
                    {
                        LOG_ERROR("报单失败了 %s %s", req.UserID, req.UserOrderLocalID);
                    }
                }
            }
            if(!_xredis.ltrim(dbi, szHKey, count, -1))
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



