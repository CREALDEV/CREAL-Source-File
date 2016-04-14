/*This is a structure file ment for the creal_ng Binary */

#ifndef CREAL_NG_STRUCTURES 



#define CREAL_NG_STRUCTURES /* Make sure we don't have any damn duplicates */


/*This is the function pointer used for the creal action data, might need to change the parameters eventually 
 * I am probably going to need to actually redo the custom lexx parser in order to utilize this portion of this code.
 * */


typedef creal_t (*actionFunctionPointer)( void); //This is the main function pointer for doing all kinds of things

struct pre_actions { 
		//this are actions added to the action list
		char actionType; //this is used for the action type
		uint targetID; //the target id of the node
		actionFunctionPointer actionFunction; //this is the action function of the creal actions
		creal_t targetValue; //the target id of the node
};

struct pre_conditionlist { 
		uint cID; //this is the condition list id
		char relationType; //this is used for the action type
		uint field; 
		
		creal_t value; //this is used to compare to the previous element for conditions 

}; 

/* This is the action list right here */
struct actionList { 
		uint aID; //this is the action struct id
		uint numberOfConditions; //used to tell how many elements are in the conditions			
		uint numberOfActionItems; //used to tell how many elements are in the properties
						
		pre_conditionlist conditions[5];
		pre_actions actions[5]; 
}; 



struct crealNodeStruct { 
	
		/* May need to modify the datatypes */ 
		
		uint iD; //this is the id
		uint numberOfProperties; //the number of properties
		uint numberOfActions; //the number of actions 
		char notNull; //this is to make sure that the data structure is not null
		
		
		uint pID[5]; //these are the property ids 
		creal_t properties[5]; //these are the properties right here
		struct actionList actionsList[5]; //this is the actions
		
					//this is the creal node data structure
	
}; 



/*
struct pre_actionlist { 
		uint iD;
		char actionListIsNull;
		char conditionListIsNull;
			
						
			
						
							//this is the action list data structure	
}; 

*/


 #endif //end the if statements to stop duplications
