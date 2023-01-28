#include "../head/server.h"
#define Z_SERVER_IP 	"127.0.0.1"
#define Z_SERVER_PORT   44444

typedef int ID;
SOCKET server;
List list;
ID id = 0;
PACKAGE package;
HANDLE hMutex;
Element element;

int GroupSend(int GroupID, PACKAGE *pmsg)
{
	SOCKET sTemp;
	int len, i;
	Element group[GROUP_MAX] = {0};
	if(GroupID == -1)
	{
		showNode(&list,group,&len);
		for( i = 0; i<len; i++ )
		{
			sTemp = group[i].client;
			SendSock(&sTemp, pmsg, pmsg->size);
		}
	}
	return 0;
}

DWORD WINAPI recvMsg(void* client)
{
	SOCKET Client = (SOCKET)client;
	char Buffer[64] = {0};
	//init msg
	PACKAGE msg;
	msg.size = sizeof(msg);
	msg.ClientID = id;
	msg.GroupID = -1;
	sprintf(Buffer,"User %d",msg.ClientID);
	strcpy(msg.ClientName,Buffer);
	sprintf(Buffer,"Group %d",msg.GroupID);
	strcpy(msg.GroupName,Buffer);
	//return id
	msg.command = INIT_USER;
	sprintf(Buffer,"init user success...\r\n你初始ID（即名字）为 %d\r\n",msg.ClientID);
	strcpy(msg.Buffer,Buffer);
	SendSock(&Client, &msg, msg.size);
	//add linked-list
	WaitForSingleObject(hMutex,INFINITE);
 	element.name_id = msg.ClientID;
	element.room_id = msg.GroupID;
	element.client = (SOCKET)client;
	addNode(&list, element);
	ReleaseMutex(hMutex);
	while(1)
	{
		int r = RecvSock(&Client,&msg, msg.size);
		if( r == SUCCESS)
		{
			strcat(msg.Buffer,"\n\0");
			printf("%d:%d:%s",msg.command,msg.ClientID,msg.Buffer);
			switch(msg.command)
			{
				case GROUP_SEND:
					{
						GroupSend(msg.GroupID,&msg);
						break;
					}
				default:
					{
						
					}
			}
		}
		else
		{
			WaitForSingleObject(hMutex,INFINITE);
			delNode(&list,msg.GroupID);
			ReleaseMutex(hMutex);
			if( r == 0 )
			{
				printf("client leave \n");
			}
			else
			{
				printf("recv error %d\n", r);
			}
			ExitThread(0);
		}
	}
}

int main()
{
//	initConsole();
	initList(&list);
	int r;
	r = InitSock(SERVER, &server, Z_SERVER_IP, Z_SERVER_PORT);
 	if(r==ERROR_SOCKET_SUCCESS_SERVER)
 	{
 		printf("create server success...\n");
	}
 	else
 	{
 		printf("create server failure!!!%d\n", r);
 		CloseSock(&server);
 		return 0;
	}
	hMutex = CreateMutex(NULL,FALSE,NULL);
	while(1)
	{
		SOCKET client;
		char client_ip[32] = {0};
		int client_port;
		if(AcceptSock(&server, &client,client_ip, &client_port) == SUCCESS)
		{
			printf("client connect success from %s:%d\n", client_ip, client_port);
			id++;
			initThread(recvMsg, (void*)client);
		}
		else
		{
			printf("服务器崩溃：%ld\n", GetLastError());
			closesocket(server);
			WSACleanup();
			return -1;
		}
	}
	return 0;
}
