#include "global.h"
#include "Thread.h"
#include "plotbase.h"
#include "Inifile.h"
#include "Logger.h"
#include "Lib.h"

using namespace inifile;

const char* CONF_INI = "../conf/config.ini";

class CApp : public Thread
{
    public:
        CApp();
        virtual ~CApp(void);
        void Init(string group, string appkey);
        void Run();
    private:
        xRedisClient _xredis;

        IniFile m_iniHndl;
        string m_clientReq;
        int m_iReqNo;
        CPlotBase m_plotbase;
        PlotRedis m_plotRedis;
        string m_routerMsg;
        string m_group;
        string m_appKey;
        string m_rtnorder;
        string m_rtntrade;
        string m_rsporder;
        map<string, string> m_subscribeList;
}; 

CApp::CApp()
{
    m_iReqNo = 0;
}

CApp::~CApp()
{

}
void CApp::Init(string group, string appkey)
{
    m_group  = group;
    m_appKey = appkey; 

    string FlowPath;
    int iRet = 0;
    m_iniHndl.load(CONF_INI);

    string _env = m_iniHndl.getStringValue(SYSTEM_SECTION, "env", iRet);

    //#########################################################################
    // 1. 路由分发到策略，策略只做接收？如何接收Redis订阅，还是使用消息队列？
    // 2. 策略模块在收到策略后，订阅成交和Order，订阅对应行情，促发策略计算；
    // 3. 促发报单，检查资金持仓与冻结，加上策略模块标记发到Redis中；
    // 4. 接收返回消息再次促发订单；
    //#########################################################################
    int _db             = m_iniHndl.getIntValue(REDIS_SECTION, "rds_db", iRet);    
    string _redishost   = m_iniHndl.getStringValue(REDIS_SECTION, "rds_host", iRet);
    int _port           = m_iniHndl.getIntValue(REDIS_SECTION, "rds_port", iRet);
    string _redispasswd = m_iniHndl.getStringValue(REDIS_SECTION, "rds_password", iRet);	

    LOG_INFO("#Redis# rds_host:%s, rds_port:%d, rds_pwd:%s, rds_db:%d", _redishost.c_str(), _port, _redispasswd.c_str(),
            _db);

    string _userstatus     = m_iniHndl.getStringValue(TRADE_SECTION, "channel_user_status", iRet);
    string _channel        = m_iniHndl.getStringValue(TRADE_SECTION, "channel_market", iRet);
    string _rspaction      = m_iniHndl.getStringValue(TRADE_SECTION, "channel_trade_rspaction", iRet);
    string _rspinsert      = m_iniHndl.getStringValue(TRADE_SECTION, "channel_trade_rspinsert", iRet);
    string _rtnorder       = m_iniHndl.getStringValue(TRADE_SECTION, "channel_trade_rtnorder", iRet);
    string _rtntrade       = m_iniHndl.getStringValue(TRADE_SECTION, "channel_trade_rtntrade", iRet);
    string _clientposition = m_iniHndl.getStringValue(TRADE_SECTION, "channel_user_clientposition", iRet);
    string _instruments    = m_iniHndl.getStringValue(TRADE_SECTION, "channel_instrument", iRet);
    string _clientreq      = m_iniHndl.getStringValue(TRADE_SECTION, "client_msg_queue", iRet);
    string _snapshort      = m_iniHndl.getStringValue(TRADE_SECTION, "channel_snapshot", iRet);
    string _account        = m_iniHndl.getStringValue(TRADE_SECTION, "channel_user_account", iRet);
    string _routermsg      = m_iniHndl.getStringValue(TRADE_SECTION, "router_msg_queue", iRet);

    string _brokerid = m_iniHndl.getStringValue(TRADE_SECTION, "trade_broker_id", iRet);
    string _userid = m_iniHndl.getStringValue(TRADE_SECTION, "trade_user_id", iRet);

    m_rsporder = _rspinsert + _env;
    m_rsporder += "_";
    m_rsporder += _brokerid;
    m_rsporder += "_";
    m_rsporder += "m001";

    m_rtnorder = _rtnorder  + _env;
    m_rtnorder += "_";
    m_rtnorder += _brokerid;
    m_rtnorder += "_";
    m_rtnorder += "m001";
    LOG_INFO("%s", m_rtnorder.c_str());

    m_rtntrade = _rtntrade  + _env;
    m_rtntrade += "_";
    m_rtntrade += _brokerid;
    m_rtntrade += "_";
    m_rtntrade += "m001";

    m_routerMsg = _routermsg + _env;
    m_routerMsg += "_";
    m_routerMsg += m_group;

    m_clientReq = _clientreq + _env;

    LOG_INFO("#Channel# channel:%s, userstatus:%s, client_queue:%s", _channel.c_str(), _userstatus.c_str(), _clientreq.c_str());
    LOG_INFO("rspaction:%s, rspinsert:%s, clientposition:%s, instrument:%s", _rspaction.c_str(), _rspinsert.c_str(), 
            _clientposition.c_str(), _instruments.c_str());
    LOG_INFO("rtnorder:%s, rtntrade:%s", _rtnorder.c_str(), _rtntrade.c_str());

    _xredis.Init(3);

    RedisNode RedisList1[3] = {
        {0, "127.0.0.1", 6379, "123456", 2, 5, 0},
        {1, "127.0.0.1", 6379, "123456", 2, 5, 0},
        {2, "127.0.0.1", 6379, "123456", 2, 5, 0}
    };

    if(_xredis.ConnectRedisCache(RedisList1, 3, CACHE_TYPE_1))
    {
        LOG_ERROR("connect redis error");
    }

    //	m_plotRedis.RedisPub           = &_publisher;
    m_plotRedis.xredis             = &_xredis; 
    m_plotRedis.Env		           = _env;	
    m_plotRedis.Channel            = _channel;	
    m_plotRedis.Snapshot           = _snapshort;
    m_plotRedis.UserStatus         = _userstatus;
    m_plotRedis.RspOrderInsert     = _rspinsert;
    m_plotRedis.RspOrderAction     = _rspaction;
    m_plotRedis.RtnOrder           = _rtnorder;
    m_plotRedis.RtnTrade           = _rtntrade;
    m_plotRedis.ClientPosition     = _clientposition;
    m_plotRedis.Instruments        = _instruments;
    m_plotRedis.ClientReq          = _clientreq;
    m_plotRedis.Account            = _account;
    m_plotRedis.RouterMsg          = _routermsg;   

    LOG_INFO("===============================================================\n");

}

void CApp::Run()
{   
    RedisDBIdx dbi(&_xredis);
    VALUES vVal;    
    bool bRet = dbi.CreateDBIndex(m_routerMsg.c_str(), APHash, CACHE_TYPE_1);
    while(true)
    {	
        if (bRet) {
            ArrayReply Reply;
            int64_t count = 0;
            if (!_xredis.llen(dbi, m_routerMsg.c_str(), count)) {
                LOG_ERROR("%s error %s", __PRETTY_FUNCTION__, dbi.GetErrInfo());
            }
			if(count == 0)
			{
				continue;
			}
			count = count > 1000?1000:count;
            //取到客户请求报单数量
            if (_xredis.lrange(dbi, m_routerMsg.c_str(), 0, count, Reply)) 
            {   
                ReplyData::iterator iter = Reply.begin();
                for (; iter != Reply.end(); iter++) 
                {
					vVal.push_back((*iter).str);
//                    LOG_INFO("%d\t%s", (*iter).type, (*iter).str.c_str());
                }
            }
			
			for(int i = 0; i < 10000; i++)
			{
				vVal.push_back("test");
			}
			
			//模拟往交易发送
			bRet = dbi.CreateDBIndex(m_clientReq.c_str(), APHash, CACHE_TYPE_1);
			if(bRet)
			{
				int64_t count = 0;
				if(!_xredis.rpush(dbi, m_clientReq.c_str(), vVal, count))
				{
					LOG_ERROR("%s error %s", __PRETTY_FUNCTION__, dbi.GetErrInfo());
				}					
			}
			
            if(!_xredis.ltrim(dbi, m_routerMsg.c_str(), count, -1))
            {
                LOG_ERROR("%s error %s", __PRETTY_FUNCTION__, dbi.GetErrInfo());
            }
        }

    }		 
}

int main(int argc, char const *argv[])
{
    string LogPath;	
    int iRet = 0;

    if(argc < 2)
    {
        printf("Usage:%s Group Appkey\n", argv[0]);
        exit(-1);
    }

    IniFile g_ini;
    g_ini.load(CONF_INI);
    string _env = g_ini.getStringValue(SYSTEM_SECTION, "env", iRet);
    LogPath = g_ini.getStringValue(SYSTEM_SECTION, "plot_log_path", iRet);
    if(iRet != RET_OK)
    {
        LogPath = "plot_@@_$$.log";
    }
    Lib::replace(LogPath, ENVNO_REPLACE_FLAG, _env);
    Lib::replace(LogPath, GROUP_REPLACE_FLAG, argv[2]);
    SET_LOG_NAME(LogPath);
    //设置日志级别
    SET_LOG_LEVEL(LOG_LEVEL_TRACE);

    //设置日志大小
    SET_LOG_SIZE(10 * 1024 * 1024);

    //设置占用磁盘空间大小
    SET_LOG_SPACE(100 * 1024 * 1024);

    LOG_INFO("####################################################################");
    LOG_INFO("#                         PLOT                                     #");
    LOG_INFO("#                         V1.0.0                                   #");
    LOG_INFO("####################################################################\n");


    CApp app;
    app.Init(argv[1], argv[2]);
    app.Start();
    app.Join();

    return 0;
}



