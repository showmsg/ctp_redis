//////////////////////////////////////////////////////////////////////////
// 文件: ExchangeLinkManager.h
// 功能: 定义了报盘管理
// 历史: 20150525 huwp 
//////////////////////////////////////////////////////////////////////////
#if !defined(EXCHANGE_API_MANAGER_H_20121119)
#define EXCHANGE_API_MANAGER_H_20121119

#include "ThostTradeLink.h"
#include "ThostMdLink.h"


typedef map<string, CBaseExchApi*> ExchLinkMap;
typedef map<string, int>           ExchStatusMap;
class CGateLinkManager
{
public:
	
	CGateLinkManager();
	virtual ~CGateLinkManager();
	
	void Init(LinkManager pLink);
	
	void StartTrade(TdRedis* redis);
	void StartMarket(MdRedis* redis);
	//启动各交易所报盘
	void StartTrade(ApiExchLink* pLink, TdRedis* redis);
	void StartMarket(ApiExchLink* pLink, MdRedis* redis);
	CBaseExchApi* GetTrade(string userID, int isTrade);
	CBaseExchApi* GetMarket(string group);
private:
	

private:	
	CBaseExchApi*               m_baseApi;
	LinkManager                 m_linkManager;
	ExchLinkMap                 m_exchLinkMap;
	ExchStatusMap               m_exchStatusMap;
};


#endif
