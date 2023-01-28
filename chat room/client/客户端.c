#include "../head/client.h"

#define Z_SERVER_IP 	"127.0.0.1"
#define Z_SERVER_PORT   44444

//#include
bit_32 g_flag = _32b00_;
HWND hwnd;
HWND hDialog;
HWND hRenameEdit;
HWND hSendBtn;
HWND hSetBtn;
HWND hout;
HWND hin;
SOCKET client;
Client_Data data;

void CreateDialogBox(void);

DWORD WINAPI recvMsg(void* pclient)
{
	char Buffer[1024];
	PACKAGE msg;
	SOCKET *pClient = (SOCKET*)pclient;
	while(1)
	{
		if(RecvSock(pClient,&msg,sizeof(msg)))
		{
			switch(msg.command)
			{
				case INIT_USER:
					{
						data.ID = msg.ClientID;
						strcpy(data.Name,msg.ClientName);
						data.GroupID = msg.GroupID;
						strcpy(data.GroupName,msg.GroupName);
						SetEditText(hout, msg.Buffer);
						break;
					}
				case GROUP_SEND:
					{
						strcpy(Buffer, msg.ClientName);
						strcat(Buffer, " :");
						strcat(Buffer, msg.Buffer);
						SetEditText(hout, Buffer);
						break;
					}
			}
		}
		else
		{
			MessageBox(hwnd, "���շ���������ʧ��\r\n�����´򿪿ͻ����Գ�������","ERROR", MB_OK|MB_ICONERROR);
			TerminateProcess(GetCurrentProcess(), 0);
		}
	}
}

void button(int id)
{
	PACKAGE bmsg;
	bmsg.size = sizeof(bmsg);
	switch(id)
	{
		case SEND_BUTTON_ID:
			{
				GetEditText(hin,bmsg.Buffer,sizeof(bmsg.Buffer));
				if(strlen(bmsg.Buffer) == 0)
				{
					MessageBox(NULL,"����������","WARNING", MB_OK);
					break;
				}
				CleanEditText(hin);
				bmsg.command = GROUP_SEND;
				bmsg.GroupID = data.GroupID;
				strcpy(bmsg.GroupName,data.GroupName);
				bmsg.ClientID = data.ID;
				strcpy(bmsg.ClientName,data.Name);
				SendSock(&client,&bmsg,bmsg.size);
				break;
			}
		case SET_BUTTON_ID:
			{
				//����ģʽ�Ի���
				if(~g_flag & _32b01_)
				{
					CreateDialogBox();
				}
				else
				{
					MessageBox(hDialog, "�������޸��������벻Ҫ�ظ���", "WARNING", MB_OK|MB_ICONERROR);
				}
				break;
			}
	}
}

void CloseDialog()
{
	DestroyWindow(hDialog);
	UnregisterClass("MyDialogBox",GetModuleHandle(NULL));
}

LRESULT CALLBACK DialogWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_COMMAND:
			switch((int)(LOWORD(wParam)))
			{
				case 1:
					{
						PACKAGE bmsg;
						bmsg.size = sizeof(bmsg);
						GetEditText(hRenameEdit,bmsg.Buffer,sizeof(bmsg.Buffer));
						if(strlen(bmsg.Buffer) == 0)
						{
							MessageBox(hDialog,"�޷�����Ϊ��","WARNING",MB_OK|MB_ICONERROR);
							CloseDialog();
						}
						strcpy(data.Name,bmsg.Buffer);
						g_flag ^= _32b01_;
						CloseDialog();
					}
                return 0;
			}
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void CreateDialogBox(void)
{
	g_flag |= _32b01_;
	HWND hRenameBtn;
	//window
	INITWIN win;
	win.style = SY_WINSIZE | SY_DIALOGBOX | SY_NAME;
//	win.style = SY_WINSIZE | SY_NAME | SY_CHILD;
	win.Width = 400;
	win.Height = 60+30;
	win.Title = "��������";
	win.className = "MyDialogBox";
	win.hwndParent = NULL;
	win.WndProc = DialogWndProc;
	hDialog = initWindow(WINFLAG_STYLE, &win);
	hRenameEdit = CreateInEdit(BORDED,BORDED,win.Width-BUTTON_WIDTH-2*BORDED,BUTTON_HEIGHT,NULL,2,hDialog);
	hRenameBtn = CreateButton(win.Width-BUTTON_WIDTH-BORDED,BORDED,BUTTON_WIDTH,BUTTON_HEIGHT,"����", 1, hDialog);
}

int winmain(void)
{
	//window
	INITWIN win;
	win.style = SY_WINSIZE | SY_FIXEDSIZE | SY_NAME;
	win.Width = WIDTH;
	win.Height = HEIGHT+30;
	win.Title = "������V1.0";
	hwnd = initWindow(WINFLAG_STYLE, &win);
    //callback
	RegistCommand(button);
	//control
	SetFont(700,"����");
 	hin = CreateInEdit(INPUT_X,INPUT_Y,INPUT_WIDTH,INPUT_HEIGHT,NULL,0,hwnd);
 	hout = CreateOutEdit(OUTPUT_X,OUTPUT_X,OUTPUT_WIDTH,OUTPUT_HEIGHT,
	 "---�������ҽ���ѧϰʹ�ò�������ҵ��;---\r\n---�벻Ҫ������������---\r\n"
	 ,0,hwnd);
 	hSendBtn = CreateButton(SEND_BUTTON_X,SEND_BUTTON_Y,BUTTON_WIDTH,BUTTON_HEIGHT,"����", SEND_BUTTON_ID, hwnd);
	hSetBtn = CreateButton(SET_BUTTON_X,SET_BUTTON_Y,BUTTON_WIDTH,BUTTON_HEIGHT,"����", SET_BUTTON_ID, hwnd);
 	
 	//socket

 	if(InitSock(CLIENT, &client, Z_SERVER_IP, Z_SERVER_PORT) == ERROR_SOCKET_SUCCESS_CLIENT)
 	{
 		SetEditText(hout, "connect server success...\n");
	}
 	else
 	{
 		MessageBox(hwnd, "����������ʧ��\r\n�����´򿪿ͻ����Գ�������","ERROR", MB_OK|MB_ICONERROR);
 		CloseSock(&client);
 		TerminateProcess(GetCurrentProcess(), 0);
	}
 	//thread
 	initThread(recvMsg, (void*)&client);
}

