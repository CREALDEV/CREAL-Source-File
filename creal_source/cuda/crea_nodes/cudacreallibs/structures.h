//this is where the creal data structures are located at and their functions
	 struct node
	 {
		 
		 
		char name[64]; //this is the name of the node
		long value; //this is the value that will be changed
		uint index; //this is the index of the array that will be changed
		char directive; // this is used to initiate a certain routine
		
		
		 
	 };
	 
		typedef struct node pre_crea_node; 
		typedef pre_crea_node *crea_node;


	crea_node returnCreaNodeMemHost(int num)
	{		
		//remember you have to cast malloc with cuda	
		
		return (crea_node) calloc(num, sizeof(pre_crea_node));	
	}
