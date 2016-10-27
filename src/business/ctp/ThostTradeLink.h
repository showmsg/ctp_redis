#ifndef __CTHostTRADE_LINK_H
#define __CTHostTRADE_LINK_H

#include "ThostFtdcTraderApi.h"
#include "ThostFtdcUserApiStruct.h"
#include "BaseExchApi.h"
#include "Logger.h"
#include "Redis.h"

class CThostTradeLink : public CThostFtdcTraderSpi, public CBaseExchApi
{
    public:
        CThostTradeLink(ApiExchLink *api);
        ~CThostTradeLink();
        //连接
	void OnFrontConnected();
	void OnFrontDisconnected(int nReason);
	//登录
	void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	//密码修改应答
	void OnRspUserPasswordUpdate(CThostFtdcUserPasswordUpdateField *pUserPasswordUpdate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast){};

	//报单
	void OnRspOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnErrRtnOrderInsert(CThostFtdcInputOrderField *pInputOrder, CThostFtdcRspInfoField *pRspInfo);
	//撤单
	void OnRspOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	void OnErrRtnOrderAction(CThostFtdcOrderActionField *pOrderAction, CThostFtdcRspInfoField *pRspInfo);

	//报单通知
	void OnRtnOrder(CThostFtdcOrderField *pOrder);
	//成交通知
	void OnRtnTrade(CThostFtdcTradeField *pTrade);

	//合约交易状态通知
	void OnRtnInstrumentStatus(CThostFtdcInstrumentStatusField *pInstrumentStatus);
    ///投资者结算结果确认响应
	virtual void OnRspSettlementInfoConfirm(CThostFtdcSettlementInfoConfirmField *pSettlementInfoConfirm, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
    //查询应答
	///报单查询应答
	virtual void OnRspQryOrder(CThostFtdcOrderField *pOrder, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///成交单查询应答
	virtual void OnRspQryTrade(CThostFtdcTradeField *pTrade, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///请求查询投资者响应
	virtual void OnRspQryInvestor(CThostFtdcInvestorField *pInvestor, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询交易编码响应
	virtual void OnRspQryTradingCode(CThostFtdcTradingCodeField *pTradingCode, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	
	///请求查询资金账户响应
	virtual void OnRspQryTradingAccount(CThostFtdcTradingAccountField *pTradingAccount, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	
	///请求查询合约响应
	virtual void OnRspQryInstrument(CThostFtdcInstrumentField *pInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	///请求查询投资者持仓响应
	virtual void OnRspQryInvestorPosition(CThostFtdcInvestorPositionField *pInvestorPosition, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
	
	///请求查询合约手续费率响应
	virtual void OnRspQryInstrumentCommissionRate(CThostFtdcInstrumentCommissionRateField *pInstrumentCommissionRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

	
	///请求查询合约保证金率响应
	virtual void OnRspQryInstrumentMarginRate(CThostFtdcInstrumentMarginRateField *pInstrumentMarginRate, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
public:
	void StartWork();
    char *GetLocalID();
	void SetRedis(TdRedis* redis);
    	///报单
	bool ReqOrderInsert(int nRequestID,CQspFtdcInputOrderField &Order);
	///撤单
	bool ReqOrderAction(int nRequestID,CQspFtdcOrderActionField &OrderAction);
	bool ReqLogin(int nRequestID,CQspFtdcReqUserLoginField &ReqLoginField);
	
protected:
	void Login();

private:
	void TransReqOrderInsert(CQspFtdcInputOrderField &Order, CThostFtdcInputOrderField &CThostOrder);
private:
    void ReqContract();
	void ReqClientPosi();
	void ReqTradingCode();
	void ReqUserInvestor();
	
	void ReqInvestorFee();
    //投资者结算结果确认
	void ReqSettlementInfoConfirm();
private:
    CThostFtdcTraderApi *m_pUserApi;
	TdRedis* m_redis;
	string m_instruments;
	int m_maxInstrumentsCnt;
	
};

#endif
