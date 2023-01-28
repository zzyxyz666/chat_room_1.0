/*
no finish
*/

#ifndef __PURE_ERROR_ZWINSOCKLIB_H__
#define __PURE_ERROR_ZWINSOCKLIB_H__
#include <windows.h>
#include <stdio.h>
#include <string.h>
void ErrorSock(int type, char *FUN_NAME, int r);
#define ErrorWindow ErrorWindows
#define ErrorWindows 0
#define ErrorConsole 1

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

void ConsoleErrorInitSock(int r);
void WindowsErrorInitSock(int r);
void ErrorSock(int type, char *FUN_NAME, int r)
{
	int flag = 0;
	if(strcmp(FUN_NAME, "InitSock") == 0) flag = 1;
	if(strcmp(FUN_NAME, "CloseSock") == 0) flag = 2;
	if(strcmp(FUN_NAME, "SendSock") == 0) flag = 3;
	if(strcmp(FUN_NAME, "RecvSock") == 0) flag = 4;
	if(strcmp(FUN_NAME, "AcceptSock") == 0) flag = 5;

	switch(type)
	{
		case ErrorWindows:
			switch(flag)
			{
				case 1:
					WindowsErrorInitSock(r);
					break;
				case 2:
					MessageBox(NULL, TEXT("�ɹ��ر�SOCKET����"), TEXT("SUCCESS_CLOSE_SOCKET"), MB_OK);
					break;
				default :
					MessageBox(NULL, TEXT("�������������!!!"), TEXT("ERROR_FUN_NAME"), MB_OK);
					break;
			}
			break;
		case ErrorConsole:
			switch(flag)
			{
				case 1:
					ConsoleErrorInitSock(r);
					break;
				case 2:
					printf("SUCCESS_CLOSE_SOCKET\n�ɹ��ر�SOCKET����!!!\n");
				default :
					printf("ERROR_FUN_NAME\n");
					printf("�������������!!!\n");
					break;
			}
			break;
		default :
			MessageBox(NULL, TEXT("TYPE �����������!!!"), TEXT("ERROR����"), MB_OK);
			break;
	}
}

void zWindowsErrorInitSock(int r)
{
	switch(r)
	{
		case ERROR_SOCKET_SUCCESS_SERVER:
			MessageBox(NULL, TEXT("��������ʼ���ɹ�!!!"), TEXT("SUCCESS_SERVER"), MB_OK);
			break;
		case ERROR_SOCKET_SUCCESS_CLIENT:
			MessageBox(NULL, TEXT("�ͻ��˳�ʼ���ɹ�!!!"), TEXT("SUCCESS_CLIENT"), MB_OK);
			break;
		case ERROR_SOCKET_DETERMINE_AGREEMENT:
			MessageBox(NULL, TEXT("ȷ��Э��汾ʧ��!!!"), TEXT("ERROR_DETERMINE_AGREEMENT"), MB_OK);
			break;
		case ERROR_SOCKET_CREAT_SOCKET:
			MessageBox(NULL, TEXT("����socketʧ��!!!"), TEXT("ERROR_CREAT_SOCKET"), MB_OK);
			break;
		case ERROR_SOCKET_SERVER_CONNECT:
			MessageBox(NULL, TEXT("���ӷ�����ʧ��!!!"), TEXT("ERROR_SERVER_CONNECT"), MB_OK);
			break;
		case ERROR_SOCKET_BIND:
			MessageBox(NULL, TEXT("��ʧ��!!!"), TEXT("ERROR_BIND"), MB_OK);
			break;
		case ERROR_SOCKET_LISTEN:
			MessageBox(NULL, TEXT("����ʧ��!!!"), TEXT("ERROR_LISTEN"), MB_OK);
			break;
		default:
			MessageBox(NULL, TEXT("��������ֵ����!!!"), TEXT("ERROR_FUN_RETURN"), MB_OK);
			break;
	}
}

void zConsoleErrorInitSock(int r)
{
	switch(r)
	{
		case ERROR_SOCKET_SUCCESS_SERVER:
			printf("SUCCESS_SERVER\n");
			printf("��������ʼ���ɹ�!!!\n");
			break;
		case ERROR_SOCKET_SUCCESS_CLIENT:
			printf("SUCCESS_CLIENT\n");
			printf("�ͻ��˳�ʼ���ɹ�!!!\n");
			break;
		case ERROR_SOCKET_DETERMINE_AGREEMENT:
			printf("ERROR_DETERMINE_AGREEMENT\n");
			printf("ȷ��Э��汾ʧ��!!!\n");
			break;
		case ERROR_SOCKET_CREAT_SOCKET:
			printf("ERROR_CREAT_SOCKET\n");
			printf("����socketʧ��!!!\n");
			break;
		case ERROR_SOCKET_SERVER_CONNECT:
			printf("ERROR_SERVER_CONNECT\n");
			printf("���ӷ�����ʧ��!!!\n");
			break;
		case ERROR_SOCKET_BIND:
			printf("ERROR_BIND\n");
			printf("��ʧ��!!!\n");
			break;
		case ERROR_SOCKET_LISTEN:
			printf("ERROR_LISTEN\n");
			printf("����ʧ��!!!\n");
			break;
		default:
			printf("ERROR_FUN_RETURN\n");
			printf("��������ֵ����!!!\n");
			break;
	}
}

#endif

