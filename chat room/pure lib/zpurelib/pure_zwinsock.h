/*
ifdef __DEBUG__ you will be simpler get error
need link wsock32
use TCP/IP
*/

#ifndef __PURE_ZWINSOCK_H__
#define __PURE_ZWINSOCK_H__
//base include file
#include "zbase.h"
#ifndef __ALLWIN__
#include <winsock2.h>
#include <windows.h>
#endif
#include <stdio.h>
#include <string.h>
//
#ifdef __DEBUG__
#include "pure_error_zwinsock.h"
#else
enum ERROR_SOCKET
{
	ERROR_SOCKET_FAILUER,
	ERROR_SOCKET_SUCCESS,
	ERROR_SOCKET_TYPE,
	ERROR_SOCKET_DETERMINE_AGREEMENT,
	ERROR_SOCKET_CREAT_SOCKET,
	ERROR_SOCKET_SERVER_CONNECT,
	ERROR_SOCKET_BIND,
	ERROR_SOCKET_LISTEN,
	ERROR_SOCKET_SUCCESS_CLIENT,
	ERROR_SOCKET_SUCCESS_SERVER,
	//error part
};
#endif
//base head file
#define SERVER 0
#define CLIENT 1
//function declare
RETURN InitSock(int TYPE, SOCKET *s, const char* P_SERVER_IP, int PORT);
RETURN Connect(SOCKET *s, SOCKADDR_IN *addr, int len);
RETURN BindListen(SOCKET *s, SOCKADDR_IN *addr, int len);
RETURN CloseSock(SOCKET *s);
RETURN SendSock(SOCKET *s,void* pbuffer, int BufferLen);
RETURN RecvSock(SOCKET *s,void* pbuffer, int BufferLen);
RETURN AcceptSock(SOCKET *pServer, SOCKET *pClient, char* Client_IP, int *Client_PORT);
//function define
RETURN InitSock(int TYPE, SOCKET *s, const char* P_SERVER_IP, int PORT)
{
	int r;
	//1.determine agreement
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if(HIBYTE(wsaData.wVersion) != 2 || LOBYTE(wsaData.wVersion) != 2)
	{
		//determine agreement failure
		return ERROR_SOCKET_DETERMINE_AGREEMENT;
	}

	//2.create socket
	*s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if(SOCKET_ERROR == *s)
	{
		//create socket failure
		WSACleanup();
		return ERROR_SOCKET_CREAT_SOCKET;
	}

	SOCKADDR_IN addr = { 0 };
	//3.Get server address cluster
	addr.sin_family = AF_INET;
	//It must be the same as the first parameter of the socket function
	addr.sin_addr.S_un.S_addr = inet_addr(P_SERVER_IP);
	//server ip address
	addr.sin_port = htons(PORT);
	//port number
	int len = sizeof(addr);

	switch(TYPE)
	{
		case SERVER :
			r = BindListen(s, &addr, len);
			if(r == SUCCESS)
			{
				return ERROR_SOCKET_SUCCESS_SERVER;
			}
			else
			{
				return r;
			}
			break;
		case CLIENT :
			r = Connect(s, &addr, len);
			if(r == SUCCESS)
			{
				return ERROR_SOCKET_SUCCESS_CLIENT;
			}
			else
			{
				return r;
			}
			break;
		default :
			return ERROR_SOCKET_TYPE;
	}
	//bind success
}

RETURN Connect(SOCKET *s, SOCKADDR_IN *addr, int len)
{
	//4.connect
	int r = connect(*s, (SOCKADDR*)addr, len);
	if(-1 == r)
	{
		//server connect failure
		CloseSock(s);
		return ERROR_SOCKET_SERVER_CONNECT;
	}
	return SUCCESS;
}

RETURN BindListen(SOCKET *s, SOCKADDR_IN *addr, int len)
{
	//4.bind
	int r =  bind(*s, (SOCKADDR*)addr, len);
	if (-1 == r)
	{
		//bind failure
		CloseSock(s);
		return ERROR_SOCKET_BIND;
	}

	//5.listen
	r = listen(*s, 16);
	if (-1 == r)
	{
		//listen failure
		CloseSock(s);
		return ERROR_SOCKET_LISTEN;
	}
	return SUCCESS;
}

RETURN CloseSock(SOCKET *s)
{
	closesocket(*s);
	WSACleanup();
	return SUCCESS;
}

RETURN AcceptSock(SOCKET *pServer, SOCKET *pClient, char* Client_IP, int *Client_PORT)
{
	//6.accept connect
	SOCKADDR_IN cAddr = { 0 };
	int len = sizeof(cAddr);

	*pClient = accept(*pServer,(struct sockaddr*)&cAddr,&len);//get data
	strcpy(Client_IP,inet_ntoa(cAddr.sin_addr));
	*Client_PORT = cAddr.sin_port;
	if(INVALID_SOCKET == *pClient)
	{
		return FAILUER;
	}
	return SUCCESS;
}

RETURN SendSock(SOCKET *s,void* pbuffer, int BufferLen)
{
	send(*s, (char*)pbuffer, BufferLen, 0);
	return SUCCESS;
}

RETURN RecvSock(SOCKET *s,void* pbuffer, int BufferLen)
{
	int r = recv(*s,(char*)pbuffer, BufferLen, 0);
	if(r > 0)
 	{
		return SUCCESS;
	}
	else
 	{
		return WSAGetLastError();
	}
}

#endif
