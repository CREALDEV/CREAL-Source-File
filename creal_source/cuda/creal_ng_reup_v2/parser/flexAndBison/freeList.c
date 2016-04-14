#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "freeList.h"

void initLinkedList(LINK root)
{
	root->trashMem = NULL;
	root->next = NULL;
	
}

LINK returnListElement()
{
	return calloc(1,sizeof(ELEMENT));
}

void addElementToList(LINK root, char *garbage)
{
	LINK tempNode = returnListElement();
	tempNode->trashMem = garbage;
	tempNode->next = NULL;
	
	
	if (root->next == NULL)
	{
		root->next = tempNode;

	}
	else
	{
		while (!(root->next == NULL))
		{
			root = root->next;
		
		}
		
		root->next = tempNode;

	}
	
	
}


int deleteFreeList(LINK root)
{

	LINK tmp;

	while (!(root == NULL))
	{
		
		
		tmp = root;
		root = root->next;
		free(tmp);
	}
	
}

int freeTrash(LINK root)
{

	LINK tmp;

	while (!(root == NULL))
	{
		
		
		tmp = root;
		
		
		root = root->next;
		if (tmp->trashMem != NULL)
		{
			free(tmp->trashMem);
		}
		//~ free(tmp->trashMem);
		//~ free(tmp);
	}
	
}

