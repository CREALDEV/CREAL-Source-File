#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <time.h> 
#include <fcntl.h> 
#include <math.h> 
#include <pthread.h> 
#include <omp.h>

//These need to be added to the include file for this program

#define NONRELATION 0 //no action
#define EQUAL 1 //used for addition
#define GREATERTHAN 2 //used for deletion
#define LESSERTHAN 3 //used for changing
#define GREATERTHANEQUALTO 4 //used for maintaining
#define LESSERTHANEQUALTO 5 //used for transporting
#define NOTEQUAL 6 //used for transporting

#define NONACTION 0 //no action
#define INCREASE 1 //used for addition
#define DECREASE 2 //used for deletion
#define CHANGE 3 //used for changing
#define MAINTAIN 4 //used for maintaining
#define TRANSPORT 5 //used for transporting
#define NOTEQUAL 6 //used for transporting

uint minRange, maxRange, speedAdjustVar; //these are used for taking the maximum and minumum values, also adjusting the speed of the application
long double crealTime, timeIncrementer; //these are used for keeping up with time
uint numOfRange;
uint count;
typedef double creal_t; 

typedef creal_t (*actionFunctionPointer)( void); 

struct pre_actions 
 { 
 uint aID; 
 char actionType; 
 uint targetID; 
 actionFunctionPointer actionFunction;	
 creal_t targetValue; 
 }; 

struct pre_conditionlist 
 { 
 uint cID; 
 char relationType; 
 uint field; 
 actionFunctionPointer conditionFunction;	
 creal_t value; 
 }; 
 
struct pre_actionlist 
 { 
 uint alID; 
 char actionListIsNull; 
 char conditionListIsNull; 
 uint numberOfActionItems; 
 uint numberOfConditions; 

 struct pre_actions actions[10]; 
 struct pre_conditionlist conditions[10];  
 
 }; 
 


   struct crealNodeStruct { 
 	
 		/* May need to modify the datatypes */ 
 		
 		uint iD; //this is the id
 		uint numberOfProperties; //the number of properties
 		uint numberOfActions; //the number of actions 
 		char notNull; //this is to make sure that the data structure is not null
 		
		uint pID[400];
		creal_t *properties[400];
		struct pre_actionlist  *actionsList[400];
		struct crealNodeStruct *subNode; //this is still experimental
};




/* These structures will be used intrinsicly inside of a function block */

struct csvNodeDataStruct{ 
	
			uint nodeNumber; //the number of the node
			uint count; //the count of all the properties
			creal_t *properties; //the properties of the node
			
};


struct csvStruct
{
	
	struct csvNodeDataStruct *nodes;
	uint count; //the count of all the nodes
	long double currentTimeValue;
	
};



struct crealNodeStruct crealNodes[400];
creal_t crealProperties[400];

creal_t sumVector[400]; //add this to the cerebro

struct pre_actionlist crealActions[400];
/* Declaring the main functions for this code */ 

void printOutDataInCrealNodes(struct crealNodeStruct nodes[]); //this will be used to print out all of the junk
int processActionsAndConditions(struct crealNodeStruct nodes[], creal_t properties[], creal_t returnVector[]); //this is the main function to process the creal nodes
int processProperties(creal_t returnVector[], creal_t properties[]); //process the properties
void crealInit(void); //this function will be used to initialize all of the data structures
/* These functions below are to grab file information, could be placed in a wrapper function */

int grabRangesFromFile(const char *string, uint rangePointer[]);
int returnLineCountOfFile(const char *string);
//this function will write out 
int writeOutDataFileFor(uint rangePointer[], struct crealNodeStruct nodes[], const char *string); //this will be used to write out to a file

/* These are purely functional types of functions for multiprocessing */
uint findNumOfProperties(uint rangeIndex, struct crealNodeStruct nodes[]); //this is used to find the number of properties
uint findNumOfActions(uint rangeIndex, struct crealNodeStruct nodes[]); //this is used to find the number of actions
uint findNumOfActionItems(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[]); //this is used to find the number of action items
uint findNumOfConditions(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[]); //this is used to find the number of action items

uint returnValueOfProperties(uint rangeIndex, struct crealNodeStruct nodes[], creal_t returnArray[]); //this is used to find the number of properties

uint returnActionsTargetValues(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], creal_t returnArray[]); //returns action target values
uint returnActionsTargetIDs(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[]); //returns actions target ids
uint returnActionsActionTypes(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[]); //returns action types

uint returnConditionFields(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[]); //returns condition fields
uint returnConditionRelationTypes(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[]); //returns condition relations
uint returnConditionValues(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], creal_t returnArray[]); //returns condition values

creal_t actionFunction_1_0(void);
creal_t actionFunction_1_1(void);
creal_t actionFunction_1_2(void);
creal_t actionFunction_1_3(void);
creal_t actionFunction_1_4(void);
creal_t actionFunction_1_5(void);
creal_t conditionFunction_1_0(void);



int main(int argc, char **argv) 
 {
	 
crealNodes[1].numberOfProperties = 1;
crealNodes[1].properties[0] = &crealProperties[31];
crealProperties[31] = 1000.000000;
crealNodes[1].numberOfActions = 1;
crealNodes[1].actionsList[0] = &crealActions[1];
crealActions[1].alID = 1;
crealActions[1].numberOfActionItems = 6;
crealActions[1].actions[0].actionType = 1;
crealActions[1].actions[0].targetID = 5;
crealActions[1].actions[0].targetValue = 10.000000;
crealActions[1].actions[0].actionFunction = &actionFunction_1_0;
crealActions[1].actions[1].actionType = 1;
crealActions[1].actions[1].targetID = 6;
crealActions[1].actions[1].targetValue = 10.000000;
crealActions[1].actions[1].actionFunction = &actionFunction_1_1;
crealActions[1].actions[2].actionType = 1;
crealActions[1].actions[2].targetID = 7;
crealActions[1].actions[2].targetValue = 10.000000;
crealActions[1].actions[2].actionFunction = &actionFunction_1_2;
crealActions[1].actions[3].actionType = 1;
crealActions[1].actions[3].targetID = 8;
crealActions[1].actions[3].targetValue = 10.000000;
crealActions[1].actions[3].actionFunction = &actionFunction_1_3;
crealActions[1].actions[4].actionType = 1;
crealActions[1].actions[4].targetID = 9;
crealActions[1].actions[4].targetValue = 10.000000;
crealActions[1].actions[4].actionFunction = &actionFunction_1_4;
crealActions[1].actions[5].actionType = 1;
crealActions[1].actions[5].targetID = 10;
crealActions[1].actions[5].targetValue = 10.000000;
crealActions[1].actions[5].actionFunction = &actionFunction_1_5;
crealActions[1].numberOfConditions = 1;
crealActions[1].conditions[0].field = 11 ;
crealActions[1].conditions[0].relationType = 2 ;
crealActions[1].conditions[0].value = 1.000000 ;
crealActions[1].conditions[0].conditionFunction = &conditionFunction_1_0;
crealNodes[2].numberOfProperties = 7;
crealNodes[2].properties[0] = &crealProperties[5];
crealProperties[5] = 60.000000;
crealNodes[2].properties[1] = &crealProperties[6];
crealProperties[6] = 60.000000;
crealNodes[2].properties[2] = &crealProperties[7];
crealProperties[7] = 60.000000;
crealNodes[2].properties[3] = &crealProperties[8];
crealProperties[8] = 60.000000;
crealNodes[2].properties[4] = &crealProperties[9];
crealProperties[9] = 60.000000;
crealNodes[2].properties[5] = &crealProperties[10];
crealProperties[10] = 60.000000;
crealNodes[2].properties[6] = &crealProperties[11];
crealProperties[11] = 60.000000;
		//this needs to be added right here
		
		crealTime = 86400; //this is just a default
		speedAdjustVar = 0;
		numOfRange = 6; //silly putty, will be changed soon
		uint tempVar = findNumOfConditions(1,0,crealNodes);
		creal_t tmp[tempVar];
		creal_t sumVector[700];
		returnConditionValues(1,0, crealNodes,	tmp);
		int i = 0;
		for (i = 0; i < tempVar; i++)
		{
			
			printf("%f\n",tmp[i]);
			
		}
		printOutDataInCrealNodes(crealNodes);	
		sleep(5);
		for (count = 0; count < crealTime; count++)
		{
				srand(time(0)); //allowing the application to generate a random seed
						
				memset(sumVector,0,1000*sizeof(creal_t)); //set the memory to zero
				
				processActionsAndConditions(crealNodes, crealProperties, sumVector);
				
				processProperties(sumVector,crealProperties);
				
				
				
				//~ sleep(speedAdjustVar); //this is used to sleep the program
		}
		
		printOutDataInCrealNodes(crealNodes);	
		printf("%f \n",crealActions[1].actions[0].actionFunction()); //this is a test to show that the functions completely work
		exit(EXIT_SUCCESS);	

//the end of the program right here		
}


void printOutDataInCrealNodes(struct crealNodeStruct nodes[])
{
	//This function is just used to print the properties
	//~ *(crealNodes[1].properties[0])
	uint i, k, j; //make vars 
	i = k = j = 0; //set to zero
	
	printf("Printing out values of the data members!!\n\n\n");
	
	for (i = 1; i < 400; i++)
	{
		for (k = 0; k < nodes[i].numberOfProperties; k++)
		{
			printf("The property Value of node %d, property %d is : %f\n",i,k,*(nodes[i].properties[k]));
		}
	
		for (k = 0; k < nodes[i].numberOfActions; k++)
		{
			//~ nodes[1]->actionsList[0].numberOfActionItems // add this in soon
			for (j = 0; j < nodes[i].actionsList[k]->numberOfActionItems; j++)
			{
				
				//~ these are the things witihin the actions
				printf("The action type in node %d, action list elements %d, and action %d is : %d\n",i,k,j,nodes[i].actionsList[k]->actions[j].actionType);
				printf("The target id in node %d, action list elements %d, and action %d is : %d\n",i,k,j,nodes[i].actionsList[k]->actions[j].targetID);
				printf("The target value in node %d, action list elements %d, and action %d is : %f\n",i,k,j,nodes[i].actionsList[k]->actions[j].targetValue);
				
			}
			
			
			for (j = 0; j < nodes[i].actionsList[k]->numberOfConditions; j++)
			{
				
				//~ these are the things witihin the actions
				printf("The field value in node %d, action list elements %d, and condition %d is : %d\n",i,k,j,nodes[i].actionsList[k]->conditions[j].field);
				printf("The relation type in node %d, action list elements %d, and condition %d is : %d\n",i,k,j,nodes[i].actionsList[k]->conditions[j].relationType);
				printf("The value in node %d, action list elements %d, and condition %d is : %f\n",i,k,j,nodes[i].actionsList[k]->conditions[j].value);
				
			}
		}
	}
	
	//~ .field = 11 ;
//~ crealActions[1].conditions[0].relationType = 2 ;
//~ crealActions[1].conditions[0].value = 1.000000 ;
	//Pointers to arrays inside of the struct have to be dereferenced at the base of the struct member.
	//Pointers to arrays of structs inside of a struct have to use the pointer symbol
	//cool, dont return anything	
	
	//nodes[i]).actionsList[k]->numberOfActionItems => this is how you access the members within the access list
}


int processActionsAndConditions(struct crealNodeStruct nodes[], creal_t properties[], creal_t returnVector[])
{
	//Take these constants out of here because they serve no purpose
//~ char NONRELATION = 0x00; //nothing a type of NULL action


/* =================================================== */

	uint i, k, j, conditionCounter; //make vars 
	i = k = j = conditionCounter = 0; //set to zero
	
	creal_t tempDoubleVar0, tempDoubleVar1, tempDoubleVar2, tempBuffer, tempBuffer0, tempBuffer1; //these are temporary variables for the actions
	tempBuffer = tempBuffer0 = tempBuffer1 = tempDoubleVar0 = tempDoubleVar1 = tempDoubleVar2 = 0; //zeroing out everything
	
	for (i = 1; i < 400; i++)
	{
	
		//~ for (k = 0; k < nodes[i].numberOfProperties; k++)
		//~ {
	
		//~ }
		
		conditionCounter = 0; //reset the condition counter
		
		for (k = 0; k < nodes[i].numberOfActions; k++)
		{
	
		
			for (j = 0; j < nodes[i].actionsList[k]->numberOfConditions; j++)
			{
				//This iteration goes through the conditions
				
				switch (nodes[i].actionsList[k]->conditions[j].relationType)
				{
					
					
					/* This is the main switch statement for determining the actions and conditions */ 
					
					
					case NONRELATION:
					{
								//~ nodes[i].actionsList[k]->conditions[j].field = A
								//~ nodes[i].actionsList[k]->conditions[j].value = B
						break;
					}
					
					case EQUAL:
					{
						
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] ==
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[nodes[i].actionsList[k]->conditions[j].field] ==
						nodes[i].actionsList[k]->conditions[j].conditionFunction())
						{
									
									conditionCounter++; //increase the condition counter
							
						}
						
						break;
					}
					
					case GREATERTHAN:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] >
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[nodes[i].actionsList[k]->conditions[j].field] >
						nodes[i].actionsList[k]->conditions[j].conditionFunction())
						{
							
							conditionCounter++; //increase the condition counter
							
						}
						break;
					}
					
					case LESSERTHAN:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] <
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[nodes[i].actionsList[k]->conditions[j].field] <
						nodes[i].actionsList[k]->conditions[j].conditionFunction())
						{
							conditionCounter++; //increase the condition counter
							
						}
						break;
					}
					
					case GREATERTHANEQUALTO:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] >=
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[nodes[i].actionsList[k]->conditions[j].field] >=
						nodes[i].actionsList[k]->conditions[j].conditionFunction())
						{
							conditionCounter++; //increase the condition counter
							
						}
						
						break;
					}
					
					case LESSERTHANEQUALTO:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] <=
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[nodes[i].actionsList[k]->conditions[j].field] <=
						nodes[i].actionsList[k]->conditions[j].conditionFunction())
						{
							conditionCounter++; //increase the condition counter
							
						}
						break;
					}
					
					case NOTEQUAL:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] !=
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[nodes[i].actionsList[k]->conditions[j].field] !=
						nodes[i].actionsList[k]->conditions[j].conditionFunction())
						{
							
							conditionCounter++; //increase the condition counter
							
						}
						
						break;
					}
					
					default:
					{
						//nothing happens here
						//play titily-winks Blah!
						break;
					}
					
				}//end of the switch statement
				
			}//end of the condition iteration
			
			
			if (conditionCounter == nodes[i].actionsList[k]->numberOfConditions) //if the its non-zero
			{
						/* Right here is where we process the actual actions taking place */
						
					for (j = 0; j < nodes[i].actionsList[k]->numberOfActionItems; j++)
					{
						
						/* This is where the action types are looked up */
						
						switch (nodes[i].actionsList[k]->actions[j].actionType)
						{
							case INCREASE:
							{
								//increase
								
								//~ returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].targetValue;
								returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].actionFunction();
								
									
									
								break;
								
							}
							
							case DECREASE:
							{
								//decrease
								
								//~ tempDoubleVar0 = (nodes[i].actionsList[k]->actions[j].targetValue * -1); //invert this value
								tempDoubleVar0 = (nodes[i].actionsList[k]->actions[j].actionFunction() * -1); //invert this value
								returnVector[nodes[i].actionsList[k]->actions[j].targetID] += tempDoubleVar0;
							
								break;
								
							}
							
							case CHANGE:
							{
								//change
								
								//~ returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].targetValue;
								returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].actionFunction();
								
								break;
							}
							
							case MAINTAIN:
							{
								//maintain
								
								//nothing implemented yet
							
								break;
								
							}
							
							case TRANSPORT:
							{
								//transport
								
								//nothing implemented yet
							
								break;
								
							}
							
							default: 
							{
								
								//nothing is suposed to happen here...
								break;
							}
							

							
							
						}//end of actions switch statement

						//~ printf("The action type in node %d, action list elements %d, and action %d is : %d\n",i,k,j,nodes[i].actionsList[k]->actions[j].actionType);
						//~ printf("The target id in node %d, action list elements %d, and action %d is : %d\n",i,k,j,nodes[i].actionsList[k]->actions[j].targetID);
						//~ printf("The target value in node %d, action list elements %d, and action %d is : %f\n",i,k,j,nodes[i].actionsList[k]->actions[j].targetValue);
						
					}//end of action item for iteration

				
				/* right here is where we apply the actions to the nice vector container */ 
				
			}//end of the true condition counter
			
		}//end of inner for iiteration
	}//end of outer for iteration

	//end the function right here
	return 0; // everything was good	
} //end of the function


int processProperties(creal_t returnVector[], creal_t properties[])
{
	
		
		int i;
		i = 0;
		
			#pragma omp parallel for //openMP parallel for loop
			for (i = 0; i < 400; i++)
			{
					properties[i] += returnVector[i];
						
					
			}
			return 0; //blah!!!
}


int grabRangesFromFile(const char *string, uint rangePointer[])
{
		FILE *fp = NULL; //the main file pointer

	//good...
	fp = fopen(string, "r");
	if (fp == NULL)
	{
		return -1; //bad
		
	}
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	size_t count = 0;
       
			
			count = 0;
           
          while ((read = getline(&line, &len, fp)) != -1) {
               
               
               if (!(read <= 1))
               {
				
				    rangePointer[count] = atoi(line);
					count++;
				   
			   }
               
               
           }

          
           
			free(line);
			fclose(fp);
			return count; //everything was good
}


int returnLineCountOfFile(const char *string)
{
	
		FILE *fp = NULL; //the main file pointer

	//good...
	fp = fopen(string, "r");
	if (fp == NULL)
	{
		return -1; //bad
		
	}
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	size_t count = 0;
       
			
			count = 0;
           
          while ((read = getline(&line, &len, fp)) != -1) {
               
               
               if (!(read <= 1))
               {
				
				    //~ rangePointer[count] = atoi(line);
					count++;
				   
			   }
               
               
           }

          
           
			free(line);
			fclose(fp);
			return count; //everything was good
			
	   }

	   
int writeOutDataFileFor(uint rangePointer[], struct crealNodeStruct nodes[], const char *string)
{
	
	/* In this function we append to a file handle and we take care of thing in terms of
	 * writing out the stuff for the graph information */ 
	FILE *fp = NULL; //the main file pointer

	
	fp = fopen(string, "a"); //MAKE SURE TO OPEN THIS THING UP FOR APPENDING
	
	if (fp == NULL)
	{
		return -1; //bad
		
	}
	//utilize alloca in this function ...
	struct csvStruct tempNode;
	
	//This is used to get the node data
	tempNode.nodes = (struct csvNodeDataStruct *) alloca(sizeof(struct csvNodeDataStruct) * numOfRange); //awesome it works!

	uint *tempArray = (uint *) alloca(sizeof(uint) * numOfRange); //utilize this with a global variable
	
	fprintf(fp,""); //use fprintf to write directly to the file so we can write everything out to a file
	
	size_t len = 0;
	ssize_t read;
	size_t count = 0;
    
	
	
	fclose(fp); //close the file pointer
				
	return 1; //everything went good
}	   
	   
	   //oh oh oh ohhh...

/* A lot of these utilities are used for a functional approach to multiprocessing */

uint findNumOfProperties(uint rangeIndex, struct crealNodeStruct nodes[])
{
		//this function returns the number of properties
		return nodes[rangeIndex].numberOfProperties;
	
}

uint findNumOfActions(uint rangeIndex, struct crealNodeStruct nodes[])
{
		//this function returns the number of actions
		return nodes[rangeIndex].numberOfActions;
	
}


uint returnValueOfProperties(uint rangeIndex, struct crealNodeStruct nodes[], creal_t returnArray[])
{
	//this function returns values to the properties
	if (nodes[rangeIndex].numberOfProperties <= 0) {return 0;}
	
	int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].numberOfProperties; i++)
	{
		
			returnArray[i] = *(nodes[rangeIndex].properties[i]);
		
	}
	
		return nodes[rangeIndex].numberOfProperties;
	
}

uint findNumOfActionItems(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[])
{
	
	//this function returns the number of action items
	return nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems;
	
	
}


uint returnActionsTargetValues(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], creal_t returnArray[])
{
	// this function returns the target values of selected actions
	if (nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems <= 0) { return 0;} //there is nothing here to process
	
	
		int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems; i++)
	{
		
		//~ returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->actions[i].targetValue;
		returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->actions[i].actionFunction();
		
	}
	
	return nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems;
	
}


uint returnActionsTargetIDs(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[])
{
	// this function returns the target ids
	if (nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems <= 0) { return 0;} //there is nothing here to process
	
	
		int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems; i++)
	{
		
		returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->actions[i].targetID;
		
	}
	
	return nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems;
	
}

uint returnActionsActionTypes(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[])
{
	// this function returns action types
	if (nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems <= 0) { return 0;} //there is nothing here to process
	
	
		int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems; i++)
	{
		
		returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->actions[i].actionType;
		
	}
	
	return nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems;
	
}

uint findNumOfConditions(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[])
{
	
	//this function returns the number of conditions

	return nodes[rangeIndex].actionsList[listIndex]->numberOfConditions;
	
	
	
}


uint returnConditionFields(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[])
{
	// this function returns condition fields
	if (nodes[rangeIndex].actionsList[listIndex]->numberOfConditions <= 0) { return 0;} //there is nothing here to process
	
	
		int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].actionsList[listIndex]->numberOfConditions; i++)
	{
		
		returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->conditions[i].field;
		
	}
	
	return nodes[rangeIndex].actionsList[listIndex]->numberOfConditions;
	
}


uint returnConditionRelationTypes(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[])
{
	// this function returns relationship types
	if (nodes[rangeIndex].actionsList[listIndex]->numberOfConditions <= 0) { return 0;} //there is nothing here to process
	
	
		int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].actionsList[listIndex]->numberOfConditions; i++)
	{
		
		returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->conditions[i].relationType;
		
	}
	
	return nodes[rangeIndex].actionsList[listIndex]->numberOfConditions;
	
}


uint returnConditionValues(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], creal_t returnArray[])
{
	// this function returns relationship types
	if (nodes[rangeIndex].actionsList[listIndex]->numberOfConditions <= 0) { return 0;} //there is nothing here to process
	
	
		int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].actionsList[listIndex]->numberOfConditions; i++)
	{
		
		//~ returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->conditions[i].value;
		returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->conditions[i].conditionFunction();
		
	}
	
	return nodes[rangeIndex].actionsList[listIndex]->numberOfConditions;
	
}

creal_t actionFunction_1_0(void)
{
 return 10;
}
creal_t actionFunction_1_1(void)
{
 return 10;
}
creal_t actionFunction_1_2(void)
{
 return 10;
}
creal_t actionFunction_1_3(void)
{
 return 10;
}
creal_t actionFunction_1_4(void)
{
 return 10;
}
creal_t actionFunction_1_5(void)
{
 return 10;
}
creal_t conditionFunction_1_0(void)
{
 return 1;
}


//~ uint returnConditionFields(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[]); //returns condition fields
//~ uint returnConditionRelationTypes(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[]); //returns condition relations
//~ uint returnConditionValues(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], creal_t returnArray[]); //returns condition values
//~ 



/*
 * 
 * Add this in sometime soon!
//~ if (argc != 2) {
            //~ fprintf(stderr, "Usage: %s <file>\n", argv[0]);
            //~ exit(EXIT_FAILURE);
           //~ }


*/
