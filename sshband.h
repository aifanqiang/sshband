#ifndef __SSHBAND_H__
#define __SSHBAND_H__	1

#include <sys/types.h>
#include <sys/time.h>
#include <stdint.h>
#include <netinet/in.h>

/**
 * 清理线程的间隔，单位秒
 * 如果客户端非正常断线，服务器是无法探知的，所以需要设定一个时间来定期检查非正常断线的客户端
 */
#define SESSION_CLEANUP_TIME 120

#define SSHBAND_LOG	printf

typedef struct hdl_pak_t {
	u_short sport;
	u_short dport;
	u_short len;
	u_char flags;
	struct in_addr ip_src, ip_dst;
} hdl_pak_t;

typedef struct ssh_session_t {
	uid_t uid;
	u_long client_data_time;	// 最后一次收到客户端数据包的时间
	u_long stime;	// 会话启动时间
	uint64_t outband;	// 服务器端上行流量
	uint64_t inband;	// 服务器下行流量
	char client_addr[17];	// 客户端地址
	char sessid[33];	// 会话唯一标识
	struct in_addr ip;
	struct ssh_session_t* next;
} ssh_session_t;
	

void load_config();	
void ssh_session_cleanup();

#endif
