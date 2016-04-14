

//~ struct propertiesArray
//~ {
	//~ int elementCount;
	//~ 
	//~ long value;
	//~ 
	//~ char threadLock; //used to lock the thread
//~ };

//~ 
//~ struct alpha_node
//~ {
	//~ int elementCount;
	//~ 
	//~ char id[5]; //used to denote the identification
	//~ char threadLock; //used to lock the thread
	//~ struct actionsArray actions[];
	//~ struct propertiesArray properties[];
//~ };


struct timeStructure
{
	uint hours;
	uint minutes;
	uint seconds;
	double milliseconds;
};



struct bracketFindingStructForActionHelper
{
		
		uint beginning, end; //this is used to find the beginning and end of the brackets
		uint targetID; //this is used to store the target id
};

struct pre_actions { 
		//this are actions added to the action list
		char actionType; //this is used for the action type
		uint targetID; //the target id of the node
		
		creal_d targetValue; //the target id of the node
		
	//~ char expressionString[2048]; //this is used to actually utilize the expression
	//~ char stringIsNull; //this is used to tell if the string is a nullified value
	//~ unsigned char isNumber; //this allows us to skip properties- really tells us if the property is real or not.
	//~ uint countOfBracketList; //count for something 
	//~ struct bracketFindingStructForActionHelper endBeginOfBrackets[128]; //this helps with processing
		
	
			

};

struct pre_conditionlist { 
		
		char relationType; //this is used for the action type
		uint field; 
		creal_d value; //this is used to compare to the previous element for conditions 
		
		
		//~ char expressionString[2048]; //this is used to actually utilize the expression
	//~ char stringIsNull; //this is used to tell if the string is a nullified value
	//~ unsigned char isNumber; //this allows us to skip properties- really tells us if the property is real or not.
	//~ uint countOfBracketList; //count for something 
	//~ struct bracketFindingStructForActionHelper endBeginOfBrackets[128]; //this helps with processing
			//~ uint creaNodeIndex; //used to find the index of the crea node
				//~ 
					//~ uint propertyIndex; //used to find the index of the property of the crea node 
	//~ 
							
						
						
									//this is the condition list data structure	
}; 



struct pre_actionlist { 
		
		char actionType; //this is used for the action type
		uint targetID; //the target id of the node
		creal_d targetValue; //the target id of the node
		uint actionListIsNull;
		uint conditionListIsNull;
			
						//~ uint creaNodeIndex; //used to find the index of the crea node
			
						//~ uint propertyIndex; //used to find the index of the property of the crea node 
	
						uint numberOfConditions; //used to tell how many elements are in the conditions
					
						uint numberOfActions; //used to tell how many elements are in the properties
						
						struct pre_actions actionsList[128];
						
						struct pre_conditionlist conditionlist[128]; //this is the main conditionlist of a crealnode, these go with actions	
						
						
							//this is the action list data structure	
}; 


struct crealNode { 
	
/* May need to modify the datatypes */ 
			
	uint numberOfProperties; //used to tell how many elements are in the properties
	
	uint numberOfActions; //used to tell how many elements are in the properties
	
		creal_t *properties; //these are the properties right here
	
			creal_t *cudaProperties; //these are the properties for cuda
	
				struct pre_actionlist *actionlist; //this is the main actionlist of a crealnode
		

					//this is the creal node data structure
	
}; 




struct helperDataForActions {
	
	//this is data used to help process the creal data
	
	char expressionString[2048]; //this is used to actually utilize the expression
	char stringIsNull; //this is used to tell if the string is a nullified value
	unsigned char isNumber; //this allows us to skip properties- really tells us if the property is real or not.
	uint countOfBracketList; //count for something 
	struct bracketFindingStructForActionHelper *endBeginOfBrackets; //this helps with processing
	
	
	
};

struct helperDataForProperties {
	
	//this is data used to help process the creal data
	
	char expressionString[2048]; //this is used to actually utilize the expression
	char stringIsNull; //this is used to tell if the string is a nullified value
	unsigned char isNumber; //this allows us to skip properties- really tells us if the property is real or not.
	uint countOfBracketList; //count for something 
	struct bracketFindingStructForActionHelper *endBeginOfBrackets; //this helps with processing
	
	
};


struct executionStructure
{
	//this structure is used to make execution calls onto the cuda kernels
	
	uint actionType;
	uint targetID;
	uint targetValue;
	
	
	
};

struct actionConditionsMetaHelp
{
	
	//these were just added in order to make way for more conditions
	
	uint countOfActions;
	struct helperDataForActions actionStrings[128];
	
	uint countOfConditions;
	struct helperDataForActions conditionStrings[128];
	
};

struct threadData
{
	creal_t properties[];
	struct helperDataForProperties propertiesHelper[];
	uint count;
	uint cpuNum;	
	char *threadPipePaths[];
	
};
