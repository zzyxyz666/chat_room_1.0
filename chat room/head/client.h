/*

*/
#ifndef __CLIENT__
#define __CLIENT__
#define __ALLWIN__
#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../pure lib/winsock.h"
#include "../pure lib/zwindows.h"
#include "../pure lib/winthread.h"
#include "message.h"
#define SEND_BUTTON_ID 1000
#define SET_BUTTON_ID 1001

#define WIDTH 1000
#define HEIGHT 600
#define BORDED 15
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 30
#define OUTPUT_WIDTH  	 	(WIDTH-2*BORDED)
#define OUTPUT_HEIGHT  		(HEIGHT-INPUT_HEIGHT-3*BORDED)
#define OUTPUT_X 			(BORDED)
#define OUTPUT_Y 			(BORDED)
#define INPUT_X      	  	(BORDED)
#define INPUT_Y     	    (OUTPUT_HEIGHT+2*BORDED)
#define INPUT_WIDTH   		(WIDTH-BUTTON_WIDTH-3*BORDED)
#define INPUT_HEIGHT    	(BUTTON_HEIGHT*3+2*BORDED)
#define SEND_BUTTON_X       (WIDTH-BORDED-BUTTON_WIDTH)
#define SEND_BUTTON_Y       (HEIGHT-BORDED-BUTTON_HEIGHT)
#define SET_BUTTON_X        (WIDTH-BORDED-BUTTON_WIDTH)
#define SET_BUTTON_Y        (HEIGHT-2*BORDED-2*BUTTON_HEIGHT)
#define OTHER_BUTTON_X      (WIDTH-BORDED-BUTTON_WIDTH)
#define OTHER_BUTTON_Y   	(HEIGHT-3*BORDED-3*BUTTON_HEIGHT)

#define CONTACTS_MAX 10
typedef struct CONTACTS_DATA
{
	int ID;
	int Name;
}Contact, *pContact;

typedef struct CLIENT_DATA
{
	int ID;
	char Name[32];
	int GroupID;
	char GroupName[32];
	Contact contact[CONTACTS_MAX];
}Client_Data,*pClient_Data;

#endif
