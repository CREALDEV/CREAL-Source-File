#ifndef CREAL_NG_LIB
/* This is the main library for Creal_ng */

#define CREAL_NG_LIB /* Make sure we don't have any damn duplicates */

/* Pre-Processor Macros */
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


/* Data types and structure delcaration */
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


 
/* Declaring the main functions for this code */ 


#endif //end the if statements to stop duplications
