/*
 * 
 * http://torontosnumber1datedoctor.com/blog/your-relationship-may-need-a-new-attitude/ ...this will help out a bit..
 * 
 * 
 * 
 * */

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
/*
	*	 
	//~ #include <gmp.h>
	* 
*/
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

 //add this to cerero.
 #define USAGE "Input a file with a range, and input a time\n"
 uint minRange, maxRange, speedAdjustVar; //these are used for taking the maximum and minumum values, also adjusting the speed of the application 
 long double crealTime, timeIncrementer; //these are used for keeping up with time 
 uint numOfRange; 
 long double count; //the counting variable 
 
#define MAX_PROPERTIES 55
#define MAX_ACTION_LISTS 55
#define MAX_ACTIONS_AND_CONDITIONS 55
#define MAX_CREAL_NODES 55

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
 		
		uint pID[1000];
		creal_t *properties[1000];
		struct pre_actionlist  *actionsList[1000];
};


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
 
struct crealNodeStruct crealNodes[1000];
creal_t crealProperties[1000];
creal_t sumVector[1000];
struct pre_actionlist crealActions[1000];


 
 void printOutDataInCrealNodes(struct crealNodeStruct nodes[]); //this will be used to print out all of the junk
 int processActionsAndConditions(struct crealNodeStruct nodes[], creal_t properties[], creal_t returnVector[]); //this is the main function to process the creal nodes
 int processProperties(creal_t returnVector[], creal_t properties[]); //process the properties
 void crealInit(void); //this function will be used to initialize all of the data structures
 /* These functions below are to grab file information, could be placed in a wrapper function */
 
 int grabRangesFromFile(const char *string, uint rangePointer[]);
 int returnLineCountOfFile(const char *string);
 //this function will write out 
  
 /* Add these selection function to cerebro */
 int processSelectedActionsAndConditions(struct crealNodeStruct nodes[], creal_t properties[], creal_t returnVector[], uint rangePointer[], uint rangeSize); //this is the main function to process the creal nodes... through a selection!
 void printOutSelectedDataInCrealNodes(struct crealNodeStruct nodes[], uint rangePointer[], uint rangeSize); //this will only utilize selections

 uint evaluateConditions(struct crealNodeStruct *node, creal_t properties[], uint actionListIndex); //this is ok
 uint processActions(struct crealNodeStruct *node, creal_t properties[], creal_t returnVector[], uint actionListIndex); //this is ok too
 
 int writeOutDataFileFor(struct crealNodeStruct nodes[], uint rangePointer[], uint rangeIndex, long double *currenTime);
 int transferDataFileDataFileIndex(struct crealNodeStruct *node, uint nodeIndex, long double *currenTime); 
 int processProperties(creal_t returnVector[], creal_t properties[]); //process the properties
 int writeSelectedDataFile(struct crealNodeStruct *node, uint nodeIndex, uint propIndex, long double *currentTime);
 
 /* These are purely functional types of functions for multiprocessing */
 uint findNumOfProperties(struct crealNodeStruct *node); //this is used to find the number of properties
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
 
creal_t actionFunction_367_0(void);
creal_t actionFunction_380_0(void);
creal_t actionFunction_381_0(void);
creal_t actionFunction_370_0(void);
creal_t conditionFunction_370_0(void);
creal_t actionFunction_371_0(void);
creal_t conditionFunction_371_0(void);
creal_t actionFunction_368_0(void);
creal_t conditionFunction_368_0(void);
creal_t actionFunction_372_0(void);
creal_t conditionFunction_372_0(void);
creal_t actionFunction_373_0(void);
creal_t conditionFunction_373_0(void);
creal_t actionFunction_374_0(void);
creal_t conditionFunction_374_0(void);
creal_t actionFunction_383_0(void);
creal_t conditionFunction_383_0(void);
creal_t conditionFunction_383_1(void);
creal_t actionFunction_376_0(void);
creal_t conditionFunction_376_0(void);
creal_t conditionFunction_376_1(void);
creal_t actionFunction_378_0(void);
creal_t conditionFunction_378_0(void);
creal_t actionFunction_382_0(void);
creal_t conditionFunction_382_0(void);
creal_t actionFunction_384_0(void);
creal_t conditionFunction_384_0(void);
creal_t conditionFunction_384_1(void);
creal_t actionFunction_386_0(void);
creal_t conditionFunction_386_0(void);
creal_t actionFunction_388_0(void);
creal_t conditionFunction_388_0(void);
creal_t actionFunction_387_0(void);
creal_t conditionFunction_387_0(void);


int main(int argc, char **argv) 
{
	 
 					if (argc <= 2)		
					{
								
								
								//nothing was entered to start the application correctly
								fputs(USAGE, stderr); //shows application usage	
								exit(EXIT_FAILURE); // exit the application
								
								
					}


				//The ranges, add this into cerebro
				uint *rangeArray, range; //for the ranges
				range = (uint) returnLineCountOfFile(argv[1]); //geting the line count of the file
				rangeArray = (uint *) alloca(sizeof(uint) * range); //allocating the array for functions

				if (grabRangesFromFile(argv[1], rangeArray) < 0)
				{
						
						
							exit(EXIT_FAILURE);
					
				}
				
				
				crealInit(); //initialize the creal properties
				

			
		crealTime = atoi(argv[2]);
		

		
 		for (count = 0; count < crealTime; count++)
 		{
				memset(sumVector,0,1000*sizeof(creal_t)); //set the memory to zero
				
 				srand(time(0)); //allowing the application to generate a random seed
 								
 				processSelectedActionsAndConditions(crealNodes, crealProperties, sumVector,rangeArray, range);
 				
 				processProperties(sumVector,crealProperties);
 				
 				writeOutDataFileFor(crealNodes, rangeArray, range, &count);
 				
 		}
 		
 
 		exit(EXIT_SUCCESS);	
}


creal_t actionFunction_367_0(void)
{
 return (int) (crealProperties[898] + 1) % 86400;
}
creal_t actionFunction_380_0(void)
{
 return 1.672 * crealProperties[905] - 137.296;
}
creal_t actionFunction_381_0(void)
{
 return 0.00020048 * crealProperties[905] - 0.01646235;
}
creal_t actionFunction_370_0(void)
{
 return 181252;
}
creal_t conditionFunction_370_0(void)
{
 return 370;
}
creal_t actionFunction_371_0(void)
{
 return 181252;
}
creal_t conditionFunction_371_0(void)
{
 return 371;
}
creal_t actionFunction_368_0(void)
{
 return 181252;
}
creal_t conditionFunction_368_0(void)
{
 return 368;
}
creal_t actionFunction_372_0(void)
{
 return 181252;
}
creal_t conditionFunction_372_0(void)
{
 return 372;
}
creal_t actionFunction_373_0(void)
{
 return 181252;
}
creal_t conditionFunction_373_0(void)
{
 return 373;
}
creal_t actionFunction_374_0(void)
{
 return 181252;
}
creal_t conditionFunction_374_0(void)
{
 return 374;
}
creal_t actionFunction_383_0(void)
{
 return 12.6889;
}
creal_t conditionFunction_383_0(void)
{
 return 383;
}
creal_t conditionFunction_383_1(void)
{
 return 383;
}
creal_t actionFunction_376_0(void)
{
 return 12.6889;
}
creal_t conditionFunction_376_0(void)
{
 return 376;
}
creal_t conditionFunction_376_1(void)
{
 return 376;
}
creal_t actionFunction_378_0(void)
{
 return -(0.0748 * pow(crealProperties[899],2)) - (2.1468 * crealProperties[899]) + 4.9123;
}
creal_t conditionFunction_378_0(void)
{
 return 378;
}
creal_t actionFunction_382_0(void)
{
 return crealProperties[905] + (0.0748 * pow(crealProperties[899],2)) + (2.1468 * crealProperties[899]) + 4.9123;
}
creal_t conditionFunction_382_0(void)
{
 return 382;
}
creal_t actionFunction_384_0(void)
{
 return 12.6889;
}
creal_t conditionFunction_384_0(void)
{
 return 384;
}
creal_t conditionFunction_384_1(void)
{
 return 384;
}
creal_t actionFunction_386_0(void)
{
 return 181252;
}
creal_t conditionFunction_386_0(void)
{
 return 386;
}
creal_t actionFunction_388_0(void)
{
 return 5;
}
creal_t conditionFunction_388_0(void)
{
 return 388;
}
creal_t actionFunction_387_0(void)
{
 return 1;
}
creal_t conditionFunction_387_0(void)
{
 return 387;
}

void printOutDataInCrealNodes(struct crealNodeStruct nodes[])
{
	//This function is just used to print the properties
	//~ *(crealNodes[1].properties[0])
	uint i, k, j; //make vars 
	i = k = j = 0; //set to zero
	
	printf("Printing out values of the data members!!\n\n\n");
	
	for (i = 1; i < 1000; i++)
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

void printOutSelectedDataInCrealNodes(struct crealNodeStruct nodes[], uint rangePointer[], uint rangeSize)
{
	//This function is just used to print the properties
	//~ *(crealNodes[1].properties[0])
	uint i, k, j; //make vars 
	i = k = j = 0; //set to zero
	
	printf("Printing out values of the data members!!\n\n\n");
	
	for (i = 0; i < rangeSize; i++)
	{
		for (k = 0; k < nodes[rangePointer[i]].numberOfProperties; k++)
		{
			printf("The property Value of node %d, property %d is : %f\n",rangePointer[i],k,*(nodes[rangePointer[i]].properties[k]));
		}
	
		for (k = 0; k < nodes[rangePointer[i]].numberOfActions; k++)
		{
			//~ nodes[1]->actionsList[0].numberOfActionItems // add this in soon
			for (j = 0; j < nodes[rangePointer[i]].actionsList[k]->numberOfActionItems; j++)
			{
				
				//~ these are the things witihin the actions
				printf("The action type in node %d, action list elements %d, and action %d is : %d\n",rangePointer[i],k,j,nodes[rangePointer[i]].actionsList[k]->actions[j].actionType);
				printf("The target id in node %d, action list elements %d, and action %d is : %d\n",rangePointer[i],k,j,nodes[rangePointer[i]].actionsList[k]->actions[j].targetID);
				printf("The target value in node %d, action list elements %d, and action %d is : %f\n",rangePointer[i],k,j,nodes[rangePointer[i]].actionsList[k]->actions[j].actionFunction());
				
			}
			
			
			for (j = 0; j < nodes[rangePointer[i]].actionsList[k]->numberOfConditions; j++)
			{
				
				//~ these are the things witihin the actions
				printf("The field value in node %d, action list elements %d, and condition %d is : %d\n",rangePointer[i],k,j,nodes[rangePointer[i]].actionsList[k]->conditions[j].field);
				printf("The relation type in node %d, action list elements %d, and condition %d is : %d\n",rangePointer[i],k,j,nodes[rangePointer[i]].actionsList[k]->conditions[j].relationType);
				printf("The value in node %d, action list elements %d, and condition %d is : %f\n",rangePointer[i],k,j,nodes[rangePointer[i]].actionsList[k]->conditions[j].conditionFunction());
				
			}
		}
	}
	

}


int processSelectedActionsAndConditions(struct crealNodeStruct nodes[], creal_t properties[], creal_t returnVector[], uint rangePointer[], uint rangeSize)
{	
	//this is the main function to process the creal nodes... through a selection!
	
		
	uint i, k, *actionTruFalseArray; //make vars 
	i = k = 0; //set to zero
	
	//~ memset(trueFalseArray, 0, sizeof(uint) * rangeSize);

	for (i = 0; i < rangeSize; i++)
	{
		
		
		actionTruFalseArray = (uint *) alloca(sizeof(uint) * nodes[rangePointer[i]].numberOfActions);
		
		memset(actionTruFalseArray, 0, sizeof(uint) * nodes[rangePointer[i]].numberOfActions);
		
		
		//~ #pragma omp parallel for //openMP parallel for loop
		for (k = 0; k < nodes[rangePointer[i]].numberOfActions; k++)
		{
	
			
			actionTruFalseArray[k] = evaluateConditions(&nodes[rangePointer[i]], properties, k);
			
		
		}//end of inner for iiteration
		
		//~ #pragma omp parallel for //openMP parallel for loop
		for (k = 0; k < nodes[rangePointer[i]].numberOfActions; k++)
		{
				if(actionTruFalseArray[k])
				{
					
					processActions(&nodes[rangePointer[i]], properties, returnVector, k);
					
				}
		
		}//end of inner for iiteration
		
		
	}//end of outer for iteration

						//end the function right here
	return 0; // everything was good	
}



uint evaluateConditions(struct crealNodeStruct *node, creal_t properties[], uint actionListIndex)
{
	/* This function will be used to return */ 
	
	uint i, k, j, conditionCounter; //make vars 
	i = k = j = conditionCounter = 0; //set to zero
	
	if (!(node->actionsList[actionListIndex]->numberOfConditions))
	{
		
		return 1; //this means there are no conditions set, so run the action anyways
		
		
	}
			for (j = 0; j < node->actionsList[actionListIndex]->numberOfConditions; j++)
			{
				//This iteration goes through the conditions
				
				switch (node->actionsList[actionListIndex]->conditions[j].relationType)
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
						if (properties[node->actionsList[actionListIndex]->conditions[j].field] ==
						node->actionsList[actionListIndex]->conditions[j].conditionFunction())
						{
									
									conditionCounter++; //increase the condition counter
							
						}
						
						break;
					}
					
					case GREATERTHAN:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] >
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[node->actionsList[actionListIndex]->conditions[j].field] >
						node->actionsList[actionListIndex]->conditions[j].conditionFunction())
						{
							
							conditionCounter++; //increase the condition counter
							
						}
						break;
					}
					
					case LESSERTHAN:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] <
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[node->actionsList[actionListIndex]->conditions[j].field] <
						node->actionsList[actionListIndex]->conditions[j].conditionFunction())
						{
							conditionCounter++; //increase the condition counter
							
						}
						break;
					}
					
					case GREATERTHANEQUALTO:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] >=
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[node->actionsList[actionListIndex]->conditions[j].field] >=
						node->actionsList[actionListIndex]->conditions[j].conditionFunction())
						{
							conditionCounter++; //increase the condition counter
							
						}
						
						break;
					}
					
					case LESSERTHANEQUALTO:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] <=
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[node->actionsList[actionListIndex]->conditions[j].field] <=
						node->actionsList[actionListIndex]->conditions[j].conditionFunction())
						{
							conditionCounter++; //increase the condition counter
							
						}
						break;
					}
					
					case NOTEQUAL:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] !=
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[node->actionsList[actionListIndex]->conditions[j].field] !=
						node->actionsList[actionListIndex]->conditions[j].conditionFunction())
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

			if (conditionCounter == node->actionsList[actionListIndex]->numberOfConditions)
			{

				return 1; //everything is ok here
			}
			else
			{
				
				return 0; //everything is all bad here
			}
}

uint processActions(struct crealNodeStruct *node, creal_t properties[], creal_t returnVector[], uint actionListIndex)
{
	if (!(node->actionsList[actionListIndex]->numberOfActionItems))
	{
		return 0; //there are no action items to process, return 0
		
	}
	
	/* This function will process the actions */ 
	uint j; //make vars 
	j = 0; //set to zero
	
	
	creal_t tempDoubleVar0; //these are temporary variables for the actions
	tempDoubleVar0 = 0; //zeroing out everything
	

					//beginning 
					for (j = 0; j < node->actionsList[actionListIndex]->numberOfActionItems; j++)
					{
						
						/* This is where the action types are looked up */
						
						switch (node->actionsList[actionListIndex]->actions[j].actionType)
						{
							case INCREASE:
							{
								//increase
								
								//~ returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].targetValue;
								returnVector[node->actionsList[actionListIndex]->actions[j].targetID] += node->actionsList[actionListIndex]->actions[j].actionFunction();
								
									
									
								break;
								
							}
							
							case DECREASE:
							{
								//decrease
								
								//~ tempDoubleVar0 = (nodes[i].actionsList[k]->actions[j].targetValue * -1); //invert this value
								tempDoubleVar0 = (node->actionsList[actionListIndex]->actions[j].actionFunction() * -1); //invert this value
								returnVector[node->actionsList[actionListIndex]->actions[j].targetID] += tempDoubleVar0;
							
								break;
								
							}
							
							case CHANGE:
							{
								//change
								
								//~ returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].targetValue;
								//This has to be changed right here
								//~ returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].actionFunction();
								properties[node->actionsList[actionListIndex]->actions[j].targetID] = node->actionsList[actionListIndex]->actions[j].actionFunction();
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

	return 1;
	
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
	
	for (i = 1; i < 1000; i++)
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
			
			
			//~ if (conditionCounter == nodes[i].actionsList[k]->numberOfConditions) //if the its non-zero
			//~ {
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
								//This has to be changed right here
								//~ returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].actionFunction();
								properties[nodes[i].actionsList[k]->actions[j].targetID] = nodes[i].actionsList[k]->actions[j].actionFunction();
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
				
			//~ }//end of the true condition counter
			
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
			for (i = 0; i < 1000; i++)
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

	   
int writeOutDataFileFor(struct crealNodeStruct nodes[], uint rangePointer[], uint rangeIndex, long double *currentTime)
{
	
	/* In this function we append to a file handle and we take care of thing in terms of
	 * writing out the stuff for the graph information */ 
		
	int i = 0;
	//~ #pragma omp parallel for //openMP parallel for loop
	for(i = 0; i < rangeIndex; i++)
	{
		
			transferDataFileDataFileIndex(&nodes[rangePointer[i]], rangePointer[i] , currentTime);
		
		
		
	}
		
	return 1; //everything went good	
}


int transferDataFileDataFileIndex(struct crealNodeStruct *node, uint nodeIndex, long double *currentTime)
{
	int k = 0;
	
	uint numProp = findNumOfProperties(node); //find the number of properties
	
	//~ #pragma omp parallel for //openMP parallel for loop
	for(k = 0; k < numProp; k++)
	{
		
			writeSelectedDataFile(node, nodeIndex, k, currentTime);
	
		
	}
	
	
	
	return 1;
}


int writeSelectedDataFile(struct crealNodeStruct *node, uint nodeIndex, uint propIndex, long double *currentTime)
{
	
	/* In this function we append to a file handle and we take care of thing in terms of
	 * writing out the stuff for the graph information */ 
	
	FILE *fp = NULL; //the main file pointer
	
	char path[1024], tempString[1024]; // Good.... maybe the size should be increased eventually
	
	memset(path , 0 , sizeof(char) * 1024); // this is just setting the memory to zero
	
	sprintf(path,"%d_%d.dat\0", nodeIndex, propIndex);
	
	fp = fopen(path, "a"); //MAKE SURE TO OPEN THIS THING UP FOR APPENDING
	//~ 
	if (fp == NULL)
	{
		
		return -1; //bad
		
		
	}
	
	flockfile(fp); //lock the file handle.. like a semaphore
	
	fprintf(fp,"%d %f\n",(uint) *currentTime, *node->properties[propIndex] ); //use fprintf to write directly to the file so we can write everything out to a file
	
 
	
	funlockfile(fp);
	fclose(fp); //close the file pointer
				//~ 
	return 1; //everything went good	
}	   
	   
	   //oh oh oh ohhh...

/* A lot of these utilities are used for a functional approach to multiprocessing */

uint findNumOfProperties(struct crealNodeStruct *node)
{
		//this function returns the number of properties
		return node->numberOfProperties;
	
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

void crealInit(void)
{
	crealNodes[679].numberOfProperties = 1;
crealNodes[679].properties[0] = &crealProperties[898];
crealProperties[898] = 0.000000;
crealNodes[679].numberOfActions = 1;
crealNodes[679].actionsList[0] = &crealActions[367];
crealActions[367].alID = 367;
crealActions[367].numberOfActionItems = 1;
crealActions[367].actions[0].actionType = 3;
crealActions[367].actions[0].targetID = 898;
crealActions[367].actions[0].targetValue = 0.000000;
crealActions[367].actions[0].actionFunction = &actionFunction_367_0;
crealActions[367].numberOfConditions = 0;
crealNodes[681].numberOfProperties = 3;
crealNodes[681].properties[0] = &crealProperties[903];
crealProperties[903] = 1.000000;
crealNodes[681].properties[1] = &crealProperties[904];
crealProperties[904] = 1.000000;
crealNodes[681].properties[2] = &crealProperties[905];
crealProperties[905] = 901.260000;
crealNodes[681].numberOfActions = 2;
crealNodes[681].actionsList[0] = &crealActions[380];
crealActions[380].alID = 380;
crealActions[380].numberOfActionItems = 1;
crealActions[380].actions[0].actionType = 3;
crealActions[380].actions[0].targetID = 903;
crealActions[380].actions[0].targetValue = 1.672000;
crealActions[380].actions[0].actionFunction = &actionFunction_380_0;
crealActions[380].numberOfConditions = 0;
crealNodes[681].actionsList[1] = &crealActions[381];
crealActions[381].alID = 381;
crealActions[381].numberOfActionItems = 1;
crealActions[381].actions[0].actionType = 3;
crealActions[381].actions[0].targetID = 904;
crealActions[381].actions[0].targetValue = 0.000200;
crealActions[381].actions[0].actionFunction = &actionFunction_381_0;
crealActions[381].numberOfConditions = 0;
crealNodes[682].numberOfProperties = 1;
crealNodes[682].properties[0] = &crealProperties[900];
crealProperties[900] = 0.000000;
crealNodes[682].numberOfActions = 6;
crealNodes[682].actionsList[0] = &crealActions[370];
crealActions[370].alID = 370;
crealActions[370].numberOfActionItems = 1;
crealActions[370].actions[0].actionType = 2;
crealActions[370].actions[0].targetID = 900;
crealActions[370].actions[0].targetValue = 181252.000000;
crealActions[370].actions[0].actionFunction = &actionFunction_370_0;
crealActions[370].numberOfConditions = 1;
crealActions[370].conditions[0].field = 898 ;
crealActions[370].conditions[0].relationType = 1 ;
crealActions[370].conditions[0].value = 370.000000 ;
crealActions[370].conditions[0].conditionFunction = &conditionFunction_370_0;
crealNodes[682].actionsList[1] = &crealActions[371];
crealActions[371].alID = 371;
crealActions[371].numberOfActionItems = 1;
crealActions[371].actions[0].actionType = 1;
crealActions[371].actions[0].targetID = 900;
crealActions[371].actions[0].targetValue = 181252.000000;
crealActions[371].actions[0].actionFunction = &actionFunction_371_0;
crealActions[371].numberOfConditions = 1;
crealActions[371].conditions[0].field = 898 ;
crealActions[371].conditions[0].relationType = 1 ;
crealActions[371].conditions[0].value = 371.000000 ;
crealActions[371].conditions[0].conditionFunction = &conditionFunction_371_0;
crealNodes[682].actionsList[2] = &crealActions[368];
crealActions[368].alID = 368;
crealActions[368].numberOfActionItems = 1;
crealActions[368].actions[0].actionType = 1;
crealActions[368].actions[0].targetID = 900;
crealActions[368].actions[0].targetValue = 181252.000000;
crealActions[368].actions[0].actionFunction = &actionFunction_368_0;
crealActions[368].numberOfConditions = 1;
crealActions[368].conditions[0].field = 898 ;
crealActions[368].conditions[0].relationType = 1 ;
crealActions[368].conditions[0].value = 368.000000 ;
crealActions[368].conditions[0].conditionFunction = &conditionFunction_368_0;
crealNodes[682].actionsList[3] = &crealActions[372];
crealActions[372].alID = 372;
crealActions[372].numberOfActionItems = 1;
crealActions[372].actions[0].actionType = 2;
crealActions[372].actions[0].targetID = 900;
crealActions[372].actions[0].targetValue = 181252.000000;
crealActions[372].actions[0].actionFunction = &actionFunction_372_0;
crealActions[372].numberOfConditions = 1;
crealActions[372].conditions[0].field = 898 ;
crealActions[372].conditions[0].relationType = 1 ;
crealActions[372].conditions[0].value = 372.000000 ;
crealActions[372].conditions[0].conditionFunction = &conditionFunction_372_0;
crealNodes[682].actionsList[4] = &crealActions[373];
crealActions[373].alID = 373;
crealActions[373].numberOfActionItems = 1;
crealActions[373].actions[0].actionType = 1;
crealActions[373].actions[0].targetID = 900;
crealActions[373].actions[0].targetValue = 181252.000000;
crealActions[373].actions[0].actionFunction = &actionFunction_373_0;
crealActions[373].numberOfConditions = 1;
crealActions[373].conditions[0].field = 898 ;
crealActions[373].conditions[0].relationType = 1 ;
crealActions[373].conditions[0].value = 373.000000 ;
crealActions[373].conditions[0].conditionFunction = &conditionFunction_373_0;
crealNodes[682].actionsList[5] = &crealActions[374];
crealActions[374].alID = 374;
crealActions[374].numberOfActionItems = 1;
crealActions[374].actions[0].actionType = 2;
crealActions[374].actions[0].targetID = 900;
crealActions[374].actions[0].targetValue = 181252.000000;
crealActions[374].actions[0].actionFunction = &actionFunction_374_0;
crealActions[374].numberOfConditions = 1;
crealActions[374].conditions[0].field = 898 ;
crealActions[374].conditions[0].relationType = 1 ;
crealActions[374].conditions[0].value = 374.000000 ;
crealActions[374].conditions[0].conditionFunction = &conditionFunction_374_0;
crealNodes[683].numberOfProperties = 1;
crealNodes[683].properties[0] = &crealProperties[899];
crealProperties[899] = 0.000000;
crealNodes[683].numberOfActions = 5;
crealNodes[683].actionsList[0] = &crealActions[383];
crealActions[383].alID = 383;
crealActions[383].numberOfActionItems = 1;
crealActions[383].actions[0].actionType = 1;
crealActions[383].actions[0].targetID = 899;
crealActions[383].actions[0].targetValue = 12.688900;
crealActions[383].actions[0].actionFunction = &actionFunction_383_0;
crealActions[383].numberOfConditions = 2;
crealActions[383].conditions[0].field = 898 ;
crealActions[383].conditions[0].relationType = 2 ;
crealActions[383].conditions[0].value = 383.000000 ;
crealActions[383].conditions[0].conditionFunction = &conditionFunction_383_0;
crealActions[383].conditions[1].field = 898 ;
crealActions[383].conditions[1].relationType = 3 ;
crealActions[383].conditions[1].value = 383.000000 ;
crealActions[383].conditions[1].conditionFunction = &conditionFunction_383_1;
crealNodes[683].actionsList[1] = &crealActions[376];
crealActions[376].alID = 376;
crealActions[376].numberOfActionItems = 1;
crealActions[376].actions[0].actionType = 1;
crealActions[376].actions[0].targetID = 899;
crealActions[376].actions[0].targetValue = 12.688900;
crealActions[376].actions[0].actionFunction = &actionFunction_376_0;
crealActions[376].numberOfConditions = 2;
crealActions[376].conditions[0].field = 898 ;
crealActions[376].conditions[0].relationType = 2 ;
crealActions[376].conditions[0].value = 376.000000 ;
crealActions[376].conditions[0].conditionFunction = &conditionFunction_376_0;
crealActions[376].conditions[1].field = 898 ;
crealActions[376].conditions[1].relationType = 3 ;
crealActions[376].conditions[1].value = 376.000000 ;
crealActions[376].conditions[1].conditionFunction = &conditionFunction_376_1;
crealNodes[683].actionsList[2] = &crealActions[378];
crealActions[378].alID = 378;
crealActions[378].numberOfActionItems = 1;
crealActions[378].actions[0].actionType = 3;
crealActions[378].actions[0].targetID = 899;
crealActions[378].actions[0].targetValue = 0.000000;
crealActions[378].actions[0].actionFunction = &actionFunction_378_0;
crealActions[378].numberOfConditions = 1;
crealActions[378].conditions[0].field = 899 ;
crealActions[378].conditions[0].relationType = 2 ;
crealActions[378].conditions[0].value = 378.000000 ;
crealActions[378].conditions[0].conditionFunction = &conditionFunction_378_0;
crealNodes[683].actionsList[3] = &crealActions[382];
crealActions[382].alID = 382;
crealActions[382].numberOfActionItems = 1;
crealActions[382].actions[0].actionType = 3;
crealActions[382].actions[0].targetID = 905;
crealActions[382].actions[0].targetValue = 0.000000;
crealActions[382].actions[0].actionFunction = &actionFunction_382_0;
crealActions[382].numberOfConditions = 1;
crealActions[382].conditions[0].field = 899 ;
crealActions[382].conditions[0].relationType = 2 ;
crealActions[382].conditions[0].value = 382.000000 ;
crealActions[382].conditions[0].conditionFunction = &conditionFunction_382_0;
crealNodes[683].actionsList[4] = &crealActions[384];
crealActions[384].alID = 384;
crealActions[384].numberOfActionItems = 1;
crealActions[384].actions[0].actionType = 1;
crealActions[384].actions[0].targetID = 899;
crealActions[384].actions[0].targetValue = 12.688900;
crealActions[384].actions[0].actionFunction = &actionFunction_384_0;
crealActions[384].numberOfConditions = 2;
crealActions[384].conditions[0].field = 898 ;
crealActions[384].conditions[0].relationType = 2 ;
crealActions[384].conditions[0].value = 384.000000 ;
crealActions[384].conditions[0].conditionFunction = &conditionFunction_384_0;
crealActions[384].conditions[1].field = 898 ;
crealActions[384].conditions[1].relationType = 3 ;
crealActions[384].conditions[1].value = 384.000000 ;
crealActions[384].conditions[1].conditionFunction = &conditionFunction_384_1;
crealNodes[684].numberOfProperties = 1;
crealNodes[684].properties[0] = &crealProperties[901];
crealProperties[901] = 0.000000;
crealNodes[685].numberOfProperties = 1;
crealNodes[685].properties[0] = &crealProperties[902];
crealProperties[902] = 0.000000;
crealNodes[686].numberOfProperties = 1;
crealNodes[686].properties[0] = &crealProperties[906];
crealProperties[906] = 0.000000;
crealNodes[686].numberOfActions = 1;
crealNodes[686].actionsList[0] = &crealActions[386];
crealActions[386].alID = 386;
crealActions[386].numberOfActionItems = 1;
crealActions[386].actions[0].actionType = 1;
crealActions[386].actions[0].targetID = 906;
crealActions[386].actions[0].targetValue = 181252.000000;
crealActions[386].actions[0].actionFunction = &actionFunction_386_0;
crealActions[386].numberOfConditions = 1;
crealActions[386].conditions[0].field = 898 ;
crealActions[386].conditions[0].relationType = 1 ;
crealActions[386].conditions[0].value = 386.000000 ;
crealActions[386].conditions[0].conditionFunction = &conditionFunction_386_0;
crealNodes[689].numberOfProperties = 1;
crealNodes[689].properties[0] = &crealProperties[908];
crealProperties[908] = 10.000000;
crealNodes[689].numberOfActions = 1;
crealNodes[689].actionsList[0] = &crealActions[388];
crealActions[388].alID = 388;
crealActions[388].numberOfActionItems = 1;
crealActions[388].actions[0].actionType = 1;
crealActions[388].actions[0].targetID = 908;
crealActions[388].actions[0].targetValue = 5.000000;
crealActions[388].actions[0].actionFunction = &actionFunction_388_0;
crealActions[388].numberOfConditions = 1;
crealActions[388].conditions[0].field = 908 ;
crealActions[388].conditions[0].relationType = 3 ;
crealActions[388].conditions[0].value = 388.000000 ;
crealActions[388].conditions[0].conditionFunction = &conditionFunction_388_0;
crealNodes[690].numberOfProperties = 1;
crealNodes[690].properties[0] = &crealProperties[907];
crealProperties[907] = 120.000000;
crealNodes[690].numberOfActions = 1;
crealNodes[690].actionsList[0] = &crealActions[387];
crealActions[387].alID = 387;
crealActions[387].numberOfActionItems = 1;
crealActions[387].actions[0].actionType = 1;
crealActions[387].actions[0].targetID = 907;
crealActions[387].actions[0].targetValue = 1.000000;
crealActions[387].actions[0].actionFunction = &actionFunction_387_0;
crealActions[387].numberOfConditions = 1;
crealActions[387].conditions[0].field = 907 ;
crealActions[387].conditions[0].relationType = 3 ;
crealActions[387].conditions[0].value = 387.000000 ;
crealActions[387].conditions[0].conditionFunction = &conditionFunction_387_0;

	
}



