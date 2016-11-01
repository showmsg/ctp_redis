#include "ThostTradeLink.h"
#include "Lib.h"


CThostTradeLink::CThostTradeLink(ApiExchLink *api)
{
    _brokerID = api->BrokerID;
    _userID   = api->UserID;
    _password = api->Password;
    _address  = api->Address;
    _flowpath = api->FlowPath;
    m_redis   = NULL;
    m_maxInstrumentsCnt = 0;
}
CThostTradeLink::~CThostTradeLink()
{

}

//连接
void CThostTradeLink::OnFrontConnected()
{
    char sTemp[1024];	
    sprintf(sTemp,"交易席位[%s]连接成功", _brokerID.c_str());
    printf("%s \n",sTemp);
    Login();

}

//断开
void CThostTradeLink::OnFrontDisconnected(int nReason)
{
    char sTemp[1024];	
    sprintf(sTemp,"交易席位[%s]断开,Reason=[%d]",  _brokerID.c_str(),nReason);		
    LOG_ERROR("#disconnect# %s", sTemp);
    printf("%s \n",sTemp);

}
bool CThostTradeLink::ReqLogin(int nRequestID, CQspFtdcReqUserLoginField &ReqLoginField)
{
    _brokerID = ReqLoginField.BrokerID;
    _userID   = ReqLoginField.UserID;
    _password = ReqLoginField.Password;
    Login();
    return true;
}
//登录
void CThostTradeLink::Login()
{
    if (!_brokerID.empty())
    {
        printf("发起登录...\n");
        CThostFtdcReqUserLoginField reqUserLogin;
        memset(&reqUserLogin, 0, sizeof(reqUserLogin));
        strcpy(reqUserLogin.TradingDay, m_pUserApi->GetTradingDay());
        strncpy(reqUserLogin.BrokerID, _brokerID.c_str(), sizeof(reqUserLogin.BrokerID));
        strncpy(reqUserLogin.UserID, _userID.c_str(), sizeof(reqUserLogin.UserID));
        strncpy(reqUserLogin.Password, _password.c_str(), sizeof(reqUserLogin.Password));

        m_pUserApi->ReqUserLogin(&reqUserLogin, 0);
    }
}

void CThostTradeLink::OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (pRspInfo->ErrorID == 0)
    {	
        m_iMaxLocalNo = atoi(pRspUserLogin->MaxOrderRef)+1;

        printf("登录成功!\n");
        if(NULL != _xredis)
        {	
            Json::FastWriter writer;
            Json::Value userStatus;
            userStatus["TradingDay"] = pRspUserLogin->TradingDay;
            userStatus["LoginTime"]  = pRspUserLogin->LoginTime;
            userStatus["BrokerID"]  = pRspUserLogin->BrokerID;
            userStatus["UserID"]  = pRspUserLogin->UserID;
            userStatus["SystemName"]  = pRspUserLogin->SystemName;
            userStatus["FrontID"]  = pRspUserLogin->FrontID;
            userStatus["SessionID"]  = pRspUserLogin->SessionID;
            userStatus["MaxOrderRef"]  = pRspUserLogin->MaxOrderRef;
            std::string jsonStr = writer.write(userStatus);
            Lib::trimright(jsonStr, '\n');
            Lib::trimright(jsonStr, '\r');
			
			string userinfo = m_redis->UserStatus;
			LOG_INFO("%s \n %s", userinfo.c_str(), jsonStr.c_str());
			string brokeruser = pRspUserLogin->BrokerID;
			brokeruser += UNDERSCORE_FLAG;
			brokeruser += pRspUserLogin->UserID;
			
			RedisDBIdx dbi(_xredis);				
			bool bRet = dbi.CreateDBIndex(userinfo.c_str(), APHash, CACHE_TYPE_1);
			if(bRet)
			{
				int64_t count = 0;
				LOOP_USERLOGIN:
				if (!_xredis->hset(dbi, userinfo.c_str(), brokeruser, jsonStr, count)) {
					LOG_ERROR("[%s][%s] %s error %s", userinfo.c_str(), brokeruser.c_str(), __PRETTY_FUNCTION__, dbi.GetErrInfo());
					usleep(10);
					goto LOOP_USERLOGIN;
				}
			}		
            LOG_INFO("#rsplogin# %s", jsonStr.c_str());
        }

        usleep(2000);
        //发送合约查询
        ReqSettlementInfoConfirm();	
    }
    else
    {
        char sTemp[1024];	
        sprintf(sTemp,"交易席位[%s]登录失败[%d]: %s",_brokerID.c_str(),pRspInfo->ErrorID,pRspInfo->ErrorMsg);		
        // 		g_Logger.WriteWarnInfo("",0,"中金所接口",sTemp);
        printf("%s \n",sTemp);
        usleep(5000000);

        Login();		
    }
}


void CThostTradeLink::ReqSettlementInfoConfirm()
{
    printf("投资者结算结果确认...\n");
    CThostFtdcSettlementInfoConfirmField req;
    memset(&req, 0, sizeof(req));
    strcpy(req.BrokerID, _brokerID.c_str());
    strcpy(req.InvestorID, _userID.c_str());
    int iResult = m_pUserApi->ReqSettlementInfoConfirm(&req, ++m_iReqSeqNo);
    while (iResult)
    {
        usleep(1000000);
        iResult = m_pUserApi->ReqSettlementInfoConfirm(&req, m_iReqSeqNo);
        if (iResult)
        {
            char sTemp[1024];	
            sprintf(sTemp,"投资者结算结果确认失败!");

        }
    }
    //首个
    if(iResult)
    {
        m_bEssentialDataLast = false;
    }
    else
    {
        m_bEssentialData  = true;
    }
}

void CThostTradeLink::OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (bIsLast )
    {		
        ///请求查询合约
        ReqContract();
    }
}
void CThostTradeLink::OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

}

//报单应答
void CThostTradeLink::OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
	printf("OnRspOrderInsert %s\n", pRspInfo->ErrorMsg);
	LOG_INFO("OnRspOrderInsert %s\n", pRspInfo->ErrorMsg);
    if(NULL != pInputOrder && NULL != _xredis)
    {
		m_rspinserMap[pInputOrder->UserID] += 1; 
        Json::FastWriter writer;
        Json::Value rspOrderInsert;
		rspOrderInsert["Idx"]                = m_rspinserMap[pInputOrder->UserID];
        rspOrderInsert["BrokerID"] = pInputOrder->BrokerID;
        rspOrderInsert["InvestorID"] = pInputOrder->InvestorID;
        rspOrderInsert["InstrumentID"] = pInputOrder->InstrumentID;
        rspOrderInsert["OrderRef"] = pInputOrder->OrderRef;
        rspOrderInsert["UserID"] = pInputOrder->UserID;
        rspOrderInsert["OrderPriceType"] = pInputOrder->OrderPriceType;
        rspOrderInsert["Direction"] = pInputOrder->Direction;
        rspOrderInsert["CombOffsetFlag"] = pInputOrder->CombOffsetFlag;
        rspOrderInsert["CombHedgeFlag"] = pInputOrder->CombHedgeFlag;
        rspOrderInsert["LimitPrice"] = pInputOrder->LimitPrice;
        rspOrderInsert["VolumeTotalOriginal"] = pInputOrder->VolumeTotalOriginal;
        rspOrderInsert["TimeCondition"] = pInputOrder->TimeCondition;
        rspOrderInsert["GTDDate"] = pInputOrder->GTDDate;
        rspOrderInsert["VolumeCondition"] = pInputOrder->VolumeCondition;
        rspOrderInsert["MinVolume"] = pInputOrder->MinVolume;
        rspOrderInsert["ContingentCondition"] = pInputOrder->ContingentCondition;
        rspOrderInsert["StopPrice"] = pInputOrder->StopPrice;
        rspOrderInsert["ForceCloseReason"] = pInputOrder->ForceCloseReason;
        rspOrderInsert["IsAutoSuspend"] = pInputOrder->IsAutoSuspend;
        rspOrderInsert["BusinessUnit"] = pInputOrder->BusinessUnit;
        rspOrderInsert["RequestID"] = pInputOrder->RequestID;
        rspOrderInsert["UserForceClose"] = pInputOrder->UserForceClose;
        rspOrderInsert["IsSwapOrder"] = pInputOrder->IsSwapOrder;
        rspOrderInsert["ExchangeID"] = pInputOrder->ExchangeID;
        rspOrderInsert["InvestUnitID"] = pInputOrder->InvestUnitID;
        rspOrderInsert["AccountID"] = pInputOrder->AccountID;
        rspOrderInsert["CurrencyID"] = pInputOrder->CurrencyID;
        rspOrderInsert["ClientID"] = pInputOrder->ClientID;
        rspOrderInsert["IPAddress"] = pInputOrder->IPAddress;
        rspOrderInsert["MacAddress"] = pInputOrder->MacAddress;

        std::string jsonStr = "'";
		jsonStr += writer.write(rspOrderInsert);
        Lib::trimright(jsonStr, '\n');
        Lib::trimright(jsonStr, '\r');
		jsonStr += "'";
				
        string key = m_redis->RspOrderInsert;
        key += UNDERSCORE_FLAG;
        key += pInputOrder->BrokerID;
        key += UNDERSCORE_FLAG;
        key += pInputOrder->UserID;
		
		RedisDBIdx dbi(_xredis);
		//模拟往交易发送
		bool bRet = dbi.CreateDBIndex(key.c_str(), APHash, CACHE_TYPE_1);
		if(bRet)
		{
			int64_t count = 0;
			VALUES vVal;
			vVal.push_back(jsonStr);
			if(!_xredis->rpush(dbi, key.c_str(), vVal, count))
			{
				LOG_ERROR("%s error %s", __PRETTY_FUNCTION__, dbi.GetErrInfo());
			}					
		}
    }
}
//错单回报
void CThostTradeLink::OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo)
{

}

//撤单应答
void CThostTradeLink::OnRspOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
    printf("OnRspOrderAction\n");
    if(NULL != pOrderAction && NULL != _xredis)
    {
		m_rspactionMap[pOrderAction->UserID] += 1;
        Json::FastWriter writer;
        Json::Value rspOrderAction;
		rspOrderAction["Idx"]            = m_rspactionMap[pOrderAction->UserID];
        rspOrderAction["BrokerID"] = pOrderAction->BrokerID;
        rspOrderAction["InvestorID"] = pOrderAction->InvestorID;
        rspOrderAction["OrderActionRef"] = pOrderAction->OrderActionRef;
        rspOrderAction["OrderRef"] = pOrderAction->OrderRef;
        rspOrderAction["RequestID"] = pOrderAction->RequestID;
        rspOrderAction["FrontID"] = pOrderAction->FrontID;
        rspOrderAction["SessionID"] = pOrderAction->SessionID;
        rspOrderAction["ExchangeID"] = pOrderAction->ExchangeID;
        rspOrderAction["OrderSysID"] = pOrderAction->OrderSysID;
        rspOrderAction["ExchangeID"] = pOrderAction->ExchangeID;
        rspOrderAction["ActionFlag"] = pOrderAction->ActionFlag;
        rspOrderAction["LimitPrice"] = pOrderAction->LimitPrice;
        rspOrderAction["VolumeChange"] = pOrderAction->VolumeChange;
        rspOrderAction["ActionDate"] = pOrderAction->ActionDate;
        rspOrderAction["ActionTime"] = pOrderAction->ActionTime;
        rspOrderAction["TraderID"] = pOrderAction->TraderID;
        rspOrderAction["InstallID"] = pOrderAction->InstallID;
        rspOrderAction["OrderLocalID"] = pOrderAction->OrderLocalID;
        rspOrderAction["ActionLocalID"] = pOrderAction->ActionLocalID;
        rspOrderAction["ParticipantID"] = pOrderAction->ParticipantID;
        rspOrderAction["ClientID"] = pOrderAction->ClientID;
        rspOrderAction["BusinessUnit"] = pOrderAction->BusinessUnit;
        rspOrderAction["OrderActionStatus"] = pOrderAction->OrderActionStatus;
        rspOrderAction["UserID"] = pOrderAction->UserID;
        rspOrderAction["StatusMsg"] = pOrderAction->StatusMsg;
        rspOrderAction["InstrumentID"] = pOrderAction->InstrumentID;
        rspOrderAction["BranchID"] = pOrderAction->BranchID;
        rspOrderAction["InvestUnitID"] = pOrderAction->InvestUnitID;
        rspOrderAction["IPAddress"] = pOrderAction->IPAddress;
        rspOrderAction["MacAddress"] = pOrderAction->MacAddress;

        std::string jsonStr = "'";
		jsonStr += writer.write(rspOrderAction);		
        Lib::trimright(jsonStr, '\n');
        Lib::trimright(jsonStr, '\r');
		jsonStr += "'";
		
        string key = m_redis->RspOrderAction;
        
        key += pOrderAction->BrokerID;
        key +=  UNDERSCORE_FLAG;
        key += pOrderAction->UserID;
		
		RedisDBIdx dbi(_xredis);
		//模拟往交易发送
		bool bRet = dbi.CreateDBIndex(key.c_str(), APHash, CACHE_TYPE_1);
		if(bRet)
		{
			int64_t count = 0;
			VALUES vVal;
			vVal.push_back(jsonStr);
			if(!_xredis->rpush(dbi, key.c_str(), vVal, count))
			{
				LOG_ERROR("%s error %s", __PRETTY_FUNCTION__, dbi.GetErrInfo());
			}					
		}
    }
}
//错误撤单回报
void CThostTradeLink::OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo)
{

}

//报单通知
void CThostTradeLink::OnRtnOrder(CThostFtdcOrderField *pOrder)
{
    printf("OnRtnOrder\n");
    if(NULL != pOrder && NULL != _xredis)
    {
		m_rtnorderMap[pOrder->UserID] += 1;
        Json::FastWriter writer;
        Json::Value rspOrderInsert;
		rspOrderInsert["Idx"]                = m_rtnorderMap[pOrder->UserID];
        rspOrderInsert["BrokerID"] = pOrder->BrokerID;
        rspOrderInsert["InvestorID"] = pOrder->InvestorID;
        rspOrderInsert["InstrumentID"] = pOrder->InstrumentID;
        rspOrderInsert["OrderRef"] = pOrder->OrderRef;
        rspOrderInsert["UserID"] = pOrder->UserID;
        rspOrderInsert["OrderPriceType"] = pOrder->OrderPriceType;
        rspOrderInsert["Direction"] = pOrder->Direction;
        rspOrderInsert["CombOffsetFlag"] = pOrder->CombOffsetFlag;
        rspOrderInsert["CombHedgeFlag"] = pOrder->CombHedgeFlag;
        rspOrderInsert["LimitPrice"] = pOrder->LimitPrice;
        rspOrderInsert["VolumeTotalOriginal"] = pOrder->VolumeTotalOriginal;
        rspOrderInsert["TimeCondition"] = pOrder->TimeCondition;
        rspOrderInsert["GTDDate"] = pOrder->GTDDate;
        rspOrderInsert["VolumeCondition"] = pOrder->VolumeCondition;
        rspOrderInsert["MinVolume"] = pOrder->MinVolume;
        rspOrderInsert["ContingentCondition"] = pOrder->ContingentCondition;
        rspOrderInsert["StopPrice"] = pOrder->StopPrice;
        rspOrderInsert["ForceCloseReason"] = pOrder->ForceCloseReason;
        rspOrderInsert["IsAutoSuspend"] = pOrder->IsAutoSuspend;
        rspOrderInsert["BusinessUnit"] = pOrder->BusinessUnit;
        rspOrderInsert["RequestID"] = pOrder->RequestID;
        rspOrderInsert["UserForceClose"] = pOrder->UserForceClose;
        rspOrderInsert["IsSwapOrder"] = pOrder->IsSwapOrder;
        rspOrderInsert["ExchangeID"] = pOrder->ExchangeID;
        rspOrderInsert["InvestUnitID"] = pOrder->InvestUnitID;
        rspOrderInsert["AccountID"] = pOrder->AccountID;
        rspOrderInsert["CurrencyID"] = pOrder->CurrencyID;
        rspOrderInsert["ClientID"] = pOrder->ClientID;
        rspOrderInsert["IPAddress"] = pOrder->IPAddress;
        rspOrderInsert["MacAddress"] = pOrder->MacAddress;
        rspOrderInsert["OrderSysID"] = pOrder->OrderSysID;
        rspOrderInsert["TradingDay"] = pOrder->TradingDay;
        rspOrderInsert["OrderStatus"] = pOrder->OrderStatus;
        rspOrderInsert["OrderType"] = pOrder->OrderType;
        rspOrderInsert["VolumeTraded"] = pOrder->VolumeTraded;
        rspOrderInsert["VolumeTotal"] = pOrder->VolumeTotal;
        rspOrderInsert["InsertDate"] = pOrder->InsertDate;
        rspOrderInsert["InsertTime"] = pOrder->InsertTime;
        std::string jsonStr = "'";
		jsonStr += writer.write(rspOrderInsert);
        Lib::trimright(jsonStr, '\n');
        Lib::trimright(jsonStr, '\r');
		jsonStr += "'";

		std::string key = m_redis->RtnOrder;	
			
		key += pOrder->BrokerID;	
		key += UNDERSCORE_FLAG;
		key += pOrder->UserID;
				
		RedisDBIdx dbi(_xredis);
		//模拟往交易发送
		bool bRet = dbi.CreateDBIndex(key.c_str(), APHash, CACHE_TYPE_1);
		if(bRet)
		{
			int64_t count = 0;
			VALUES vVal;
			vVal.push_back(jsonStr);
			if(!_xredis->rpush(dbi, key.c_str(), vVal, count))
			{
				LOG_ERROR("%s error %s", __PRETTY_FUNCTION__, dbi.GetErrInfo());
			}					
		}        
    }
}

//成交通知
void CThostTradeLink::OnRtnTrade(CThostFtdcTradeField *pTrade)
{
    printf("OnRtnTrade\n");
    if(NULL != pTrade && NULL != _xredis)
    {
		m_rtntradeMap[pTrade->UserID] += 1;
        Json::FastWriter writer;
        Json::Value rtnTrade;
		rtnTrade["Idx"]                   = m_rtntradeMap[pTrade->UserID];
        rtnTrade["BrokerID"] = pTrade->BrokerID;
        rtnTrade["InvestorID"] = pTrade->InvestorID;
        rtnTrade["InstrumentID"] = pTrade->InstrumentID;
        rtnTrade["OrderRef"] = pTrade->OrderRef;
        rtnTrade["UserID"] = pTrade->UserID;
        rtnTrade["ExchangeID"] = pTrade->ExchangeID;
        rtnTrade["TradeID"] = pTrade->TradeID;
        rtnTrade["Direction"] = pTrade->Direction;
        rtnTrade["OrderSysID"] = pTrade->OrderSysID;
        rtnTrade["ParticipantID"] = pTrade->ParticipantID;
        rtnTrade["ClientID"] = pTrade->ClientID;
        rtnTrade["TradingRole"] = pTrade->TradingRole;
        rtnTrade["ExchangeInstID"] = pTrade->ExchangeInstID;
        rtnTrade["OffsetFlag"] = pTrade->OffsetFlag;
        rtnTrade["HedgeFlag"] = pTrade->HedgeFlag;
        rtnTrade["Price"] = pTrade->Price;
        rtnTrade["Volume"] = pTrade->Volume;
        rtnTrade["TradeDate"] = pTrade->TradeDate;
        rtnTrade["TradeTime"] = pTrade->TradeTime;
        rtnTrade["TradeType"] = pTrade->TradeType;
        rtnTrade["PriceSource"] = pTrade->PriceSource;
        rtnTrade["TraderID"] = pTrade->TraderID;
        rtnTrade["OrderLocalID"] = pTrade->OrderLocalID;
        rtnTrade["ClearingPartID"] = pTrade->ClearingPartID;
        rtnTrade["BusinessUnit"] = pTrade->BusinessUnit;
        rtnTrade["SequenceNo"] = pTrade->SequenceNo;
        rtnTrade["TradingDay"] = pTrade->TradingDay;
        rtnTrade["SettlementID"] = pTrade->SettlementID;
        rtnTrade["BrokerOrderSeq"] = pTrade->BrokerOrderSeq;
        rtnTrade["TradeSource"] = pTrade->TradeSource;

        std::string jsonStr = "'";
		jsonStr += writer.write(rtnTrade);
        Lib::trimright(jsonStr, '\n');
        Lib::trimright(jsonStr, '\r');
		jsonStr += "'";
		
        string key = m_redis->RtnTrade;
        
        key += string(pTrade->BrokerID);
        key += UNDERSCORE_FLAG;
        key += string(pTrade->UserID);      
		
		RedisDBIdx dbi(_xredis);
		//模拟往交易发送
		bool bRet = dbi.CreateDBIndex(key.c_str(), APHash, CACHE_TYPE_1);
		if(bRet)
		{
			int64_t count = 0;
			VALUES vVal;
			vVal.push_back(jsonStr);
			if(!_xredis->rpush(dbi, key.c_str(), vVal, count))
			{
				LOG_ERROR("%s error %s", __PRETTY_FUNCTION__, dbi.GetErrInfo());
			}					
		}
    }
}

//合约交易状态通知
void CThostTradeLink::OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus)
{

}

void CThostTradeLink::StartWork()
{
	char stemp[1024];
	memset(stemp, 0, sizeof(stemp));
	sprintf(stemp, "%s%s", _flowpath.c_str(), _userID.c_str());
	
    m_pUserApi = CThostFtdcTraderApi::CreateFtdcTraderApi(stemp);
    m_pUserApi->RegisterSpi(this);

    m_pUserApi->SubscribePrivateTopic(THOST_TERT_RESUME);
    m_pUserApi->SubscribePublicTopic(THOST_TERT_RESUME);

    m_pUserApi->RegisterFront(Lib::stoc(_address));

    m_pUserApi->Init();
    //	m_pUserApi->Join();
    //这里由于在客户持仓查询过程中有多个查询，这些查询发送的时间要有间隔
    //防止被交易所拒绝，所以每发送一个请求要等待结果后才能发下个请求
    //如果在前一个查询应答的回调函数中发送下一个查询请求，那么就没法有一定的间隔，因为
    //堵住api线程查询不能成功	

}

void CThostTradeLink::TransReqOrderInsert(CQspFtdcInputOrderField &Order, CThostFtdcInputOrderField &CThostOrder)
{

    //交易所代码
    strncpy(CThostOrder.ExchangeID,Order.ExchangeID,sizeof(CThostOrder.ExchangeID)-1);
    //会员号
    strncpy(CThostOrder.BrokerID,Order.BrokerID,sizeof(CThostOrder.BrokerID)-1);
    //客户号
    strncpy(CThostOrder.InvestorID,Order.InvestorID,sizeof(CThostOrder.InvestorID)-1);
    //交易用户
    strncpy(CThostOrder.UserID,Order.UserID,sizeof(CThostOrder.UserID)-1);
    //合约
    strncpy(CThostOrder.InstrumentID,Order.InstrumentID,sizeof(CThostOrder.InstrumentID)-1);
    //价格类型
    CThostOrder.OrderPriceType = Order.OrderPriceType;
    //买卖方向
    CThostOrder.Direction = Order.Direction;
    //开平标志
    CThostOrder.CombOffsetFlag[0]=Order.OffsetFlag;
    //投机套保标志
    //strncpy(CThostOrder.CombHedgeFlag,Order.HedgeFlag.getValue(),sizeof(CThostOrder.CombHedgeFlag)-1);
    //CThostOrder.CombHedgeFlag[0] = Order.HedgeFlag.getValue();
    //强制转成投机
    CThostOrder.CombHedgeFlag[0] = Order.HedgeFlag;
    //价格
    CThostOrder.LimitPrice = Order.LimitPrice;
    //数量
    CThostOrder.VolumeTotalOriginal = Order.Volume;

    //本地报单号
    strncpy(CThostOrder.OrderRef, Order.UserOrderLocalID, sizeof(CThostOrder.OrderRef));
    //有效期类型
    CThostOrder.TimeCondition = Order.TimeCondition;

    // GTD日期
    strncpy(CThostOrder.GTDDate,Order.GTDDate,sizeof(CThostOrder.GTDDate)-1);

    // 成交量类型
    CThostOrder.VolumeCondition = Order.VolumeCondition;
    // 最小成交量
    CThostOrder.MinVolume = Order.MinVolume;
    // 止损价
    CThostOrder.StopPrice = Order.StopPrice;

    // 强平原因
    CThostOrder.ForceCloseReason = Order.ForceCloseReason;
    // 自动挂起标志
    CThostOrder.IsAutoSuspend = Order.IsAutoSuspend;

    //
    CThostOrder.ContingentCondition = THOST_FTDC_CC_Immediately;

    CThostOrder.IsSwapOrder = 0;

}

bool CThostTradeLink::ReqOrderInsert(int nRequestID,CQspFtdcInputOrderField &Order)
{
    bool successful=true ;
    CThostFtdcInputOrderField oFld;
	memset(&oFld, 0, sizeof(CThostFtdcInputOrderField));
    TransReqOrderInsert(Order, oFld);

    int ret = m_pUserApi->ReqOrderInsert(&oFld, nRequestID); 
    if (ret)                                                 
    {                                                        
        successful=false;             
    } 	
    return successful;	
}


bool CThostTradeLink::ReqOrderAction(int nRequestID,CQspFtdcOrderActionField &OrderAction)
{
    bool successful=true ;
    CThostFtdcInputOrderActionField oFld;
    //这里可以memset，CThostFtdcOrderActionField是一个struct
    memset(&oFld,0,sizeof(oFld));

    int ret = m_pUserApi->ReqOrderAction(&oFld, nRequestID); 			
    if (ret)		
    {
        successful=false;
        char sTemp[1024];	
        //		sprintf(sTemp,"发送撤单失败!user:%s,OrderSysId:%s,ret=%d",OrderAction.UserID.getValue(),OrderAction.OrderSysID.getValue(),ret);		

    }	
    return successful; 
}

char *CThostTradeLink::GetLocalID()
{	
    sprintf(m_sMaxLocalNo,"%012u",++m_iMaxLocalNo);
    return m_sMaxLocalNo;
}
void CThostTradeLink::SetRedis(TdRedis* redis)
{
    _xredis   = redis->xredis;
    
    m_redis = redis;
}
void CThostTradeLink::ReqContract()
{
    int iReqTimes = 5;
    printf("初始查询合约请求....\n");
    bool successful=true ;
    CThostFtdcQryInstrumentField oFld;
    memset(&oFld,0,sizeof(oFld));	
    int ret = m_pUserApi->ReqQryInstrument(&oFld, 0); 
    while (ret && iReqTimes-- > 0)
    {

        usleep(1000000);

        ret = m_pUserApi->ReqQryInstrument(&oFld, 0); 
        if (ret)
        {
            successful=false;
            char sTemp[1024];	
            sprintf(sTemp,"发送合约查询失败!");		
            printf(sTemp);
        }	
    }
    if(ret)
    {
        m_bEssentialDataLast = false;
        m_bEssentialData     = false;
    }
    else
    {
        m_bEssentialData  = m_bEssentialData ? true: false;
    }
}
void CThostTradeLink::ReqClientPosi()
{
    int iReqTimes = 5;
    printf("开始查询持仓....\n");
    CThostFtdcQryInvestorPositionField oFld;		
    memset(&oFld,0,sizeof(oFld));
    //会员代码
    strncpy(oFld.BrokerID, _brokerID.c_str(), sizeof(oFld.BrokerID));

    int ret = m_pUserApi->ReqQryInvestorPosition(&oFld, 0); 
    while (ret && iReqTimes-- > 0)
    {
        usleep(1000000);

        ret = m_pUserApi->ReqQryInvestorPosition(&oFld, 0); 
        if (ret)
        {
            char sTemp[1024];	
            sprintf(sTemp,"发送客户持仓查询失败!");	
        }
    }
    if(ret)
    {
        m_bEssentialDataLast = false;
        m_bEssentialData     = false;
    }
    else
    {
        m_bEssentialData  = m_bEssentialData ? true: false;
    }
}

void CThostTradeLink::ReqTradingCode()
{
    int iReqTimes = 5;
    printf("开始查询交易编码....\n");
    CThostFtdcQryTradingCodeField oFld;		
    memset(&oFld,0,sizeof(oFld));
    //会员代码
    strncpy(oFld.BrokerID, _brokerID.c_str(), sizeof(oFld.BrokerID));

    int ret = m_pUserApi->ReqQryTradingCode(&oFld, 0); 
    while (ret && iReqTimes-- > 0)
    {

        usleep(1000000);

        ret = m_pUserApi->ReqQryTradingCode(&oFld, 0);
        if (ret)
        {
            char sTemp[1024];	
            sprintf(sTemp,"发送交易编码查询请求失败!\n");	

        }
    }
    if(ret)
    {
        m_bEssentialDataLast = false;
        m_bEssentialData     = false;
    }
    else
    {
        m_bEssentialData  = m_bEssentialData ? true: false;
    }
}

void CThostTradeLink::ReqUserInvestor()
{
    printf("开始查询用户投资者关系....\n");
    int iReqTimes = 5;
    ///请求查询投资者
    CThostFtdcQryInvestorField oFld;		
    memset(&oFld,0,sizeof(oFld));
    strcpy(oFld.BrokerID, _brokerID.c_str());

    int ret = m_pUserApi->ReqQryInvestor(&oFld, 0); 
    while (ret && iReqTimes-- > 0)
    {

        usleep(1000000);

        ret = m_pUserApi->ReqQryInvestor(&oFld, 0);
        if (ret)
        {

        }

    }
    if(ret)
    {
        m_bEssentialDataLast = false;
        m_bEssentialData     = false;
    }
    else
    {
        m_bEssentialData  = m_bEssentialData ? true: false;
    }

}
void CThostTradeLink::ReqInvestorFee()
{
    int iReqTimes = 5;
    printf("开始查询投资者手续费....\n");
    CThostFtdcQryInstrumentCommissionRateField oFld;		
    memset(&oFld,0,sizeof(oFld));
    strcpy(oFld.BrokerID, _brokerID.c_str());	
    strcpy(oFld.InvestorID, _userID.c_str());		
    int ret = m_pUserApi->ReqQryInstrumentCommissionRate(&oFld, 0); 
    while (ret && iReqTimes-- > 0)
    {

        usleep(1000000);

        ret = m_pUserApi->ReqQryInstrumentCommissionRate(&oFld, 0);
        if (ret)
        {

        }

    }
    if(ret)
    {
        m_bEssentialDataLast = false;
        m_bEssentialData     = false;
    }
    else
    {
        m_bEssentialData  = m_bEssentialData ? true: false;
    }
}

///报单查询应答
void CThostTradeLink::OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{


};

///成交单查询应答
void CThostTradeLink::OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{


};

///可用投资者账户查询应答
void CThostTradeLink::OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{	
    if(NULL != pInvestor && NULL != _xredis)
    {
        Json::FastWriter writer;
        Json::Value userStatus;
        userStatus["TradingDay"] = pInvestor->InvestorID;
        userStatus["BrokerID"] = pInvestor->BrokerID;
        userStatus["InvestorGroupID"] = pInvestor->InvestorGroupID;
        userStatus["InvestorName"] = pInvestor->InvestorName;
        userStatus["IdentifiedCardType"] = pInvestor->IdentifiedCardType;
        userStatus["IdentifiedCardNo"] = pInvestor->IdentifiedCardNo;
        userStatus["IsActive"] = pInvestor->IsActive;
        userStatus["Telephone"] = pInvestor->Telephone;
        userStatus["Address"] = pInvestor->Address;
        userStatus["OpenDate"] = pInvestor->OpenDate;
        userStatus["Mobile"] = pInvestor->Mobile;
        userStatus["CommModelID"] = pInvestor->CommModelID;
        userStatus["MarginModelID"] = pInvestor->MarginModelID;

        std::string jsonStr = writer.write(userStatus);
        Lib::trimright(jsonStr, '\n');
        Lib::trimright(jsonStr, '\r');
        
        string key = m_redis->UserStatus;
        string field = pInvestor->BrokerID;       
        field += UNDERSCORE_FLAG;
        field += string(pInvestor->InvestorID);        
		
		RedisDBIdx dbi(_xredis);
		bool bRet = dbi.CreateDBIndex(key.c_str(), APHash, CACHE_TYPE_1);
		if(bRet)
		{
			int64_t count = 0;
			LOOP_QRYINVESTOR:
			if (!_xredis->hset(dbi, key.c_str(), field, jsonStr, count)) {
				LOG_ERROR("[%s][%s] %s error %s", key.c_str(), field.c_str(), __PRETTY_FUNCTION__, dbi.GetErrInfo());
				usleep(10);
				goto LOOP_QRYINVESTOR;
			}
		}
    }


    if(nRequestID == 0 && bIsLast)
    {
        ReqClientPosi();		
    }
};

///交易编码查询应答
void CThostTradeLink::OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if (nRequestID == 0 && bIsLast)
    {
        printf("CTP查询结束\n");
    }
    if(bIsLast)
    {
        if(m_bEssentialData)
        {
            m_bEssentialDataLast = true;
        }
    }
};

///投资者资金账户查询应答
void CThostTradeLink::OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{

};

///合约查询应答
void CThostTradeLink::OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if(NULL != pInstrument && NULL != _xredis)
    {
        //        printf("OnRspQryInstrument\n");
        Json::FastWriter writer;
        Json::Value instrument;	
        //合约中空格会导致问题
        string skeyInstrument(pInstrument->InstrumentID);
        Lib::replace(skeyInstrument, " ", "#");

        instrument["InstrumentID"] = pInstrument->InstrumentID;
        instrument["ExchangeID"] = pInstrument->ExchangeID;
        instrument["InstrumentName"] = pInstrument->InstrumentName;
        instrument["ExchangeInstID"] = pInstrument->ExchangeInstID;
        instrument["ProductID"] = pInstrument->ProductID;
        instrument["ProductClass"] = pInstrument->ProductClass;
        instrument["DeliveryYear"] = pInstrument->DeliveryYear;
        instrument["DeliveryMonth"] = pInstrument->DeliveryMonth;
        instrument["MaxMarketOrderVolume"] = pInstrument->MaxMarketOrderVolume;
        instrument["MinMarketOrderVolume"] = pInstrument->MinMarketOrderVolume;
        instrument["MaxLimitOrderVolume"] = pInstrument->MaxLimitOrderVolume;
        instrument["MinLimitOrderVolume"] = pInstrument->MinLimitOrderVolume;
        instrument["VolumeMultiple"] = pInstrument->VolumeMultiple;
        instrument["PriceTick"] = pInstrument->PriceTick;
        instrument["CreateDate"] = pInstrument->CreateDate;
        instrument["OpenDate"] = pInstrument->OpenDate;
        instrument["ExpireDate"] = pInstrument->ExpireDate;
        instrument["StartDelivDate"] = pInstrument->StartDelivDate;
        instrument["EndDelivDate"] = pInstrument->EndDelivDate;
        instrument["InstLifePhase"] = pInstrument->InstLifePhase;
        instrument["IsTrading"] = pInstrument->IsTrading;
        instrument["PositionType"] = pInstrument->PositionType;
        instrument["PositionDateType"] = pInstrument->PositionDateType;
        instrument["LongMarginRatio"] = pInstrument->LongMarginRatio;
        instrument["ShortMarginRatio"] = pInstrument->ShortMarginRatio;
        instrument["MaxMarginSideAlgorithm"] = pInstrument->MaxMarginSideAlgorithm;
        instrument["UnderlyingInstrID"] = pInstrument->UnderlyingInstrID;
        instrument["StrikePrice"] = pInstrument->StrikePrice;
        instrument["OptionsType"] = pInstrument->OptionsType;
        instrument["UnderlyingMultiple"] = pInstrument->UnderlyingMultiple;
        instrument["CombinationType"] = pInstrument->CombinationType;

        string jsonStr = "\'";
        jsonStr += writer.write(instrument);		
        Lib::trimright(jsonStr, '\n');
        Lib::trimright(jsonStr, '\r');
        jsonStr += "\'";
		
		string linstrument = m_redis->Instruments;
		string inst = pInstrument->ExchangeID;
		inst += UNDERSCORE_FLAG;
		inst += pInstrument->InstrumentID;
		
		RedisDBIdx dbi(_xredis);
		LOG_INFO("instrument:%s, %s", linstrument.c_str(), inst.c_str());
		bool bRet = dbi.CreateDBIndex(linstrument.c_str(), APHash, CACHE_TYPE_1);
		if(bRet)
		{
			int64_t count = 0;
			LOOP_INSTRUMENTS_HSET:
			if(!_xredis->hset(dbi, linstrument.c_str(), inst, jsonStr, count))
			{
				LOG_ERROR("hset [%s][%s] %s error %s", linstrument.c_str(), inst.c_str(), __PRETTY_FUNCTION__, dbi.GetErrInfo());
				usleep(10);
				goto LOOP_INSTRUMENTS_HSET;
			}
		}
		
		m_instruments = m_instruments + SPLIT_FLAG;
        m_instruments = m_instruments + pInstrument->InstrumentID;
		
        if(m_maxInstrumentsCnt > MAX_STORE_INSTRUMENTS || bIsLast)
        {	
			string lmrklist = m_redis->MrktList;
			LOG_INFO("market list:%s %s", lmrklist.c_str(), m_instruments.c_str());
			bRet = dbi.CreateDBIndex(lmrklist.c_str(), APHash, CACHE_TYPE_1);
			if(bRet)
			{
				int64_t count = 0;
				VALUES vVal;
				vVal.push_back(m_instruments);
				LOOP_INSTRUMENT_RPUSH:
				if(!_xredis->rpush(dbi, lmrklist.c_str(), vVal, count))
				{
					LOG_ERROR("[%s] rpush %s error %s", lmrklist.c_str(), __PRETTY_FUNCTION__, dbi.GetErrInfo());
					usleep(10);
					goto LOOP_INSTRUMENT_RPUSH;
				}
				m_instruments.clear();
                m_maxInstrumentsCnt = 0;
			}
		}
        
        m_maxInstrumentsCnt++;
    }


    if (nRequestID == 0 && bIsLast)
    {
        ReqUserInvestor();
    }
};

///投资者持仓查询应答
void CThostTradeLink::OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pRspInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast)
{
    if(NULL != pRspInvestorPosition && NULL != _xredis)
    {
        Json::FastWriter writer;
        Json::Value clientpostion;
        clientpostion["InstrumentID"] = pRspInvestorPosition->InstrumentID;
        clientpostion["BrokerID"] = pRspInvestorPosition->BrokerID;	
        clientpostion["InvestorID"] = pRspInvestorPosition->InvestorID;
        clientpostion["PosiDirection"] = pRspInvestorPosition->PosiDirection;
        clientpostion["HedgeFlag"] = pRspInvestorPosition->HedgeFlag;
        clientpostion["PositionDate"] = pRspInvestorPosition->PositionDate;
        clientpostion["YdPosition"] = pRspInvestorPosition->YdPosition;
        clientpostion["Position"] = pRspInvestorPosition->Position;
        clientpostion["LongFrozen"] = pRspInvestorPosition->LongFrozen;
        clientpostion["ShortFrozen"] = pRspInvestorPosition->ShortFrozen;
        clientpostion["LongFrozenAmount"] = pRspInvestorPosition->LongFrozenAmount;
        clientpostion["ShortFrozenAmount"] = pRspInvestorPosition->ShortFrozenAmount;
        clientpostion["OpenVolume"] = pRspInvestorPosition->OpenVolume;
        clientpostion["CloseVolume"] = pRspInvestorPosition->CloseVolume;
        clientpostion["OpenAmount"] = pRspInvestorPosition->OpenAmount;
        clientpostion["CloseAmount"] = pRspInvestorPosition->CloseAmount;
        clientpostion["PositionCost"] = pRspInvestorPosition->PositionCost;
        clientpostion["PreMargin"] = pRspInvestorPosition->PreMargin;
        clientpostion["UseMargin"] = pRspInvestorPosition->UseMargin;
        clientpostion["FrozenMargin"] = pRspInvestorPosition->FrozenMargin;
        clientpostion["FrozenCash"] = pRspInvestorPosition->FrozenCash;
        clientpostion["FrozenCommission"] = pRspInvestorPosition->FrozenCommission;
        clientpostion["CashIn"] = pRspInvestorPosition->CashIn;
        clientpostion["Commission"] = pRspInvestorPosition->Commission;
        clientpostion["CloseProfit"] = pRspInvestorPosition->CloseProfit;
        clientpostion["PositionProfit"] = pRspInvestorPosition->PositionProfit;
        clientpostion["PreSettlementPrice"] = pRspInvestorPosition->PreSettlementPrice;
        clientpostion["SettlementPrice"] = pRspInvestorPosition->SettlementPrice;
        clientpostion["TradingDay"] = pRspInvestorPosition->TradingDay;
        clientpostion["SettlementID"] = pRspInvestorPosition->SettlementID;
        clientpostion["OpenCost"] = pRspInvestorPosition->OpenCost;
        clientpostion["ExchangeMargin"] = pRspInvestorPosition->ExchangeMargin;
        clientpostion["CombPosition"] = pRspInvestorPosition->CombPosition;
        clientpostion["CombLongFrozen"] = pRspInvestorPosition->CombLongFrozen;
        clientpostion["CombShortFrozen"] = pRspInvestorPosition->CombShortFrozen;
        clientpostion["CloseProfitByDate"] = pRspInvestorPosition->CloseProfitByDate;
        clientpostion["CloseProfitByTrade"] = pRspInvestorPosition->CloseProfitByTrade;
        clientpostion["TodayPosition"] = pRspInvestorPosition->TodayPosition;
        clientpostion["MarginRateByMoney"] = pRspInvestorPosition->MarginRateByMoney;
        clientpostion["MarginRateByVolume"] = pRspInvestorPosition->MarginRateByVolume;
        clientpostion["StrikeFrozen"] = pRspInvestorPosition->StrikeFrozen;
        clientpostion["StrikeFrozenAmount"] = pRspInvestorPosition->StrikeFrozenAmount;
        clientpostion["AbandonFrozen"] = pRspInvestorPosition->AbandonFrozen;

        std::string jsonStr = writer.write(clientpostion);
        Lib::trimright(jsonStr, '\n');
        Lib::trimright(jsonStr, '\r');
		
        string positionkey = m_redis->ClientPosition;
        string positionfield = pRspInvestorPosition->BrokerID;       
        positionfield += UNDERSCORE_FLAG;
        positionfield += string(pRspInvestorPosition->InvestorID);
        positionfield += UNDERSCORE_FLAG;
        positionfield += string(pRspInvestorPosition->InstrumentID);
        positionfield += UNDERSCORE_FLAG;
        positionfield += pRspInvestorPosition->PosiDirection;
		
		RedisDBIdx dbi(_xredis);
		bool bRet = dbi.CreateDBIndex(positionkey.c_str(), APHash, CACHE_TYPE_1);
		if(bRet)
		{
			LOOP_QRYPOSITION:
			int64_t count = 0;
			if (!_xredis->hset(dbi, positionkey.c_str(), positionfield, jsonStr, count)) {
				LOG_ERROR("[%s][%s] %s error %s", positionkey.c_str(), positionfield.c_str(), __PRETTY_FUNCTION__, dbi.GetErrInfo());
				usleep(10);
				goto LOOP_QRYPOSITION;
			}
		}
    }
    if (nRequestID == 0 && bIsLast)
    {		 
        ReqTradingCode();
    }
};



///投资者手续费率查询应答
void CThostTradeLink::OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{

};

///投资者保证金率查询应答
void CThostTradeLink::OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast) 
{

};

