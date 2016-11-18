#include "plotbase.h"
#include "Logger.h"

CPlotBase::CPlotBase()
{
	
}

CPlotBase::~CPlotBase()
{
	
}
bool CPlotBase::SendOrder(Json::Value root)
{
	return true;
}

//订单响应，CTP一般只有出错才会返回响应
bool CPlotBase::OnRspOrderInsert(Json::Value root)
{
	LOG_INFO("OnRspOrderInsert %s", root["ErrorMsg"].asString().c_str());
	
	///处理因报单失败促发的策略操作
	
}
//撤单响应，CTP一般出错才会响应到Rsp
bool CPlotBase::OnRspOrderAction(Json::Value root)
{

	LOG_INFO("OnRspOrderAction %s", root["ErrorMsg"].asString().c_str());
	
	///处理因撤单失败促发的策略操作
	
	return true;
}
//报撤单响应
bool CPlotBase::OnRtnOrder(Json::Value root)
{
	LOG_INFO("RtnOrder");
	switch(root["OrderStatus"].asInt())
	{
		//全部成交
		case OS_AllTraded:
		//部分成交
		case OS_PartTradedQueueing:
		//未成交
		case OS_NoTradeQueueing:
		{
			///策略处理报单响应对应的处理，此处的成交数量不要作为最终成交，最终成交需要等收到成交后重新计算
		}
		break;
		//部分成交不在队列中
		case OS_PartTradedNotQueueing:
		break;
		//未成交不在队列中
		case OS_NoTradeNotQueueing:
		break;
		//撤单
		case OS_Canceled:
		{
			///处理撤单响应策略
		}
		break;
		default:
		break;
	}
	
	return true;
}
//成交响应
bool CPlotBase::OnRtnTrade(Json::Value root)
{
	LOG_INFO("RtnTrade");
	///所有成交促发策略都应该在此处处理，并计算报单成交数量

	return true;
}
		