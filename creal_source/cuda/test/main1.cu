
#include <stdio.h> //standard library
#include "/usr/include/linux/cuda.h" //cuda library
#include <stdlib.h>	
#include <unistd.h>

__global__ void kernel(int* A)
{
	
	A[0]++;
	
}

//~ __global__ void vecAdd(int* A, int* B)
//~ {
	//~ 
	//~ 
//~ }



//~ __global__ void passTheTorch(int* A)
//~ {
	//~ 
		//~ int i = threadIdx.x; //this is used as a thread identifier 
		//~ 
//~ }


/*more things need to be done right here 
 * you have to cast malloc in order to pass some stuff
 * ridiculous stuff going on
 * 
 * 
 * 
 * 
 * 
 * 	
 * */
 
 
int main (void)
{
	
	
	int* hostMem = (int*)malloc(sizeof(int) * 1); //allocate one element of host memory
	int* cudaMem; //allocate one element of device memory
	cudaMalloc(&cudaMem, sizeof(int) * 1); //this will allocate memory inside of the cuda device
    
	hostMem[0] = 0; //just assign the host memory value to zero
    cudaMemcpy(cudaMem,hostMem,sizeof(int) * 1,cudaMemcpyHostToDevice); //copy memory from host to the device
    
    
		for(int i = 0; i < 1000; i++) //iterate 1000 times
		
		{
			printf("Value %d\n",hostMem[0]);
    
			kernel<<<1,1>>>(cudaMem); //call the cuda kernel function
			cudaMemcpy(hostMem,cudaMem,sizeof(int) * 1,cudaMemcpyDeviceToHost); //copy memory from device to the host
			
			printf("Sleeping for 2 \n"); //sleeping
			sleep(2); //sleep for 5 seconds
			printf("Value %d\n\n",hostMem[0]); //the new value
			
			cudaMemcpy(cudaMem,hostMem,sizeof(int) * 1,cudaMemcpyHostToDevice); //copy memory from host to the device
		
		}
			
				free(hostMem); //free the host memory
				cudaFree(cudaMem); //free device memory
		
    
    return 0; //return 0
		

}
