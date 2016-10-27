/*********************************************************************
*
* 文件名称：Heartbeat.hh
* 摘    要：跨Windows和Linux平台的Heartbeat类
*
* 当前版本：0.1
* 作    者：Jaxon Jia
* 创建日期：2013/07/24
*
**********************************************************************/
#ifndef __Heartbeat_h__
#define __Heartbeat_h__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>		// for memset
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <vector>
using std::vector;

#ifdef WIN32
#include <process.h>	// for _begainthread()
#include <WinSock2.h>
#include <WS2tcpip.h>	// for inet_pton
#pragma comment(lib, "ws2_32.lib")
#else
#include <sys/socket.h>
#include <getopt.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#endif

#define HB_VERSION    		"0.1"

#define HB_MAX_NODE_COUNT	100
#define HB_INTERVAL_SLEEP	1000
#define HB_DEFAULT_PORT		8000
#define HB_DEFAULT_IP		"127.0.0.1"
#define HB_TOLERANCE		4				// default is 4s

#define HB_IP_LEN			40				// define max ip len is 40byte
#define HB_NODE_DESCRIPT	50				// max length of node descript text 
#define HB_BUF_SIZE			1024			// socket recv or send buffer size

#define TRACE(format, ...)	printf("[%s]"format"\n", __FUNCTION__, ##__VA_ARGS__)
#define MIN(a,b)			(((a)<(b))?(a):(b))
#define MAX(a,b)			(((a)>(b))?(a):(b))

enum
{
	HB_ERR_SOCK_INIT = -100,
	HB_ERR_SOCK_BIND,
	HB_ERR_SOCK_SETOPT,
	HB_ERR_SOCK_SEND,
	HB_ERR_SOCK_RECV,
	HB_ERR_INVALID_PARAM,
	HB_OK = 0
};

typedef enum
{
	HB_CLIENT = 0,
	HB_SERVER
}HBRUNTYPE;

typedef enum
{
	HB_MSG_REG = 0,	// register to server or controller
	HB_MSG_RUNNING,	// running, heartbeat message
	HB_MSG_QUIT,	// client quit message
	HB_MSG_ERR,		// run error

}HBMSGTYPE;

typedef struct 
{
	HBMSGTYPE type;			// message type
	time_t    timestamp;	// current time
	u_int     len;			// msg length
	char      content[1];	// message content
}HBMSG;

typedef struct 
{
	char   ip[HB_IP_LEN];	// node ip
	u_int  port;			// node port
	time_t timestamp;		// node latest timestamp
	u_int  islive;			// 1 live, 0 dead
	void*  descript;		// node other info
}NODE;

class Heartbeat
{
public:
	Heartbeat(void);
	Heartbeat(HBRUNTYPE hb_type, const char* ip, u_int port=HB_DEFAULT_PORT, u_int interval=HB_INTERVAL_SLEEP, u_int tolerance=HB_TOLERANCE);
	~Heartbeat(void);

public:
	/*********************************************************************
	* 函数名称: init
	* 函数描述: 初始化
	* 参    数: 
	*			[IN]ip			const char *	IP地址
	*			[IN]port		u_int			端口
	*			[IN]interval	u_int			发送心跳包的间隔
	*			[IN]tolerance	u_int			心跳超时间隔时间
	* 返 回 值: N/A
	* 创建日期: 2013/07/24
	*********************************************************************/
	void init(HBRUNTYPE hb_type, const char* ip=HB_DEFAULT_IP, u_int port=HB_DEFAULT_PORT, u_int interval=HB_INTERVAL_SLEEP, u_int tolerance=HB_TOLERANCE);
	
	/*********************************************************************
	* 函数名称: send_msg
	* 函数描述: 消息发送函数 
	* 参    数: 
	*			[IN]type	HBMSGTYPE		消息类型
	*			[IN]content	const char *	消息内容
	*			[IN]len		u_int			消息内容的长度
	* 返 回 值: 发送成功返回0，否则返回负值
	* 创建日期: 2013/07/24
	*********************************************************************/
	int  send_msg(HBMSGTYPE type, const char* content, u_int len);

	/*********************************************************************
	* 函数名称: run
	* 函数描述: 作为Heartbeat客户端或服务端运行
	* 参    数: N/A
	* 返 回 值: N/A
	* 创建日期: 2013/07/25
	*********************************************************************/
	int  run();

	/*********************************************************************
	* 函数名称: callback
	* 函数描述: 心跳线程回调函数 
	* 参    数: 
	*			[IN]msg		HBMSG *		发送或接收到的消息
	*			[IN]src_sin	sockaddr_in	发送或接收的IP,Port信息
	* 返 回 值: N/A
	* 创建日期: 2013/07/25
	*********************************************************************/
	virtual void* callback(HBMSG* msg=NULL, sockaddr_in* src_sin=NULL);

	/*********************************************************************
	* 函数名称: as_server
	* 函数描述: 作为服务端运行时的心跳线程函数, as_client和as_server互斥
	* 参    数: N/A
	* 返 回 值: N/A
	* 创建日期: 2013/07/25
	*********************************************************************/
	virtual int as_server();

	/*********************************************************************
	* 函数名称: as_client
	* 函数描述: 作为客户端运行时的心跳线程函数, as_client和as_server互斥 
	* 参    数: N/A
	* 返 回 值: N/A
	* 创建日期: 2013/07/25
	*********************************************************************/
	virtual int as_client();

private:
	time_t cur_time();
	int init_sock();
	void mysleep(u_int ms);
	int closesock(int sock);
#ifdef WIN32
	static void threadfunc(void *param);
	int new_thread(void (*func)(void*), void *param);
#else
	static void* threadfunc(void *param);
	int new_thread(void* (*func)(void*), void *param);
#endif

	int   m_sock;
	HBRUNTYPE m_hb_type;	// run as client or server
	char  m_ip[HB_IP_LEN];	// Destination ip address, default is 127.0.0.1.
	u_int m_port;			// Listen or send socket port 
	u_int m_interval;		// The interval in milliseconds between heartbeat message, default is 1000 (1 second).
	u_int m_tolerance;		// The number of seconds before reporting that the node is dead, default is 4s.
	vector<NODE> node_list;
};

#endif // __Heartbeat_h__

