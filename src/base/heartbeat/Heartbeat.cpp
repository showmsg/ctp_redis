/*********************************************************************
*
* 文件名称：Heartbeat.cxx
* 摘    要：跨Windows和Linux平台的Heartbeat类
*
* 当前版本：0.1
* 作    者：Jaxon Jia
* 创建日期：2013/07/24
*
* 修改历史：
*   |     Date    |  Programmer |  Description 
*   |             |             | 
*********************************************************************/

#ifndef __Heartbeat__
#define __Heartbeat__

#include "Heartbeat.h"

Heartbeat::Heartbeat(void)
{
}

Heartbeat::Heartbeat(HBRUNTYPE hb_type, 
					 const char* ip, 
					 u_int port/*=DEFAULT_PORT*/, 
					 u_int interval/*=INTERVAL_SLEEP*/, 
					 u_int tolerance/*=TOLERANCE*/)
{
	init(hb_type, ip, port, interval, tolerance);
}

Heartbeat::~Heartbeat(void)
{
	closesock(m_sock);
}

/*********************************************************************
* 函数名称: init
* 函数描述: 初始化
* 参    数: 
*			[IN]ip			const char *	IP地址
*			[IN]port		u_int			端口
*			[IN]interval	u_int			发送心跳包的间隔
*			[IN]tolerance	u_int			心跳超时间隔时间
* 返 回 值: N/A
* 创    建: Jaxon Jia (sz082169)
* 创建日期: 2013/07/24
*********************************************************************/
void Heartbeat::init(HBRUNTYPE hb_type, const char* ip, u_int port, u_int interval, u_int tolerance)
{
	m_hb_type = hb_type;
	strcpy(m_ip, ip);
	m_port = port;
	m_interval = interval;
	m_tolerance = tolerance;

	init_sock();
}

/*********************************************************************
* 函数名称: send_msg
* 函数描述: 消息发送函数 
* 参    数: 
*			[IN]type	HBMSGTYPE		消息类型
*			[IN]content	const char *	消息内容
*			[IN]len		u_int			消息内容的长度
* 返 回 值: 发送成功返回0，否则返回负值
* 创    建: Jaxon Jia (sz082169)
* 创建日期: 2013/07/24
*********************************************************************/
int Heartbeat::send_msg(HBMSGTYPE type, const char* content, u_int len)
{
	u_int pkt_len = sizeof(HBMSG) + len;
	HBMSG* msg = (HBMSG*)malloc(pkt_len);
	msg->type = type;
	msg->timestamp = cur_time();
	msg->len = pkt_len;
	memcpy(msg->content, content, len);
	msg->content[len] = '\0';

	struct sockaddr_in saddrsend = {0};

	saddrsend.sin_family = AF_INET;
	saddrsend.sin_port = htons(m_port);
	saddrsend.sin_addr.s_addr = inet_addr(m_ip);

	int sendlen = sendto(m_sock, (char*)msg, pkt_len, 0, (struct sockaddr*)&saddrsend, sizeof(saddrsend));
	free(msg);
	if (sendlen < 0)
	{
		TRACE("Heartbeat -- Socket send error! ERR:%d", errno);			
		return HB_ERR_SOCK_SEND;
	}
	TRACE("Heartbeat -- Send %d byte.", sendlen);	
	return HB_OK;
}

int Heartbeat::run()
{
	return new_thread(threadfunc, this);
}

/*********************************************************************
* 函数名称: as_client
* 函数描述: 作为客户端运行时的心跳线程函数, as_client和as_server互斥 
* 参    数: N/A
* 返 回 值: N/A
* 创    建: Jaxon Jia (sz082169)
* 创建日期: 2013/07/25
*********************************************************************/
int Heartbeat::as_client()
{
	TRACE("Heartbeat -- Send to IP:Port = %s:%d!", m_ip, m_port);
	while (true)
	{// 定时发送心跳
		send_msg(HB_MSG_RUNNING, "Heartbeat", strlen("Heartbeat"));
		TRACE("Heartbeat -- Send Heartbeat!");
		//callback();	// 回调处理
		mysleep(m_interval);
	}

	return HB_OK;
}

/*********************************************************************
* 函数名称: as_server
* 函数描述: 作为服务端运行时的心跳线程函数, as_client和as_server互斥
* 参    数: N/A
* 返 回 值: N/A
* 创    建: Jaxon Jia (sz082169)
* 创建日期: 2013/07/25
*********************************************************************/
int Heartbeat::as_server()
{
	TRACE("Heartbeat -- Listening IP:Port = %s:%d!", m_ip, m_port);

	fd_set read_set;
	char recvbuf[HB_BUF_SIZE] = {0};

	sockaddr_in src_sin = {0};
	socklen_t src_len = sizeof(src_sin);

	while (true)
	{
		FD_ZERO(&read_set);
		FD_SET(m_sock, &read_set);
		struct timeval timeout;
		timeout.tv_sec = 3;
		timeout.tv_usec = 0;

		int ret = select(m_sock + 1, &read_set, NULL, NULL, &timeout);

		if (0 == ret)
		{
			TRACE("Heartbeat -- Recivie udp packet timeout.");
		}
		else if (ret < 0)
		{
			TRACE("Heartbeat -- Select socket failed! Error: %d.", errno);
			return -1;
		}
		else if (ret > 0 && FD_ISSET(m_sock, &read_set))
		{
			memset(recvbuf, 0, sizeof(recvbuf));
			int recvlen = recvfrom(m_sock, recvbuf, HB_BUF_SIZE, 0, (sockaddr*)&src_sin, &src_len); 
			if (recvlen < 0)
			{
				TRACE("Heartbeat -- recv socket failed! Error: %s\n", strerror(errno));
			}
			else if (0 == recvlen)
			{
				continue;
			}
			else
			{
				callback((HBMSG*)recvbuf, &src_sin);	// 回调处理
			}
		}//end of else if (ret > 0 && FD_ISSET(m_sock, &read_set))
	}

	return HB_OK;
}

/*********************************************************************
* 函数名称: callback
* 函数描述: 线程回调函数 
* 参    数: 
*			[IN]msg		HBMSG *		发送或接收到的消息
*			[IN]src_sin	sockaddr_in	发送或接收的IP,Port信息
* 返 回 值: N/A
* 创    建: Jaxon Jia (sz082169)
* 创建日期: 2013/07/25
*********************************************************************/
void* Heartbeat::callback(HBMSG* msg, sockaddr_in *src_sin)
{
	if (m_hb_type == HB_CLIENT)
	{
	}
	else
	{
		char *ip = inet_ntoa(src_sin->sin_addr);
		u_int port = src_sin->sin_port;
		int len = msg->len - sizeof(HBMSG);		
		char descript[HB_NODE_DESCRIPT] = {0};		
		memcpy(descript, msg->content, MIN(HB_NODE_DESCRIPT, len));
		int n = node_list.size();
		switch (msg->type)
		{
		case HB_MSG_REG:
			TRACE("Heartbeat -- Recv node register message!");
			TRACE("Heartbeat -- IP:PORT = %s:%d, descript: %s", ip, port, descript);
			if (node_list.size() < HB_MAX_NODE_COUNT)
			{
				NODE node;
				strcpy(node.ip, ip);
				node.port = port;
				node.timestamp = msg->timestamp;
				node.islive = 1;
				node.descript = descript;
				node_list.push_back(node);
			}
			else
			{
				TRACE("Heartbeat -- node list size greater than HB_MAX_NODE_COUNT!");
			}
			break;
		case HB_MSG_RUNNING:
			TRACE("Heartbeat -- Recv Heartbeat message!");
			for (int i = 0; i < n; i++)
			{
				if (node_list[i].ip == ip && node_list[i].port == port)
				{
					if (msg->timestamp - node_list[i].timestamp > m_tolerance)
					{
						TRACE("Heartbeat -- Node %s:%u is dead! recv timestamp: %ll, last timestamp: %ll", 
							ip, port, msg->timestamp, node_list[i].timestamp);
						node_list[i].islive = 0;
					} 

					node_list[i].timestamp = msg->timestamp;
					break;
				}
			}
			break;
		case HB_MSG_QUIT:
			TRACE("Heartbeat -- Recv node exit message!");
			for (int i = 0; i < n; i++)
			{
				if (node_list[i].ip == ip && node_list[i].port == port)
				{				
					node_list[i].islive = 0;
					break;
				}
			}
			break;
		}
	}

	return (void*)HB_OK;
}

// 线程函数
#ifdef WIN32
void Heartbeat::threadfunc(void *param)
#else
void* Heartbeat::threadfunc(void *param)
#endif
{
	Heartbeat* hb = (Heartbeat*)param;

	if (hb->m_hb_type == HB_CLIENT)
	{
		hb->as_client();
	}
	else
	{
		hb->as_server();
	}
}

// 获取当前时间,精确到秒
time_t Heartbeat::cur_time()
{
	return time(NULL);
}

// socket初始化
int Heartbeat::init_sock()
{
#ifdef WIN32
	WSADATA wsad; 
	if (WSAStartup(MAKEWORD(2,2),&wsad) != 0)			
	{
		TRACE("Heartbeat -- Socket init error!");			
		return HB_ERR_SOCK_INIT;
	}
#endif

	struct sockaddr_in local_sock;

	if ((m_sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0)
	{
		TRACE("Heartbeat -- Socket init error!");
		return HB_ERR_SOCK_INIT;
	}	

	if (inet_pton(AF_INET|AF_INET6, m_ip, &local_sock.sin_addr) < 0)
	{
		TRACE("Heartbeat -- Invalid ip address!");
		return HB_ERR_INVALID_PARAM;
	}

	memset(&local_sock, 0, sizeof(local_sock));
	local_sock.sin_family = AF_INET;

	if (m_hb_type == HB_CLIENT)
	{
		local_sock.sin_port = INADDR_ANY;
		local_sock.sin_addr.s_addr = INADDR_ANY;
	} 
	else
	{
		local_sock.sin_port = htons(m_port);
		local_sock.sin_addr.s_addr = inet_addr(m_ip);
	}	

	int reuse = 1;
	int res = setsockopt(m_sock, SOL_SOCKET, SO_REUSEADDR, (char*)&reuse, sizeof(int));
	if (res < 0)
	{
		TRACE("Heartbeat -- Error to set reuse socket.");
		return HB_ERR_SOCK_SETOPT;
	}

	res = bind(m_sock, (sockaddr*)(&local_sock), sizeof(local_sock));
	if (res < 0)
	{
		TRACE("Heartbeat -- Error to bind socket.");
		return HB_ERR_SOCK_BIND;
	}

	int bufszie = HB_BUF_SIZE;
	int sock_opt = (m_hb_type == HB_CLIENT) ? SO_SNDBUF : SO_RCVBUF;
	res = setsockopt(m_sock, SOL_SOCKET, sock_opt, (char*)&bufszie, sizeof(int));
	if (res < 0)
	{
		TRACE("Heartbeat -- Error to set socket buffer size.");
		return HB_ERR_SOCK_SETOPT;
	}

	if (ntohl(inet_addr(m_ip)) > 0xe0000000 && ntohl(inet_addr(m_ip)) < 0xefffffff)
	{// multicast address
		struct ip_mreq mreq = {0};
		mreq.imr_multiaddr.s_addr = inet_addr(m_ip);
		mreq.imr_interface.s_addr = INADDR_ANY;

		res = setsockopt(m_sock, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mreq, sizeof(mreq));
		if(res < 0 )
		{
			TRACE("Heartbeat -- Error to add membership.");
			return HB_ERR_SOCK_SETOPT;
		}
	}

	return HB_OK;
}

//============= 下面是跨平台相关函数 ================

// 延时函数
void Heartbeat::mysleep(u_int ms)
{
#ifdef WIN32
	Sleep(ms);
#else
	usleep(ms*1000);
#endif
}

// 关闭socket
int Heartbeat::closesock(int sock)
{
#ifdef WIN32
	return closesocket(sock);
#else
	return close(sock);
#endif
}

// 创建线程
#ifdef WIN32
int Heartbeat::new_thread(void (*func)(void*), void *param)
{
	int ret = _beginthread(func, NULL, param);
#else
int Heartbeat::new_thread(void* (*func)(void*), void *param)
{
	pthread_t handle = 0;        
	int ret = pthread_create(&handle, (pthread_attr_t*)0, func, param);
#endif
	if (ret >= 0) 
	{
		TRACE("Heartbeat -- Begin thread success!");
	}
	else
	{
		TRACE("Heartbeat -- ERROR: Begin thread fail! ERR:%d", ret);
	}
	return ret;
}

//===================================================

#endif // __Heartbeat__

