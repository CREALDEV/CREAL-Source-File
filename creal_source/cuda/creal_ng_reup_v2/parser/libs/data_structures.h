/*This is the main data structure file for the new creal
Developed by Randy White for Lawerence Berkeley National Laboratory



*/

struct qLinkedList
{
		// this queue structure is completely different
	uint crealNodeIndex; //this is the index for the crea node 
	uint crealNodeIndexExtra; //this is used for other processes 
	char *executionList; //this is sent to the cuda device for execution
	struct qLinkedList *next;
};


typedef struct qLinkedList QELEMENT;
typedef QELEMENT *QLINK;

struct queue
{
	QLINK head, tail;
	int numOfElements;
	
};

typedef struct queue QUEUE;




struct linkedList
{
			int element; //this is a voided pointer to something
			struct linkedList *next; //this a pointer to the next element in the list
			
};


struct stackContainer
{
		struct linkedList *top; //this is the head of the stack
		
	
};

struct garbageList
{
	//this is for the garbage list stuff		
			
			void *element;
			struct garbageList *next;
			
			
};

struct csvLinkedList
{
                        double element; //this is a voided pointer to something
                        struct csvLinkedList  *next; //this a pointer to the next element in the list

};

	

/*  Prototypes  */ 

/* Queue stuff */
int isQueueEmpty(QUEUE *root);
void initQueue(QUEUE *root);
QLINK returnQueueElement();  //make sure this is correct
void enqueue(QUEUE *root, uint cNodeIndex, char **execList); 
void enqueueForInternal(QUEUE *root, uint begining, uint end); 
int dequeue(QUEUE *root); 
char *returnExecutionElements(uint count); //this is used to return execution elements
/*   Stack prototypes */ 
int pushToStack(struct stackContainer *mainStack, struct linkedList *listElement); //push
int popOffStack(struct stackContainer *mainStack); //pop
struct linkedList *returnListElement(void); //return a stack element
struct stackContainer returnStackContainerElement(void); //return a stack element
typedef struct linkedList LINKEDLIST;
void initStack(struct stackContainer *mainStack);
void initList(struct linkedList *listElement);
void testFunction(int num, struct stackContainer *mainStack); 
/*Garbage list stuff */
void removeGarbage(struct garbageList *root, char const typeDirective);
void removeGarbageListItself(struct garbageList *root);
void initGarbageList(struct garbageList *root);
void addElementToGarbageList(void *passedElement, struct garbageList *root);
struct garbageList *returnGarbageListElement();
/* CSV linked list stuff */
struct csvLinkedList *returnCsvListElement(int count);
void initCsvList(struct csvLinkedList *root); //void the stuff
//this stuff is for the queue
int isQueueEmpty(QUEUE *root)
{
	if (root->head == NULL)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}

void initQueue(QUEUE *root)
{
	root->head = NULL;
	root->tail = NULL;
	root->numOfElements = 0;
}

QLINK returnQueueElement()
{
	//~ return malloc(sizeof(QLINK) * 1); //this is so freaking wrong
	return (QLINK) calloc(1, sizeof(QELEMENT));
}

void enqueue(QUEUE *root, uint cNodeIndex, char **execList)
{
	QLINK temp = returnQueueElement();
	
	temp->crealNodeIndex = cNodeIndex; 
	temp->executionList = *execList; 
	temp->next = NULL;
	
	if (isQueueEmpty(root) > 0)
	{
		root->head = root->tail = temp;
	}
	else
	{
		root->tail->next = temp;
		root->tail = temp;
	}
	root->numOfElements++;
}


void enqueueForInternal(QUEUE *root, uint begining, uint end)
{
	QLINK temp = returnQueueElement();
	
	temp->crealNodeIndex = begining; 
	temp->crealNodeIndexExtra = end; 
	
	temp->executionList = NULL; 
	temp->next = NULL;
	
	if (isQueueEmpty(root) > 0)
	{
		root->head = root->tail = temp;
	}
	else
	{
		root->tail->next = temp;
		root->tail = temp;
	}
	root->numOfElements++;
	
}

int dequeueForInternal(QUEUE *root)
{
		if (isQueueEmpty(root) > 0)
	{
			return -1;
	}
	else
	{
		QLINK temp = root->head->next;
		//~ free(root->head->executionList); //first get rid of the char array
		//beep-boop-beep-boop
		free(root->head); // then get rid of the head of the array
		
		root->head = temp;
		root->numOfElements--;
		
		if (root->head == NULL && root->tail != NULL)
		{
			
			root->tail = NULL; //Set tail to null as well lol it could of been bad!!
		}
		
		return 1; // everything is all good right here
	}
}

int dequeue(QUEUE *root)
{
	
	if (isQueueEmpty(root) > 0)
	{
			return -1;
	}
	else
	{
		QLINK temp = root->head->next;
		free(root->head->executionList); //first get rid of the char array
		//beep-boop-beep-boop
		free(root->head); // then get rid of the head of the array
		
		root->head = temp;
		root->numOfElements--;
		
		if (root->head == NULL && root->tail != NULL)
		{
			
			root->tail = NULL; //Set tail to null as well lol it could of been bad!!
		}
		
		return 1; // everything is all good right here
	}

}


char *returnExecutionElements(uint count)
{
	//return the execution element list
	return (char *) calloc(count, sizeof(char));
}


//stack stuff right here 


int pushToStack(struct stackContainer *mainStack, struct linkedList *listElement )
{
	
	listElement->next = mainStack->top; //set the element's link to the top
	 mainStack->top = listElement; //change the top to the list element
	
	
		return 1;
	
}


int popOffStack(struct stackContainer *mainStack)
{
	if (mainStack->top == NULL)
	{
		
		return -1;
	}
	
	else
	{
		struct linkedList *tempList = mainStack->top;
		mainStack->top = mainStack->top->next;
		free(tempList);
		
	}
	
		return 1;
}

void initStack(struct stackContainer *mainStack)
{
	
		
	mainStack->top = NULL;
	
}


struct linkedList *returnListElement(void)
{
	// returns a calloc and this is also casted
	return (struct linkedList *)calloc(1, sizeof(struct linkedList));
}


void testFunction(int num, struct stackContainer *mainStack)
{
	
	struct linkedList *temp = returnListElement();
	
	initList(temp);
	temp->element = num;
	pushToStack(mainStack, temp);
}


void initList(struct linkedList *listElement)
{
	listElement->next = NULL;
	listElement->element = 0;
	
	
	
	
}



//garbage collection

void initGarbageList(struct garbageList *root)
{
	root->element = NULL;
	root->next = NULL;
}
//~ 


struct garbageList *returnGarbageListElement()
{
	return (struct garbageList *)calloc(1,sizeof(struct garbageList));
	
}


void addElementToGarbageList(void *passedElement, struct garbageList *root)
{
		


			if (root->element == NULL)
			{
				
				root->next = NULL;
				root->element = passedElement;
			}

			else
			{	
				struct garbageList *tempNode = returnGarbageListElement();

				tempNode->element = passedElement;
				tempNode->next = NULL;
					while (!(root->next == NULL))
					{
						root = root->next;

					}
				
				root->next = tempNode;

			}


}


void removeGarbage(struct garbageList *root, char const typeDirective)
{
	
	struct garbageList *tmp = NULL; //nullify the pointer
	
		while (!(root == NULL))
			{


					tmp = root;
					
						
						if (tmp->element != NULL)
						{
								if (typeDirective == HOST) { free(tmp->element); }
				
								if (typeDirective == DEVICE) { cudaFree(tmp->element); }
						}
						if (root != NULL)
						{
						
							free(tmp);
							root = root->next;
						}
			}
	//~ void *tmp = NULL;
	//~ 
	//~ while (root->element != NULL)
	//~ {
		//~ 
			//~ tmp = root->element;
		//~ 
	
		//~ 
		//~ 
		//~ 
		//~ 
				//~ root = root->next; //move down the list!!
		//~ 
	//~ }
	
	
}


//check this stufff bellow to make sure that it is ok,
struct csvLinkedList *returnCsvListElement(int count)
{
    //this returns a linked list element for the csv file
	if (count)
	{
 	return (struct csvLinkedList *) calloc(count, sizeof(struct csvLinkedList));
	}
	else
	{
		return (struct csvLinkedList *) calloc(1, sizeof(struct csvLinkedList));
	}

}


void initCsvList(struct csvLinkedList *root)
{
	root->element = 0.f;
	root->next = NULL;
}



//~ void removeGarbageListItself(struct garbageList *root)
//~ {
		//~ while (!(root == NULL))
//~ {
//~ 
//~ 
//~ tmp = root;
//~ root = root->next;
//~ free(tmp);
//~ }
//~ }
