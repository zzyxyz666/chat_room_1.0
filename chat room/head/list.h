/*
*/
#ifndef __SINGLE_LINKED_LIST__
#define __SINGLE_LINKED_LIST__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"
#include "../pure lib/winsock.h"

enum ERROR_LIST
{
	LIST_FAILURE,
	LIST_SUCCESS,
	NODE_MALLOC_ERROR,
	NO_EXIIST_DATA,
	NONE_LIST,
	NO_FIND_DATA,
	NEW_FILE,
	READ_FILE_ERROR,
	WRITE_FILE_ERROR
};

typedef struct _ELEMENT//this struct can change
{
	//findNode use number to match sign
	int name_id;
	int room_id;
	SOCKET client;
}Element, *pElement;

typedef struct _NODE
{
	Element data;
	struct _NODE * next;
}Node, *pNode;

typedef struct _LINKED_LIST
{
	pNode head;
	pNode tail;
	pNode cur;
	pNode pre;
}List, *pList;
//function declare
int existNode(pList, int);
int initList(pList);
int addNode(pList, Element);
int delNode(pList, int);
int findNode(pList, int, pElement);
int showNode(pList, pElement, int*);
int changeNode(pList, int, pElement);
int emptyNode(pList);

int existNode(pList plist, int id)
{
	plist->pre = NULL;
	for(plist->cur = plist->head;\
	 plist->cur;\
	 plist->pre = plist->cur, plist->cur = plist->cur->next )
	{
		if(plist->cur->data.name_id == id)
		{
			return LIST_SUCCESS;
		}
	}
	return NO_EXIIST_DATA;
}

int initList(List *plist)
{
	plist->head = NULL;
	plist->tail = NULL;
	plist->cur = NULL;
	plist->pre = NULL;
}

int addNode(List *plist, Element element)
{
	pNode pnode;
	if(plist->head)
	{
		pnode = (pNode)malloc(sizeof(Node));
		if(pnode == NULL)
		{
			return NODE_MALLOC_ERROR;
		}
		pnode->data = element;
		pnode->next = NULL;
		plist->tail->next = pnode;
		plist->tail = pnode;
	}
	else
	{
		pnode = (pNode)malloc(sizeof(Node));
		if(pnode == NULL)
		{
			return NODE_MALLOC_ERROR;
		}
		pnode->data = element;
		pnode->next = NULL;
		plist->head = pnode;
		plist->tail = pnode;
	}
	return LIST_SUCCESS;
}

int delNode(List *plist,int sign)
{
	if(existNode(plist, sign) == LIST_SUCCESS)
	{
		if(plist->pre)
		{
			if(plist->cur == plist->tail)
			{
				plist->tail = plist->pre;
			}
			plist->pre->next = plist->cur->next;
		}
		else
		{
			if(plist->cur == plist->tail)
			{
				plist->tail = NULL;
			}
			plist->head = plist->cur->next;
		}
		free(plist->cur);
		return LIST_SUCCESS;
	}
	else
	{
		return NO_FIND_DATA;
	}
}

int showNode(List *plist, pElement list, int* listLen)
{
	int i = 0;
	pNode temp = plist->head;
	if(temp == NULL)
	{
		return NONE_LIST;
	}
	for( temp = plist->head; temp; temp = temp->next)
	{
		list[i] = temp->data;
		i++;
	}
	*listLen = i;
	return LIST_SUCCESS;
}

int findNode(List *plist, int sign, pElement ele)
{
	if(existNode(plist, sign) == LIST_SUCCESS)
	{
		*ele = plist->cur->data;
		return LIST_SUCCESS;
	}
	else
	{
		return NO_FIND_DATA;
	}
}

int changeNode(List *plist, int sign, pElement ele)
{
	if(existNode(plist, sign) == LIST_SUCCESS)
	{
		plist->cur->data = *ele;
		return LIST_SUCCESS;
	}
	else
	{
		return NO_FIND_DATA;
	}
}

int emptyNode(List *plist)
{
	pNode temp = plist->head;
	if(temp != NULL)
	{
		for( temp = plist->head; temp; temp = temp->next)
		{
			free(temp);
		}
		initList(plist);
	}
	return LIST_SUCCESS;
}

//////////////////////////////this function is file function
//
//int readData(pList plist)//这个是读文件的操作
//{
//	Element element;
//	FILE *pf = fopen("student.data", "a+b");
//	if( pf )
//	{
//		if(fgetc(pf) == EOF)
//		{
//			fclose(pf);
//			return NEW_FILE;
//		}
//		rewind(pf);
//		while(1)
//		{
//			fread(&element, sizeof(Element), 1, pf);
//			if(element.flag == '1')
//			{
//				fclose(pf);
//				return SUCCESS;
//			}
//			else
//			{
//				element.flag = '2';
//				_addNode(plist, element);
//			}
//		}
//	}
//	else
//	{
//		printf("读取数据失败！！！\n");
//		fclose(pf);
//		return READ_FILE_ERROR;
//	}
//}

//int saveData(pList plist)//这个是保存文件的操作
//{
//	pNode temp;
//	pElement pelement;
//	Element end = {'1',"\0","\0"};
//	FILE *pf = fopen("student.data","wb");
//	if( pf )
//	{
//		for(temp = plist->head; temp; temp = temp->next)
//		{
//			pelement = &(temp->data);
//			fwrite(pelement, sizeof(Element), 1, pf);
//		}
//		fwrite(&end, sizeof(Element), 1, pf);
//		printf("保存成功\n");
//		return SUCCESS;
//	}
//	else
//	{
//		printf("保存数据失败！！！\n");
//		fclose(pf);
//		return WRITE_FILE_ERROR;
//	}
//}

//	List list;
//	initList(&list);
//	int (*pFun[])(pList) =
//		closeNode,
//		addNode,
//		showNode,
//		findNode,
//		delNode,
//		changeNode,
//		emptyNode
#endif
