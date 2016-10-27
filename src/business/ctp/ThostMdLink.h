#ifndef THOST_QUOT_LINK_H
#define THOST_QUOT_LINK_H
#include "ThostFtdcMdApi.h"
#include "BaseExchApi.h"

#define MAX_STORE_MARKETLIST_CNT       60
class CThostMdLink: public CThostFtdcMdSpi, public CBaseExchApi
{
    public:
        CThostMdLink(ApiExchLink* mdlink);
        ~CThostMdLink();

        void OnFrontConnected();
        void OnFrontDisconnected(int nReason);
        void OnRspUserLogin(CThostFtdcRspUserLoginField *pRspUserLogin, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
        void OnRspError(CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);
        void OnRtnDepthMarketData(CThostFtdcDepthMarketDataField *pDepthMarketData);

        ///订阅行情应答
        void OnRspSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

        ///取消订阅行情应答
        void OnRspUnSubMarketData(CThostFtdcSpecificInstrumentField *pSpecificInstrument, CThostFtdcRspInfoField *pRspInfo, int nRequestID, bool bIsLast);

        ///订阅行情。
        ///@param ppInstrumentID 合约ID  
        ///@param nCount 要订阅/退订行情的合约个数
        ///@remark 
        int SubMarketData(char *ppInstrumentID[], int nCount);

        ///退订行情。
        ///@param ppInstrumentID 合约ID  
        ///@param nCount 要订阅/退订行情的合约个数
        ///@remark 
        int UnSubMarketData(char *ppInstrumentID[], int nCount);

        void StartWork();

        void SetRedis(MdRedis* redis);

        bool ReqLogin(string BrokerID, string UserID, string Password);

        void SetQuot(vector<string> v);

        vector<string> GetQuot(string storePath);
        void StoreQuot(string storePath);

    protected:
        void Login();     
    private:
        CThostFtdcMdApi *m_pUserApi;
        MdRedis* m_redis;

        string _env;	
        string _channel;
        string _snapshot;
        string _tick;
        string _mrklist;
        bool   _isTick;		
};

#endif
