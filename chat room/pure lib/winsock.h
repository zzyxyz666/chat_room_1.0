/*
#define SERVER 0
#define CLIENT 1
InitSock(int TYPE, SOCKET *s, const char* P_SERVER_IP, int PORT);
RETURN AcceptSock(SOCKET *pServer, SOCKET *pClient);
RETURN CloseSock(SOCKET *s);
RETURN SendSock(SOCKET *s,void* pbuffer);
RETURN RecvSock(SOCKET *s,void* pbuffer, int BufferLen);
//
RETURN Connect(SOCKET *s, SOCKADDR_IN *addr);
RETURN BindListen(SOCKET *s, SOCKADDR_IN *addr);
*/

#ifndef __PURE_WINSOCKET_H__
#define __PURE_WINSOCKET_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "zpurelib/pure_zwinsock.h"

#ifdef __cplusplus
}
#endif

#endif
