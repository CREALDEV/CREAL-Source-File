#ifndef FREE_LIST
/* This is the main library for Creal_ng */

#define FREE_LIST /* Make sure we don't have any damn duplicates */

struct linkedList
{
	char *trashMem;
	struct linkedList *next;

	
};

typedef struct linkedList ELEMENT;
typedef ELEMENT *LINK;

int freeTrash(LINK root);
int deleteFreeList(LINK root);
void addElementToList(LINK root, char *garbage);
LINK returnListElement();
void initLinkedList(LINK root);

#endif //end the if statements to stop duplications




