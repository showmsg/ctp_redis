#include "global.h"
#include "Thread.h"
#include "plotbase.h"
#include "Inifile.h"
#include "Logger.h"
#include "Lib.h"
#include "json/json.h"
#include "UserApiDataType.h"

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
        xRedisClient        _xredis;

        IniFile             m_iniHndl;
        string              m_clientReq;
        int                 m_iReqNo;
        CPlotBase           m_plotbase;
        PlotRedis           m_plotRedis;
        string              m_routerMsg;
        string              m_group;
        string              m_appKey;
        string              m_rtnorder;
        string              m_rtntrade;
        string              m_rsporder;
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
	
	int iredis_cnt       = m_iniHndl.getIntValue(REDIS_SECTION, "rds_count", iRet);
	if(iredis_cnt < 1)
	{
		LOG_ERROR("Not config redis");
		exit(-1);
	}
	RedisNode RedisList[iredis_cnt];
	for(int j = 1; j <= iredis_cnt; j++)
	{
		int _index            = m_iniHndl.getIntValue(REDIS_SECTION, Lib::cati("rds_index_", j), iRet); 		
		string _redishost     = m_iniHndl.getStringValue(REDIS_SECTION, Lib::cati("rds_host_", j), iRet);
		int _port             = m_iniHndl.getIntValue(REDIS_SECTION, Lib::cati("rds_port_", j), iRet);
		string _redispasswd   = m_iniHndl.getStringValue(REDIS_SECTION, Lib::cati("rds_password_", j), iRet);
		int _poolsize         = m_iniHndl.getIntValue(REDIS_SECTION, Lib::cati("rds_poolsize_", j), iRet);
		int _pooltimeout      = m_iniHndl.getIntValue(REDIS_SECTION, Lib::cati("rds_pooltimeout_", j), iRet);
		int _isslave          = m_iniHndl.getIntValue(REDIS_SECTION, Lib::cati("is_redis_slave_", j), iRet);
		
		LOG_INFO("#Redis# rds_host:%s, rds_port:%d, rds_pwd:%s, rds_db:%d", _redishost.c_str(), _port, _redispasswd.c_str(),
            _index);
			
		RedisList[j-1].dbindex  = _index;
		RedisList[j-1].port     = _port;
		RedisList[j-1].poolsize = _poolsize;
		RedisList[j-1].timeout  = _pooltimeout;
		RedisList[j-1].role     = _isslave;
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

    m_rsporder  = _env + _rspinsert;
    m_rsporder += UNDERSCORE_FLAG;
    m_rsporder += _brokerid;
    m_rsporder += UNDERSCORE_FLAG;
    m_rsporder += "m001";

    m_rtnorder  = _env + _rtnorder;
    m_rtnorder += UNDERSCORE_FLAG;
    m_rtnorder += _brokerid;
    m_rtnorder += UNDERSCORE_FLAG;
    m_rtnorder += "m001";
    LOG_INFO("%s", m_rtnorder.c_str());

    m_rtntrade  = _env + _rtntrade;
    m_rtntrade += UNDERSCORE_FLAG;
    m_rtntrade += _brokerid;
    m_rtntrade += UNDERSCORE_FLAG;
    m_rtntrade += "m001";

    m_routerMsg  = _env + _routermsg;
    m_routerMsg += m_group;
	
	printf("Router:[%s]\n", m_routerMsg.c_str());
    m_clientReq = _env + _clientreq;
	
	LOG_INFO("#PLOT# [%s], SendQueue:[%s]", m_routerMsg.c_str(), m_clientReq.c_str());
    LOG_INFO("#Channel# channel:[%s], userstatus:[%s], client_queue:[%s]", _channel.c_str(), _userstatus.c_str(), _clientreq.c_str());
    LOG_INFO("rspaction:[%s], rspinsert:[%s], clientposition:[%s], instrument:[%s]", _rspaction.c_str(), _rspinsert.c_str(), 
            _clientposition.c_str(), _instruments.c_str());
    LOG_INFO("rtnorder:[%s], rtntrade:[%s]", _rtnorder.c_str(), _rtntrade.c_str());
    
    m_plotRedis.xredis             = &_xredis; 
    m_plotRedis.Env		           = _env;	
    m_plotRedis.Channel            = _env + _channel;	
    m_plotRedis.Snapshot           = _env + _snapshort;
    m_plotRedis.UserStatus         = _env + _userstatus;
    m_plotRedis.RspOrderInsert     = _env + _rspinsert;
    m_plotRedis.RspOrderAction     = _env + _rspaction;
    m_plotRedis.RtnOrder           = _env + _rtnorder;
    m_plotRedis.RtnTrade           = _env + _rtntrade;
    m_plotRedis.ClientPosition     = _env + _clientposition;
    m_plotRedis.Instruments        = _env + _instruments;
    m_plotRedis.ClientReq          = _env + _clientreq;
    m_plotRedis.Account            = _env + _account;
    m_plotRedis.RouterMsg          = _env + _routermsg;   

    LOG_INFO("===============================================================\n");

}

void CApp::Run()
{   
    RedisDBIdx dbi(&_xredis);
    
	/// 策略报单结构json
	// {group:a,msgtype:plota,id:1,brokerid:9999,userid:m001,
	//  invesotorid:a,exchangeid:shfe,instrumentid:zn1701,pricetype:0,
	// limitprice:1000.0,direction:buy}
	LOG_INFO("m_routerMsg:[%s]", m_routerMsg.c_str());
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
			
			Json::Reader reader;
			Json::Value clientMsgQueue;
            ///取到客户请求报单数量
            if (_xredis.lrange(dbi, m_routerMsg.c_str(), 0, count, Reply)) 
            {   
                ReplyData::iterator iter = Reply.begin();
                for (; iter != Reply.end(); iter++) 
                {
					if(reader.parse((*iter).str, clientMsgQueue))
					{
						if(clientMsgQueue["group"].compare("当前启动组"))
						{
							//促发策略
						}
					}
                }
            }
			
			///循环处理报入策略,根据行情和成交返回等情况触发报单,Redis连接,交易连接,报单
			//=================================================================
			VALUES vVal;

			for(int i = 0; i < count; i++)
			{
				Json::Value order;
				Json::FastWriter writer;

				order["itype"]                     = "order";
				order["exchangeid"]                = "SHFE";
				order["brokerid"]                  = "9999";
				order["investorid"]                = "047811";
				order["userid"]                    = "047811";
				order["instrumentid"]              = "zn1701";
				order["pricetype"]                 = OPT_LimitPrice;
				order["direction"]                 = D_Buy;
				order["offsetflag"]                = OF_Open;
				order["hedgeflag"]                 = CHF_Speculation;
				order["limitprice"]                = 14.40;
				order["volume"]                    = 1;
				order["timecondition"]             = TC_GFD;
				order["gtddate"]                   = "20161108";
				order["volumecondition"]           = VC_AV;
				order["closereason"]                = FCR_NotForceClose;

				string jsonstr = writer.write(order);
				vVal.push_back(jsonstr);
				LOG_INFO("%s %s", m_clientReq.c_str(), jsonstr.c_str());
			}
			
//			LOG_INFO("模拟策略发单发单%s", m_clientReq.c_str());
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
			//=================================================================
			
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



