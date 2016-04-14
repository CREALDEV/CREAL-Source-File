void processCudaProperties(creal_t a, creal_t b);

__device__ int get_global_index(void)
{
	//this function is super nice!
	//a functional approach to all the hard work

	return blockIdx.x * blockDim.x + threadIdx.x;



}


//these cuda kernels are being used to transform the current json data (depracted)

/* Actions */ 
//////////////////////////////////////////
__device__ creal_t nothing(creal_t initialValue, creal_t modifier)
{
	modifier = 0;
	
	return (initialValue + modifier);
}


__device__ creal_t increase(creal_t initialValue, creal_t modifier)
{
	
	return (initialValue + modifier);
}



__device__ creal_t decrease(creal_t initialValue, creal_t modifier)
{
	
	return (initialValue - modifier);
}


__global__ void change(void)
{
	
	
}

__global__ void maintain(void)
{
	
	
}

__global__ void transport(void)
{
	
	
}

__device__ int test(void)
{
	
		return 1;
}

		/* IT WORKS */


		//constant function look up tables
	
			//~ __device__ int (*something[2])(void) = {&test, &test}; //what the fuck is this?




			__constant__ creal_t (*actionLookUpTable[6])(creal_t , creal_t) = 
			{
			
				&nothing,  //this function does nothing
				
				&increase, //this function simply increases
				
				&decrease, //this function decreases
				
				//&change,   //this function changes
				
				//&maintain, //this functions maintains
				 
				//&transport //this functions transports
			}; 







__global__ void actionKernel(int *i)
{
	
		
		
		*i++;
			
			//~ *i = actionLookUpTable[ADD](2,6);
			
			

		__syncthreads(); //makes sure all of the threads are synchronized
}


__global__ void testCrealProperties(creal_t *properties)
{
	
		int cudaThreads = get_global_index();
		
		
			int temp = properties[cudaThreads]; //temporary 
			
			properties[cudaThreads] = actionLookUpTable[INCREASE](temp,1);
			//~ cuPrintf("Total passed thread: %d\n", 30);
			

		__syncthreads(); //makes sure all of the threads are synchronized
}



__global__ void executeCudaPartOfCreal(creal_t *properties, struct executionStructure executionArray[] )
{
	//This is the main execution kernel
			uint cudaThreads = get_global_index();
			uint actionType, targetID, targetValue, temp;
			actionType = targetID = targetValue = temp = 0;
			//~ 
			actionType = executionArray[cudaThreads].actionType;
			targetID = executionArray[cudaThreads].targetID;
			targetValue = executionArray[cudaThreads].targetValue;
			//~ 
			temp = properties[targetID]; //temporary 
			//~ 
			properties[targetID] = actionLookUpTable[actionType](temp,1);
			//~ 
			printf("Property Value: %f, At cuda thread: %u, Action Type : %u \n", properties[cudaThreads], cudaThreads,actionType);
			
			//~ printf("cuda property value: %i  , in thread: %i , data in executionStructure : %d\n", 
			//~ properties[cudaThreads], cudaThreads, executionArray[cudaThreads].targetValue);

			__syncthreads(); //makes sure all of the threads are synchronized
}



__global__ void testCudaPrintf(creal_t *properties, struct executionStructure executionArray[] )
{
	uint cudaThreads = get_global_index(); //this allows us to get an indice
	
		printf("Hello From Cuda\n: %d", cudaThreads);
	
}



////////////////////////////////////////////////////



//~ char const NON = 0x00; //nothing a type of NULL action
//~ char const ADD = 0x01; //used for addition
//~ char const DEL = 0x02; //used for deletion
//~ char const CHG = 0x03; //used for changing
//~ char const MAI = 0x04; //used for maintaining
//~ char const TRA = 0x05; //used for transporting

////////////////////////////////////////////////////
/* Stuff for function pointers */




//////////////////////////////////////////
/*These are actions above */




//////////////////////////////////////////



//~ int equal(int a, int b);
//~ int notEqual(int a, int b);
//~ int greater(int a, int b);
//~ int lesser(int a, int b);
//~ int greaterEqual(int a, int b);
//~ int lesserEqual(int a, int b);
//~ 

