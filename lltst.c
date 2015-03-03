#include <stdio.h>
#include "llist.h"

#define MAXLENGTH 1024

int Invert(char* FileName)
{
	FILE *fp1;
	char oneword[MAXLENGTH+1];
	char *c;
	int count, aux;
	pLINKEDLIST LinkedList= LLCreate();

	fp1 = fopen(FileName, "r");

	do {
		c = fgets(oneword, MAXLENGTH, fp1); /* get one line from the file */
		if (c != NULL)
			LLInsertItem(LinkedList, oneword);
	}
	while (c != NULL); /* repeat until NULL          */

	aux= LLLenght(LinkedList)>>1;
	printf ("aux= %d    %d\n", aux, LLLenght(LinkedList));
	for (count=1 ; count<=aux; count++)
		LLDeleteItem(LinkedList, count);
#if 1
	aux= LLLenght(LinkedList);
	for (count=1 ; count<aux; count++)
		printf("%s",LLGetItemString(LinkedList, count));
#else
	for (count=LLLenght(LinkedList); count; count--)
		printf("%s",LLGetItemString(LinkedList, count));
#endif
	fclose(fp1);
	LLDeleteList(LinkedList);
	return 0;
}

int main(int argc, char *argv[])
{
	if (argc==1){
		printf("Usage: INVERT filename(s)\n");
		exit(-1);
	}
	while(--argc > 0){
		printf("\n\n\nInverted file: %s\n", *++argv);
		Invert(*argv);
	}
	return 0;
}
