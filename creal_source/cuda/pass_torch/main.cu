#include <stdio.h> //standard library
#include "/usr/include/linux/cuda.h" //cuda library
#include "simplePrintf/cuPrintf.cu" //including the cuda simple printf stuff
#include <stdlib.h>	 //standard lib
#include <unistd.h> //universal standard

#define BLOCK_SIZE = 16 //constant
//just use this above as a constant to a thread block


__global__ void printThreadStuff()
{
	
			//~ int iThreadID = threadIdx.x; //this is used as a thread identifier 
			int nTotalThreads = blockDim.x;	// Total number of active threads
			unsigned int ThreadIDX= threadIdx.x+blockDim.x*blockIdx.x;
			
			
			__shared__ int sharedArray[1000]; //a shared value
			 
			
				
				
		
				sharedArray[0] = 0; //zero out the value
				
				
				
				for(; sharedArray[nTotalThreads - 1] < 1000000000;)
				{
		
					for (int i = 1; i < nTotalThreads; i++)
					{
						if (ThreadIDX == i)
						{
							sharedArray[ThreadIDX] = sharedArray[ThreadIDX - 1] + 1;
						
						}
						
						__syncthreads(); //syncs the threads up
					}
						sharedArray[0] = sharedArray[nTotalThreads - 1]; //zero out the value
						__syncthreads(); //syncs the threads up
				}		
				
				
				
				if(ThreadIDX == 0) //only use the first thread
				{
					
					cuPrintf("Total passed thread: %d\n",sharedArray[nTotalThreads - 1] );
				}
}


		/*more things need to be done right here 
		 * you have to c111ast malloc in order to pass some stuff
		 * ridiculous stuff going on
		 * 
		 * __shared__ float max[256]; // add this somewhere in new code base.. this is for a shared memory object
		 * 
		 * int nTotalThreads = blockDim.x;	// Total number of active threads
		 * __syncthreads(); //find out more about this function
		 * 	
		 * */




		typedef unsigned int uint; //unsigned


		int main(int argc, char **argv)
		{
		

			if ( argc != 2 )
			{
				
				
					//~ argc is actually whats on the command line..
				
					printf("Sorry %s \n", argv[0]); //show errata for the program
				
					
					
				
			}

		//else run the rest of the program
		
		else
		{
			
				//BEGIN//
				
					cudaPrintfInit(); //initializes the cuda printf function
			
					//~ int* tmpVar = (int*)malloc(sizeof(int) * 1); //allocate one element of host memory
					//~ tmpVar = (int*)argv[1]; //cast the argument as a integer pointer
					//~ printf("Doing this %s\n", argv[1] ); // for will print out the first argument 
		
					printThreadStuff<<<1,10>>>(); //call the cuda kernel function	
				
					cudaPrintfDisplay(stdout, true); //displays the cuda printf functionality
			
					//~ free(tmpVar); // free a temporary variable
				
				
				//END//
				
					cudaPrintfEnd(); //ends the cuda printf function
				
				
				return 0; //return 0
				
				
		}


}
	
