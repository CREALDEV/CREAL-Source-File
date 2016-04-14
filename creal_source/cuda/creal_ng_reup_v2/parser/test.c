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
/* This is a shadow copy of Creal the next generation */

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
 creal_t value; 
 }; 
 
struct pre_actionlist 
 { 
 uint alID; 
 char actionListIsNull; 
 char conditionListIsNull; 
 uint numberOfActions; 
 uint numberOfConditions; 

 struct pre_actions actionsList[5]; 
 struct pre_conditionlist conditionlist[5];  
 
 }; 
 
 struct crealNodeStruct { 
	
		/* May need to modify the datatypes */ 
		
		uint iD; //this is the id
		uint numberOfProperties; //the number of properties
		uint numberOfActions; //the number of actions 
		char notNull; //this is to make sure that the data structure is not null
		
		
		uint pID[5]; //these are the property ids 
		creal_t *properties[5]; //these are the properties right here
		struct pre_actionlist  *actionsList[5]; //this is the actions
		
					//this is the creal node data structure
	
}; 

/* these need to be added to cerebro */
/* This is what you need to do in order to dereference the structure 
 * *(crealNodes[1].properties[0]) */
struct crealNodeStruct crealNodes[3]; //these are the creal nodes
creal_t crealProperties[400]; //these are the creal properties
struct pre_actionlist crealActions[400]; //these are the creal actions right here

int main(int argc, char **argv) 
 {
	 
	crealNodes[1].numberOfProperties = 1;
	
crealNodes[1].properties[0] = &crealProperties[31];
crealProperties[31] = 1000.000000;
//~ printf("This is the current creal property value %f\n", crealProperties[31]);
printf("This is the current creal property value %f\n", *(crealNodes[1].properties[0]));
crealNodes[1].numberOfActions = 1;
crealActions[1].alID = 1;
//~ crealNodes[1].actionsList[0].alID = 1;

crealNodes[1].actionsList[0] = &crealActions[1];
//~ crealNodes[1].actionlist[0].numberOfActionItems = 6;
//~ crealNodes[1].actionlist[0].actions[0].actionType = 1 ;
//~ crealNodes[1].actionlist[0].actions[0].targetID = 5 ;
//~ crealNodes[1].actionlist[0].actions[0].targetValue = 10.000000 ;
//~ crealNodes[1].actionlist[0].actions[1].actionType = 1 ;
//~ crealNodes[1].actionlist[0].actions[1].targetID = 6 ;
//~ crealNodes[1].actionlist[0].actions[1].targetValue = 10.000000 ;
//~ crealNodes[1].actionlist[0].actions[2].actionType = 1 ;
//~ crealNodes[1].actionlist[0].actions[2].targetID = 7 ;
//~ crealNodes[1].actionlist[0].actions[2].targetValue = 10.000000 ;
//~ crealNodes[1].actionlist[0].actions[3].actionType = 1 ;
//~ crealNodes[1].actionlist[0].actions[3].targetID = 8 ;
//~ crealNodes[1].actionlist[0].actions[3].targetValue = 10.000000 ;
//~ crealNodes[1].actionlist[0].actions[4].actionType = 1 ;
//~ crealNodes[1].actionlist[0].actions[4].targetID = 9 ;
//~ crealNodes[1].actionlist[0].actions[4].targetValue = 10.000000 ;
//~ crealNodes[1].actionlist[0].actions[5].actionType = 1 ;
//~ crealNodes[1].actionlist[0].actions[5].targetID = 10 ;
//~ crealNodes[1].actionlist[0].actions[5].targetValue = 10.000000 ;
//~ crealNodes[1].actionlist[0].numberOfConditions = 1;
//~ crealNodes[1].actionlist[0].conditions[0].field = 11 ;
//~ crealNodes[1].actionlist[0].conditions[0].relationType = 2 ;
//~ crealNodes[1].actionlist[0].conditions[0].value = 1.000000 ;
//~ crealNodes[2].numberOfProperties = 7;
//~ crealNodes[2]->properties[0] = &crealProperties[5];
//~ crealProperties[5] = 60.000000;
//~ crealNodes[2]->properties[1] = &crealProperties[6];
//~ crealProperties[6] = 60.000000;
//~ crealNodes[2]->properties[2] = &crealProperties[7];
//~ crealProperties[7] = 60.000000;
//~ crealNodes[2]->properties[3] = &crealProperties[8];
//~ crealProperties[8] = 60.000000;
//~ crealNodes[2]->properties[4] = &crealProperties[9];
//~ crealProperties[9] = 60.000000;
//~ crealNodes[2]->properties[5] = &crealProperties[10];
//~ crealProperties[10] = 60.000000;
//~ crealNodes[2]->properties[6] = &crealProperties[11];
//~ crealProperties[11] = 60.000000;
		exit(EXIT_SUCCESS);	
}
