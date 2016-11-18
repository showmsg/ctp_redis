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
		void ReqOrder(Json::Value value);
		void ReqCancel(Json::Value value);
    private:
        CBaseExchApi* m_pExchApi;
        xRedisClient _xredis;
		xRedisClient m_mainxredis;
        IniFile g_ini;
        string clientReq;
        unsigned long long m_iReqNo;
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

    string _response       = g_ini.getStringValue(TRADE_SECTION, "channel_trade_response", iRet);   
    string _clientposition = g_ini.getStringValue(TRADE_SECTION, "channel_user_clientposition", iRet);
    string _instruments    = g_ini.getStringValue(TRADE_SECTION, "channel_instrument", iRet);
    string _clientreq      = g_ini.getStringValue(TRADE_SECTION, "client_msg_queue", iRet);
    string _mrktlist       = g_ini.getStringValue(TRADE_SECTION, "channel_marketlist", iRet);
	
	LOG_INFO("#Channel# tick:[[%s], userstatus:[%s], client_queue:[%s]", _tick.c_str(), _userstatus.c_str(), _clientreq.c_str());
    LOG_INFO("response:[%s], clientposition:[%s], instrument:[%s]", _response.c_str(), _clientposition.c_str(), _instruments.c_str());
   
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
		mdlink.MrktList = _env + _mrktlist;
		mdlink.MrktGroup= _group;
		mdlink.isTrade  = 1;
		m_linkVect.push_back(mdlink);
	}
	
    clientReq = _env + _clientreq;
	
	LOG_INFO("#ORDER# OrderQueue:%s", clientReq.c_str());
    tdredis.xredis           = &_xredis;
    tdredis.Env		           = _env;
    tdredis.Channel            = _env + _channel;	
    tdredis.Tick               = _env + _tick;
    tdredis.UserStatus         = _env + _userstatus;
    tdredis.Response           = _env + _response;    
    tdredis.ClientPosition     = _env + _clientposition;
    tdredis.Instruments        = _env + _instruments;
    tdredis.ClientReq          = _env + _clientreq;
    tdredis.MrktList           = _env + _mrktlist;
		
	m_LinkManager = new CGateLinkManager();
	m_LinkManager->Init(m_linkVect);    
    
	m_LinkManager->StartTrade(&tdredis);
	
    LOG_INFO("CTP基础数据准备就绪，开始接单了");
    LOG_INFO("===============================================================\n");
}

void CApp::ReqOrder(Json::Value root)
{
	CInputOrderField req;
	memset(&req, 0, sizeof(CInputOrderField));
	
	//交易所代码
	strcpy(req.ExchangeID, root["exchangeid"].asString().c_str());
	//会员号
	strcpy(req.BrokerID, root["brokerid"].asString().c_str());
	//客户号
	strcpy(req.InvestorID, root["investorid"].asString().c_str());
	//交易用户
	strcpy(req.UserID, root["userid"].asString().c_str());
	//合约
	strcpy(req.InstrumentID, root["instrumentid"].asString().c_str());
	//价格类型
	req.OrderPriceType = root["pricetype"].asInt();
	//买卖方向
	req.Direction = root["direction"].asInt();
	//开平标志
	req.OffsetFlag = root["offsetflag"].asInt();
	//投机套保标志			
	req.HedgeFlag = root["hedgeflag"].asInt();
	//价格
	req.LimitPrice = root["limitprice"].asDouble();
	//数量
	req.Volume = root["volume"].asInt();
	
	//			strcpy(req.UserOrderLocalID, "00000000001");
	//有效期类型
	req.TimeCondition = root["timecondition"].asInt();
	strcpy(req.GTDDate, root["gtddate"].asString().c_str());
	// 成交量类型
	req.VolumeCondition = root["volumecondition"].asInt();
	req.ForceCloseReason = root["closereason"].asInt();

	m_pExchApi = m_LinkManager->GetTrade(req.UserID, true);
	if(NULL != m_pExchApi)
	{
		//本地报单号
		strcpy(req.UserOrderLocalID, m_pExchApi->GetLocalID());
		LOG_INFO("报单 UserID:%s, OrderLocalID:%s", req.UserID, req.UserOrderLocalID);
		if(!m_pExchApi->ReqOrderInsert(m_iReqNo, req))
		{
			LOG_ERROR("报单失败了 %s %s", req.UserID, req.UserOrderLocalID);
		}
		
	}
	else
	{
		LOG_ERROR("客户未登录 %s %s", req.UserID, req.UserOrderLocalID);
	}
	m_iReqNo++;
}
/**
*  接收报单数据json
*  { "itype":'A',
*    
*	}
*/
void CApp::ReqCancel(Json::Value root)
{
	COrderActionField req;
	memset(&req, 0, sizeof(COrderActionField));
	
	//交易所代码
	strcpy(req.ExchangeID, root["exchangeid"].asString().c_str());
	//报单编号
	strcpy(req.OrderSysID, root["ordersysid"].asString().c_str());
	//会员号
	strcpy(req.BrokerID, root["brokerid"].asString().c_str());
	//客户号
	strcpy(req.InvestorID, root["investorid"].asString().c_str());
	//交易用户
	strcpy(req.UserID, root["userid"].asString().c_str());
	
	//被撤订单的本地报单编号
	strcpy(req.UserOrderLocalID, root["orderlocalid"].asString().c_str());	
	//报单操作标志
	req.ActionFlag = root["actionflag"].asInt();	
	//价格
	req.LimitPrice = root["limitprice"].asDouble();	
	//数量
	req.VolumeChange = root["volumechange"].asInt();	

	m_pExchApi = m_LinkManager->GetTrade(req.UserID, true);
	if(NULL != m_pExchApi)
	{
		//本次撤单操作的本地编号
		strcpy(req.UserOrderActionLocalID, m_pExchApi->GetLocalID());
		LOG_INFO("报单 UserID:%s, OrderLocalID:%s, OrderSysID:%s", req.UserID, req.UserOrderLocalID, req.OrderSysID);
		if(!m_pExchApi->ReqOrderAction(m_iReqNo, req))
		{
			LOG_ERROR("报单失败了 %s %s", req.UserID, req.UserOrderLocalID);
		}
		
	}
	else
	{
		LOG_ERROR("客户未登录 %s %s", req.UserID, req.UserOrderLocalID);
	}
	m_iReqNo++;
}

void CApp::Run()
{
	//如果交易登录且查询基础信息完毕，可以进行报单
	
    const char* szHKey = clientReq.c_str();
    RedisDBIdx dbi(&_xredis);
    VALUES vVal;    
    bool bRet = dbi.CreateDBIndex(szHKey, APHash, CACHE_TYPE_1);
	LOG_INFO("ClientReq[%s]", szHKey);
    while(true)
    {	
        if (bRet) {
            ArrayReply Reply;
            int64_t count = 0;
            if (!_xredis.llen(dbi, szHKey, count)) {
                LOG_ERROR("[%s] %s error %s", clientReq.c_str(), __PRETTY_FUNCTION__, dbi.GetErrInfo());
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
					Json::Reader reader;
					Json::Value root;

					if(reader.parse((*iter).str, root))
					{

						//内部报单类型
						if(!root.isMember("itype"))
						{
							LOG_ERROR("内部报单类型字段不存在");
							continue;
						}
						
						int itype = root["itype"].asInt();
						//报单类型
						switch(itype)
						{
							case IMSG_TYPE_REQORDER:
							{
								ReqOrder(root);
							}
							break;
							case IMSG_TYPE_REQACTION:
							{
								ReqCancel(root);
							}
							break;
							default:
							LOG_ERROR("不支持的报单类型[%c] %s", itype, (*iter).str.c_str());
							break;
							
						}
						
					}
					else
					{
						LOG_ERROR("非内部报单数据%s", (*iter).str.c_str());
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



