/* Testing passing structures in cuda*/ 
//~ http://stackoverflow.com/questions/5670430/error-when-passing-pointer-to-struct-to-function-in-c  ~ this url has a nice solution

#include <stdio.h> //standard library
#include "/usr/include/linux/cuda.h" //cuda library
#include <stdlib.h>	
#include <unistd.h>
#include <string.h>
#include <time.h>
//~ #include "simplePrintf/cuPrintf.cu" //including the cuda simple printf stuff

#include "libcudacreal.h" //a json parser that is fast and efficient


//~ char const ADD = 0x01;
//~ char const DEL = 0x02;

//~ char const MOV = 0x03;
//~ char const MUL = 0x04;
//~ char const IOU = 0x05;


	 //~ struct node
	 //~ {
		 //~ 
		 //~ 
		//~ char *name; //this is the name of the node
		//~ int value; //this is the value that will be changed
		//~ uint index; //this is the index of the array that will be changed
		//~ char directive; // this is used to initiate a certain routine

		//~ 
		 //~ 
	 //~ };
	 //~ 
		//~ typedef struct node pre_crea_node; 
		//~ typedef pre_crea_node *crea_node;


	crea_node returnCreaNodeMemHost(uint num)
	{
		
		
		
		
		//remember you have to cast malloc with cuda	
		//~ return (crea_node)malloc(sizeof(pre_crea_node) * num); //make sure you allocate
		return (crea_node) calloc(num, sizeof(pre_crea_node));	
	}

	struct preNodeContainer
	{
		uint count; // this is the number of nodes
		crea_node creaNodeArray;
	};
		
	
	

// below is the main kernel for the program

	__global__ void kernel(crea_node creaNodeStructure)
		{

				int thrI = threadIdx.x; //this is used as a thread identifier 	
				int i = blockIdx.x * blockDim.x + threadIdx.x;
				
				int dI = creaNodeStructure[thrI].index;
				
				if(creaNodeStructure[i].directive == ADD) //this is for adding
					{
						
					creaNodeStructure[dI].value++;	
					//~ cuPrintf("Add Recieved\n");
						
						
					
				
					}
				
				if(creaNodeStructure[i].directive == DEL) //this is for deletion
					{
						creaNodeStructure[dI].value--;	
						
						
						//~ cuPrintf("Delete Recieved\n");
					
					
					}
					__syncthreads();
					//~ 
				//~ cuPrintf("Current Thread: %d\n", creaNodeStructure->value);
				
				//~ creaNodeStructure[thrI].value = 0;
				
				
		
		}



void freeNodeMemories(crea_node hostNode, crea_node deviceNode)
{
			free(hostNode); //free the host memory	
			cudaFree(deviceNode); //free the device memory
}


int main (void)
{
					
	/* General app stuff */				
	//~ int errorTrap; //this is used for checking errors
	

		//~ cudaPrintfInit(); //initializes the cuda printf function
		int N = 0;
	
		
		crea_node hostNode = creatCreaNodes("jsonTest.json",&N);
		crea_node deviceNode;
		
		

		
		//~ 
		//~ populateCreaNodeStructure(&hostNodeStructure,&deviceNodeStructure,N); //this adds elements to the nodes
		
		cudaMalloc(&deviceNode, sizeof(pre_crea_node) * N);
		
		//~ cudaMemcpy(&deviceNodeStructure,&hostNodeStructure,sizeof(hostNodeStructure) * 1,cudaMemcpyHostToDevice); //copy memory from host to the device
		
		cudaMemcpy(deviceNode,hostNode,sizeof(pre_crea_node) * N,cudaMemcpyHostToDevice); //copy memory from host to the device
		printf("%d",N);
		
		puts("\n\n");	
		
		
		for (int i = 0; i < N; i++)
		{
			
			printf("%d\n",hostNode[i].value);
			
			
		
		
		}
			
			puts("\n\n");	
		
		
		//~ processCreaNodes<<<1,N>>>(deviceNodeStructure);
		kernel<<<1,N>>>(deviceNode);
		
		//~ cudaPrintfDisplay(stdout, true); //displays the cuda printf functionality
		
		//~ cudaMemcpy(&hostNodeStructure,&deviceNodeStructure,sizeof(hostNodeStructure) * 1,cudaMemcpyDeviceToHost); //copy memory from device to the host
		
		//~ cudaPrintfEnd(); //ends the cuda printf function
		
		cudaMemcpy(hostNode,deviceNode,sizeof(pre_crea_node) * N,cudaMemcpyDeviceToHost); //copy memory from device to the host	
		
		
		for (int i = 0; i < N; i++)
		{
			
			printf("%d\n",hostNode[i].value);
			
			
		
		
		}
		
			
	
			//~ /*this is for testing purposes */	
	
			//~ for (int i = 0; i < hostNodeStructure.count; i++)
			//~ {
				//~ printf("%d\n",hostNodeStructure.creaNodeArray[i].value);
				//~ 
			//~ }
			//~ 
			
		
			
					
			
			//~ free(hostNode);
			freeNodeMemories(hostNode,deviceNode);
			
			return 0; //return 0 to the OS if everything was alright 
		
}


	
