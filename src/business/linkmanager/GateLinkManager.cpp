#include "GateLinkManager.h"

CGateLinkManager::CGateLinkManager()
{	
   m_baseApi = NULL;
}

CGateLinkManager::~CGateLinkManager()
{
	
}

void CGateLinkManager::Init(LinkManager pLink)
{
	m_linkManager = pLink;
	string key = "";
	for(int i = 0; i < pLink.size(); i++)
	{
		ApiExchLink link = pLink[i];
		
		if(link.isTrade)
		{	
			key = link.UserID + "#";
			key += link.isTrade;
			ExchLinkMap::iterator it = m_exchLinkMap.find(key);
			if(it == m_exchLinkMap.end())
			{
				m_baseApi = new CThostTradeLink(&link);
				m_exchLinkMap.insert(make_pair(key, m_baseApi));
			}			
		}
		else
		{
			key = link.MrktGroup;
			ExchLinkMap::iterator it = m_exchLinkMap.find(key);
			if(it == m_exchLinkMap.end())
			{
				m_baseApi = new CThostMdLink(&link);
				m_exchLinkMap.insert(make_pair(key, m_baseApi));
			}
		}
	} 
}
//启动各交易所报盘

void CGateLinkManager::StartTrade(TdRedis* redis)
{
	string key;
	for(int i = 0; i < m_linkManager.size(); i++)
	{
		ApiExchLink link = m_linkManager[i];
		if(link.isTrade)
		{
			key = link.UserID + "#";
			key += link.isTrade;
			ExchStatusMap::iterator it = m_exchStatusMap.find(key);
			if(it == m_exchStatusMap.end())
			{
				StartTrade(&link, redis);
			}
			
		}
	}
}

void CGateLinkManager::StartMarket(MdRedis* redis)
{
	string key;
	for(int i = 0; i < m_linkManager.size(); i++)
	{
		ApiExchLink link = m_linkManager[i];
		if(!link.isTrade)
		{
			key = link.MrktGroup;
			ExchStatusMap::iterator it = m_exchStatusMap.find(key);
			if(it == m_exchStatusMap.end())
			{
				StartMarket(&link, redis);
			}			
		}
	}
}
void CGateLinkManager::StartTrade(ApiExchLink* pLink, TdRedis* redis)
{
	string key = "";
	if(!pLink->isTrade)
	{
		LOG_ERROR("报盘机启动参数不正确 [%s]", pLink->UserID.c_str());
		return;
	}
	key    = pLink->UserID + "#";
	key   += pLink->isTrade;
	
    
	ExchLinkMap::iterator it = m_exchLinkMap.find(key);
	if(it != m_exchLinkMap.end())
	{
		m_baseApi = it->second;
		m_baseApi->SetRedis(redis);
		m_baseApi->StartWork();
		m_exchStatusMap.insert(make_pair(key, true));
	}
}
//启动各交易所报盘
void CGateLinkManager::StartMarket(ApiExchLink* pLink, MdRedis* redis)
{
	string key = "";
	if(pLink->isTrade)
	{
		LOG_ERROR("报盘机启动参数不正确 [%s]", pLink->UserID.c_str());
		return;
	}
	key    = pLink->MrktGroup;	
    
	ExchLinkMap::iterator it = m_exchLinkMap.find(key);
	if(it != m_exchLinkMap.end())
	{
		m_baseApi = it->second;
		
		vector<string> instruments = m_baseApi->GetQuot(pLink->MrktList);

		m_baseApi->SetQuot(instruments);
	
		m_baseApi->SetRedis(redis);
		m_baseApi->StartWork();
		m_exchStatusMap.insert(make_pair(key, true));
	}
}
CBaseExchApi* CGateLinkManager::GetTrade(string userID, int isTrade)
{
	string key = "";
	key    = userID + "#";
	key   += isTrade;
	
	ExchLinkMap::iterator it = m_exchLinkMap.find(key);
	if(it != m_exchLinkMap.end())
	{
		m_baseApi = it->second;
		return m_baseApi;
	}
	return NULL;
}

CBaseExchApi* CGateLinkManager::GetMarket(string group)
{
	
	ExchLinkMap::iterator it = m_exchLinkMap.find(group);
	if(it != m_exchLinkMap.end())
	{
		m_baseApi = it->second;
		return m_baseApi;
	}
	return NULL;
}


