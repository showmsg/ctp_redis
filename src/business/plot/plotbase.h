#ifndef _PLOT_BASE__
#define _PLOT_BASE__
#include "global.h"
#include "BaseExchApi.h"

typedef struct plotRedis
{
    xRedisClient* xredis;     ///发布句柄   
    string Env;               ///环境
    string Channel;           ///行情订阅,psub
    string Snapshot;          ///行情快照, set/get
    string Tick;              ///行情分时, lpush/lpop
    string UserStatus;        ///用户状态
    string Response;          ///订单回报\成交回报\订单响应\撤单响应    
    string ClientPosition;    ///持仓
    string Account;			  ///资金
    string Instruments;       ///合约
    string ClientReq;         ///客户请求队列
    string RouterMsg;         ///策略路由来消息
    string Unique;            ///进程唯一标识
    string Group;             ///进程所属分组
}PlotRedis;

class CPlotBase
{
    public:
        CPlotBase();
        virtual ~CPlotBase();
		bool SendOrder(Json::Value root);
		//订单响应，CTP一般只有出错才会返回响应
		bool OnRspOrderInsert(Json::Value root);
		//撤单响应，CTP一般出错才会响应到Rsp
		bool OnRspOrderAction(Json::Value root);
		//报撤单响应
		bool OnRtnOrder(Json::Value root);
		//成交响应
		bool OnRtnTrade(Json::Value root);
    protected:

};

#endif
