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

}
//撤单响应，CTP一般出错才会响应到Rsp
bool CPlotBase::OnRspOrderAction(Json::Value root)
{

	LOG_INFO("OnRspOrderAction %s", root["ErrorMsg"].asString().c_str());

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
	
	if(IMSG_TYPE_RTNTRADE == root["itype"].asInt())
	{
		LOG_INFO("RtnTrade");
	}
	return true;
}
		