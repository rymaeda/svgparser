/*------------------------------------------------------------------------
 Module:        C:\lcc\srcs\convex\llist.c
 Author:        rymaeda@yahoo.com
 Project:       Sem nome
 State:
 Creation Date: 01/08/2000
 Description:   Lista ligada.
------------------------------------------------------------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ErrMsgExit(X)	{printf(X); exit(1);}

typedef struct NodalInfo{
	struct NodalInfo *pPrevious;
	struct NodalInfo *pNext;
	char *String;
} LLNODEINFO;

typedef struct{
	LLNODEINFO *Root;
	int NumberOfItems;
} LINKEDLIST, *pLINKEDLIST;

LINKEDLIST *LLCreate(void);
LLNODEINFO *LLInsertItem(LINKEDLIST *pLinkedList, char *pNewItem);
void LLDeleteItem(LINKEDLIST *pLinkedList, int Pos);
int LLFindItem(LINKEDLIST *pLinkedList, char *pItem);
LLNODEINFO *LLGetPointerItem(LINKEDLIST *pLinkedList,int Pos);
char *LLGetItemString(LINKEDLIST *pLinkedList, int Pos);
int LLLenght(LINKEDLIST *pLinkedList);
void LLDeleteList(LINKEDLIST *pLinkedList);

