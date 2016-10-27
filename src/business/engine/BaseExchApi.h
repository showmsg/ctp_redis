#ifndef BaseExchApi_H
#define BaseExchApi_H
#include "xRedisClient.h"
#include "global.h"
#include "QspFtdcUserApiDataType.h"
#include "QspFtdcUserApiStruct.h"
#include "json/json.h"

//缓存下，减少行情频繁订阅带来的问题
#define MAX_STORE_INSTRUMENTS      60

typedef struct apiExchLink
{
    string BrokerID;
    string UserID;
    string Password;
    string Address;
    string FlowPath;
	string MrktList;
	string MrktGroup;
	int    TopicID;
	bool   isTrade;
}ApiExchLink;

typedef vector<apiExchLink> LinkManager;
typedef struct mdRedis
{
    xRedisClient* xredis;       ///xredis连接
    string Env;                 ///环境
    string Channel;             ///订阅频道 publish
    string Snapshot;            ///行情快照 set 
    bool   isTick;              ///行情快照是否打开
    string Tick;                ///行情分时, lpush
    string MrktList;            ///行情订阅列表
    string MrktListStore;       ///行情订阅列表存放位置
}MdRedis;

typedef struct tdRedis
{
    xRedisClient* xredis;       ///xredis连接
    string Env;                 ///环境
    string Channel;             ///订阅频道,publish
    string Tick;                ///分时行情,lpush
    string Snapshot;            ///行情快照, set
    string UserStatus;          ///用户状态
    string RtnOrder;            ///订单回报
    string RtnTrade;            ///成交回报
    string RspOrderInsert;      ///订单响应
    string RspOrderAction;      ///撤单响应
    string ClientPosition;      ///持仓
    string Instruments;         ///合约
    string ClientReq;           ///客户请求队列
    string MrktList;            ///行情订阅列表
}TdRedis;

class CBaseExchApi
{
    public:
        CBaseExchApi()
        {
            _xredis   = NULL;
            m_iReqSeqNo = 0;
            m_bEssentialData     = false;
            m_bEssentialDataLast = false;
        };

        virtual ~CBaseExchApi()
        {

        };

        virtual bool ReqOrderInsert(int nRequestID, CQspFtdcInputOrderField &Order){ return true;};
        virtual bool ReqOrderAction(int nRequestID, CQspFtdcOrderActionField &OrderAction){return true;};
        virtual bool ReqLogin(int nRequestID, CQspFtdcReqUserLoginField &ReqLoginField){return true;};
        virtual int SubMarketData(char *ppInstrumentID[], int nCount){return 0;};	

        virtual int UnSubMarketData(char *ppInstrumentID[], int nCount){return 0;};	

        virtual char *GetLocalID(){return NULL;};
        virtual void StartWork(){};

        virtual void SetRedis(MdRedis* redis){};
        virtual void SetRedis(TdRedis* redis){};
		
		virtual void SetQuot(vector<string> v){};

        virtual vector<string> GetQuot(string storePath){ vector<string> v; return v;};
        virtual void StoreQuot(string storePath){};
    public:
        bool m_bEssentialDataLast;              ///是否查询完毕
    public:
        bool m_bEssentialData;                  ///临时变量
    protected:
        xRedisClient*  _xredis;
         
        string _brokerID;
        string _userID;
        string _password;	
        string _address;
        string _flowpath;
		int _topic;

        int    m_iReqSeqNo;
        int  m_iMaxLocalNo;
        char m_sMaxLocalNo[50];	
		
};

#endif
