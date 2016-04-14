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
  
   #define USAGE "Input a file with a range, and input a time" 
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
  uint processActions(struct cr