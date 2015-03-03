/*------------------------------------------------------------------------
 Module:        C:\lcc\srcs\convex\llist.c
 Author:        rymaeda@yahoo.com
 Project:       None
   State:
 Creation Date: 01/08/2000
 Description:   Linked list.
------------------------------------------------------------------------*/

#include "llist.h"

LINKEDLIST *LLCreate(void){
	LINKEDLIST * NewList= (LINKEDLIST *)malloc(sizeof(LINKEDLIST));
	NewList->Root= NULL;
	NewList->NumberOfItems= 0;
	return NewList;
}

LLNODEINFO *LLInsertItem(LINKEDLIST * pLinkedList, char *pNewItem){
	LLNODEINFO *NewNode, *Previous;
	char *pNewNodeString;

	if (!((NewNode=(LLNODEINFO *)malloc(sizeof(LLNODEINFO)))&&
		(pNewNodeString=(char *)malloc(strlen(pNewItem)+1))))
		ErrMsgExit("Memory allocation error! Program terminated.\n\n");

	strcpy(pNewNodeString, pNewItem);

	if (pLinkedList->Root==NULL){
		NewNode->pPrevious= NewNode->pNext= NULL;
		NewNode->String= pNewNodeString;
		pLinkedList->Root= NewNode;
	}
	else{
		Previous= LLGetPointerItem(pLinkedList, pLinkedList->NumberOfItems);
		Previous->pNext= NewNode;
		NewNode->pPrevious= Previous;
		NewNode->pNext= NULL;
		NewNode->String= pNewNodeString;
	}
	pLinkedList->NumberOfItems++;
	return NewNode;
}

void LLDeleteItem(LINKEDLIST *pLinkedList, int Pos){
	LLNODEINFO *pNodeToDel= LLGetPointerItem(pLinkedList,Pos);

	if (Pos==0)
		return;
	if(pLinkedList->NumberOfItems==Pos){ /* Last item delete */
		pNodeToDel->pPrevious->pNext= NULL;
		free(pNodeToDel->String);
		free(pNodeToDel);
		pLinkedList->NumberOfItems--;
		return;
	} 
	if(Pos==1){ /* first item deletion */
		pNodeToDel->pNext->pPrevious= NULL;
		pLinkedList->Root= pNodeToDel->pNext;
		free(pNodeToDel->String);
		free(pNodeToDel);
		pLinkedList->NumberOfItems--;
		return;
	}
	
	pNodeToDel->pNext->pPrevious= pNodeToDel->pPrevious;
	pNodeToDel->pPrevious->pNext= pNodeToDel->pNext;
	free(pNodeToDel->String);
	free(pNodeToDel);
	pLinkedList->NumberOfItems--;
}

int LLFindItem(LINKEDLIST *pLinkedList, char *pItem){
	LLNODEINFO *pNode= pLinkedList->Root;
	int count;
	for (count=1; count<=pLinkedList->NumberOfItems; count++){
		if (strcmp(pItem,pNode->String)==0)
			return count;
		pNode= pNode->pNext;
	}
	return 0;
}

LLNODEINFO *LLGetPointerItem(LINKEDLIST *pLinkedList, int Pos){
	LLNODEINFO *pNode= pLinkedList->Root;
	int count;

	for (count=1; count<Pos; count++)
		pNode= pNode->pNext;
	return pNode;
}

char *LLGetItemString(LINKEDLIST *pLinkedList, int Pos){
	LLNODEINFO *pNode= pLinkedList->Root;
	int count;

	for (count=1; count<Pos; count++)
		pNode= pNode->pNext;
	return pNode->String;
}

int LLLenght(LINKEDLIST *pLinkedList){
	return pLinkedList->NumberOfItems;
}

void LLDeleteList(LINKEDLIST *pLinkedList){
	LLNODEINFO *pNode= pLinkedList->Root;
	int count;

	for (count=1; count<pLinkedList->NumberOfItems; count++){
		free(pNode->String);
		pNode= pNode->pNext;
		free(pNode->pPrevious);
	}
	free(pNode->String);
	free(pNode);
	free(pLinkedList);
}
