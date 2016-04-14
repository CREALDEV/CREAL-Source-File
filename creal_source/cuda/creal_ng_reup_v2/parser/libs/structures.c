struct pre_conditionlist { 
		
		char relationType; //this is used for the action type
		
			uint creaNodeIndex; //used to find the index of the crea node
				
					uint propertyIndex; //used to find the index of the property of the crea node 
	
							double compareValue; //this is used to compare to the previous element for conditions 
						
									//this is the condition list data structure	
}; 



struct pre_actionlist { 
		
		char actionType; //this is used for the action type
		
			uint creaNodeIndex; //used to find the index of the crea node
			
				uint propertyIndex; //used to find the index of the property of the crea node 
	
					uint numberOfConditions; //used to tell how many elements are in the properties
						
						struct pre_conditionlist *conditionlist; //this is the main conditionlist of a crealnode, these go with actions	
						
							//this is the action list data structure	
}; 


struct crealNode { 
	
/* May need to modify the datatypes */ 
			
	uint numberOfProperties; //used to tell how many elements are in the properties
	
	uint numberOfActions; //used to tell how many elements are in the properties
	
		double *properties; //these are the properties right here
	
			double *cudaProperties; //these are the properties for cuda
	
				struct pre_actionlist *actionlist; //this is the main actionlist of a crealnode
		

					//this is the creal node data structure
	
}; 




