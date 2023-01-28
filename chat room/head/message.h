/*

*/
#ifndef __MESSAGE_H__
#define __MESSAGE_H__

enum COMMAND_MSG
{
	GROUP_SEND,
	INIT_USER,
	RENAME,
};

typedef struct SOCKETMESSAGE
{
	int Param;
	int command;
	int ClientID;
	int GroupID;
	int size;
	char ClientName[32];
	char GroupName[32];
	char Buffer[512];
}PACKAGE, *pPACKAGE;

#endif
