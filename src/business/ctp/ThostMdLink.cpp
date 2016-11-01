#include "ThostMdLink.h"
#include "json/json.h"
#include "Logger.h"
#include "Lib.h"
#include "Redis.h"

vector<string> g_CTPSubMarketList;

CThostMdLink::CThostMdLink(ApiExchLink* mdlink)
{

    _brokerID = mdlink->BrokerID;
    _userID   = mdlink->UserID;
    _password = mdlink->Password;
    _address  = mdlink->Address;
    _flowpath = mdlink->FlowPath;
	
    _xredis   = NULL; 
}

CThostMdLink::~CThostMdLink()
{

}

void CThostMdLink::OnFrontConnected()
{
    char sTemp[1024];	
    sprintf(sTemp,"行情席位[%s]连接成功", _brokerID.c_str());
    printf("%s \n",sTemp);
    Login();
}

bool CThostMdLink::ReqLogin(string BrokerID, string UserID, string Password)
{
    _brokerID = BrokerID;
    _userID   = UserID;
    _password = Password;
    Login();
    return true;
}
void CThostMdLink::Login()
{
    if (strlen(_userID.c_str()) > 0)
    {
        CThostFtdcReqUserLoginField reqUserLogin;
        strcpy(reqUserLogin.TradingDay, m_pUserApi->GetTradingDay());
        strcpy(reqUserLogin.BrokerID, _brokerID.c_str());//经纪公司代码
        strcpy(reqUserLogin.UserID, _userID.c_str());
        strcpy(reqUserLogin.Password, _password.c_str());
        m_pUserApi->ReqUserLogin(&reqUserLogin, 0);
    }
}
void CThostMdLink::OnFrontDisconnected(int nReason)
{
    char sTemp[1024];	
    sprintf(sTemp,"行情席位[%s]断开,Reason=[%d]", _brokerID.c_str(), nReason);	

    printf("%s \n",sTemp);
    LOG_ERROR("#disconnect# %s", sTemp);
}
void CThostMdLink::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

    if (pRspInfo->ErrorID == 0)
    {				
        int cnt = g_CTPSubMarketList.size();
        if(cnt < 1)
        {
            return;
        }
        char ** Instrumnet;
        Instrumnet = (char**)malloc((sizeof(char*)) * cnt);
        for (int i = 0; i < cnt; i++) 
        {
            char * tmp = Lib::stoc(g_CTPSubMarketList[i]); 	
            Instrumnet[i] = tmp;
        }

        SubMarketData(Instrumnet, cnt);
        free(Instrumnet);
    }
    else
    {
        char sTemp[1024];	
        sprintf(sTemp,"行情席位[%s]登录失败[%d]: %s",_brokerID.c_str(), pRspInfo->ErrorID,pRspInfo->ErrorMsg);		
        printf("%s \n",sTemp);

        usleep(5000000);

        Login();
    }


}

void CThostMdLink::OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData)
{
    ///发布行情快照
    ///发布队列行情
    ///发布订阅行情
    if(NULL == pDepthMarketData) return;
    if(NULL != _xredis)
    {
        Json::FastWriter writer;
        Json::Value tick;

        string instrument = string(pDepthMarketData->InstrumentID);
        Lib::replace(instrument, " ", "#");
        tick["instrument"] = instrument;
        tick["price"] = pDepthMarketData->LastPrice;
        tick["vol"] = pDepthMarketData->Volume;
        //		tick['TradingDay'] = pDepthMarketData->TradingDay;
        tick["time"] = string(pDepthMarketData->UpdateTime);
        tick["msec"] = pDepthMarketData->UpdateMillisec;
        tick["bid1"] = pDepthMarketData->BidPrice1;
        tick["bidvol1"] = pDepthMarketData->BidVolume1;
        tick["ask1"] = pDepthMarketData->AskPrice1;
        tick["askvol1"] = pDepthMarketData->AskVolume1;

        std::string jsonStr = writer.write(tick);
        Lib::trimright(jsonStr, '\n');
        Lib::trimright(jsonStr, '\r');
		
 //       LOG_INFO("#Market# %s%s_%s\n%s", _channel.c_str(), _env.c_str(), instrument.c_str(), jsonStr.c_str());
       
//		LOG_INFO("%s%s_%s", _channel.c_str(), _env.c_str(), instrument.c_str());
		string key = _channel;
		key       += UNDERSCORE_FLAG;
		key       += instrument;
		RedisDBIdx dbi(_xredis);
		bool bRet = dbi.CreateDBIndex(key.c_str(), APHash, CACHE_TYPE_1);
		if(bRet)
		{
			int64_t count = 0;
			if(!_xredis->publish(dbi, key.c_str(), jsonStr, count))
			{
				LOG_ERROR("[%s] %s error %s", key.c_str(), __PRETTY_FUNCTION__, dbi.GetErrInfo());
			}
		}
		
		string snapshot = _snapshot;
		
		bRet = dbi.CreateDBIndex(snapshot.c_str(), APHash, CACHE_TYPE_1);
		if(bRet)
		{
			int64_t count = 0;
			if (!_xredis->hset(dbi, snapshot.c_str(), instrument, jsonStr, count)) {
				LOG_ERROR("[%s] %s error %s", snapshot.c_str(), __PRETTY_FUNCTION__, dbi.GetErrInfo());
			}
		}

            //只有开启了分时数据保存才保存
            if(_isTick)
            {
				string tick = _tick;				
				tick    += instrument;
				bRet = dbi.CreateDBIndex(tick.c_str(), APHash, CACHE_TYPE_1);
				if(bRet)
				{
					int64_t count = 0;
					VALUES vVal;
					vVal.push_back(jsonStr);
					if (!_xredis->rpush(dbi, tick.c_str(), vVal, count)) {
						LOG_ERROR("[%s] %s error %s", tick.c_str(), __PRETTY_FUNCTION__, dbi.GetErrInfo());
					}
					
				}
            }			


    }

}
void CThostMdLink::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}
void CThostMdLink::StartWork()
{
	char stemp[1024];
	memset(stemp, 0, sizeof(stemp));
	sprintf(stemp, "%s%s", _flowpath.c_str(), _userID.c_str());
	
    m_pUserApi = CThostFtdcMdApi::CreateFtdcMdApi(stemp);
    m_pUserApi->RegisterSpi(this);
    m_pUserApi->RegisterFront(Lib::stoc(_address));
    m_pUserApi->Init();	
    LOG_INFO("StartWork\n");
    //	m_pUserApi->Join();
}

///订阅行情应答
void CThostMdLink::OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if(NULL != pRspInfo)
    {

    }

    ///订阅成功，更新订阅行情列表
}

///取消订阅行情应答
void CThostMdLink::OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
    if(NULL != pRspInfo)
    {

    }	
    ///取消订阅成功，更新订阅行情列表
}

///订阅行情。
///@param ppInstrumentID 合约ID  
///@param nCount 要订阅/退订行情的合约个数
///@remark 
int CThostMdLink::SubMarketData(char *ppInstrumentID[], int nCount)
{
    int iRet = m_pUserApi->SubscribeMarketData(ppInstrumentID, nCount);
    if(iRet)
    {
        LOG_ERROR("订阅行情错误");
    }
    for(int i = 0; i < nCount; i++)
    {
        bool bFnd = false;
        for(int j = 0; j < g_CTPSubMarketList.size(); j++)
        {
            if(strcmp(ppInstrumentID[i], g_CTPSubMarketList[j].c_str()) == 0)
            {
                bFnd = true;
                break;
            }
        }
        if(!bFnd)
        {
            g_CTPSubMarketList.push_back(ppInstrumentID[i]);
        }

    }

    return iRet;
}

///退订行情。
///@param ppInstrumentID 合约ID  
///@param nCount 要订阅/退订行情的合约个数
///@remark 
int CThostMdLink::UnSubMarketData(char *ppInstrumentID[], int nCount)
{
    int iRet = m_pUserApi->UnSubscribeMarketData(ppInstrumentID, nCount);
    for(int i = 0; i < nCount; i++)
    {
        for(vector<string>::iterator it = g_CTPSubMarketList.begin(); it != g_CTPSubMarketList.end(); )
        {
            if(strcmp(ppInstrumentID[i], (*it).c_str()) == 0)
            {
                g_CTPSubMarketList.erase(it++);
                break;
            }
            else
            {
                it++;
            }
        }

    }	
    return iRet;
}

void CThostMdLink::SetQuot(vector<string> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        bool bFnd = false;
        for(int j = 0; j < g_CTPSubMarketList.size(); j++)
        {
            if(strcmp(v[i].c_str(), g_CTPSubMarketList[j].c_str()) == 0)
            {
                bFnd = true;
                break;
            }
        }
        if(!bFnd)
        {
            g_CTPSubMarketList.push_back(v[i]);
        }

    }
}
void CThostMdLink::SetRedis(MdRedis* redis)
{
    m_redis          = redis;
    _xredis          = redis->xredis;   
    _env             = redis->Env;
    _snapshot        = redis->Snapshot;
    _tick            = redis->Tick;
    _mrklist         = redis->MrktList;
    _isTick          = redis->isTick;
    _channel         = redis->Channel;	
		
}

vector<string> CThostMdLink::GetQuot(string storePath)
{
    vector<string> instruments;
    FILE* m_fp = fopen(storePath.c_str(), "rb");

    if(NULL == m_fp)
    {
        return instruments;
    }
    char line[1024];
    string stemp;
    while(fgets(line, 1024,m_fp) != NULL)
    {
        stemp = line;
        Lib::trim(stemp);
        if(stemp.empty())
        {
            continue;
        }
        instruments.push_back(stemp);
    }

    if(NULL != m_fp)
    {
        fclose(m_fp);
        m_fp = NULL;
    }
    return instruments;
}
void CThostMdLink::StoreQuot(string storePath)
{
    printf("%s\n", storePath.c_str());
    FILE* m_fp = fopen(storePath.c_str(), "wb+");
    if(NULL == m_fp)
    {
        return;
    }
    for(int i = 0; i < g_CTPSubMarketList.size(); i++)
    {		
        int write_len = fprintf(m_fp, "%s\n", g_CTPSubMarketList[i].c_str());
    }

    fflush(m_fp);
    if(NULL != m_fp)
    {
        fclose(m_fp);
        m_fp = NULL;
    }

}
