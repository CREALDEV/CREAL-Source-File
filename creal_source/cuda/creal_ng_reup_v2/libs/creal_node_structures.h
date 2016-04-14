/* These are the data structures for the application */


struct pre_actions { 
		//this are actions added to the action list
		char actionType; //this is used for the action type
		uint targetID; //the target id of the node
		creal_d targetValue; //the target id of the node
		
};



struct pre_conditionlist { 
		
		char relationType; //this is used for the action type
		uint field; 
		creal_d value; //this is used to compare to the previous element for conditions 
		
}; 



struct pre_actionlist { 
		
		char actionType; //this is used for the action type
		uint targetID; //the target id of the node
		creal_d targetValue; //the target id of the node
		uint actionListIsNull;
		uint conditionListIsNull;
		uint numberOfConditions; //used to tell how many elements are in the conditions		
		uint numberOfActions; //used to tell how many elements are in the properties
			
						
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
	
	//~ char expressionString[2048]; //this is used to actually utilize the expression
	char stringIsNull; //this is used to tell if the string is a nullified value
	unsigned char isNumber; //this allows us to skip properties- really tells us if the property is real or not.
	uint countOfBracketList; //count for something 
	struct bracketFindingStructForActionHelper *endBeginOfBrackets; //this helps with processing
	
	
	
};

struct helperDataForProperties {
	
	//this is data used to help process the creal data
	
	//~ char expressionString[2048]; //this is used to actually utilize the expression
	char stringIsNull; //this is used to tell if the string is a nullified value
	unsigned char isNumber; //this allows us to skip properties- really tells us if the property is real or not.
	uint countOfBracketList; //count for something 
	struct bracketFindingStructForActionHelper *endBeginOfBrackets; //this helps with processing
	
	
};



struct threadData
{
	creal_t properties[];
	struct helperDataForProperties propertiesHelper[];
	uint count;
	uint cpuNum;	
	char *threadPipePaths[];
	
};
