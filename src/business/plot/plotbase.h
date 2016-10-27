#ifndef _PLOT_BASE__
#define _PLOT_BASE__
#include "Redis.h"

typedef struct plotRedis
{
    xRedisClient* xredis;     ///发布句柄   
    string Env;               ///环境
    string Channel;           ///行情订阅,psub
    string Snapshot;          ///行情快照, set/get
    string Tick;              ///行情分时, lpush/lpop
    string UserStatus;        ///用户状态
    string RtnOrder;          ///订单回报
    string RtnTrade;          ///成交回报
    string RspOrderInsert;    ///订单响应
    string RspOrderAction;    ///撤单响应
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
    protected:

};

#endif
