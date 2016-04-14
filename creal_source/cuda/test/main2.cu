#include <stdio.h> //standard library
#include "/usr/include/linux/cuda.h" //cuda library
#include <stdlib.h>	
#include <unistd.h>

typedef unsigned int uint;

__global__ void kernel(int* A, int* B, int* C)
{
	
			int i = threadIdx.x; //this is used as a thread identifier 
			
			C[i] = A[i] + B[i];
	
}




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
 
void addNumber(int* var, int count)
{
	for (int $i = 0; $i < count; $i++)
	
	{
		var[$i] = 5;
		
	}
	
}
void zeroArray(int* var, int count)
{
	for (int $i = 0; $i < count; $i++)
	
	{
		var[$i] = 0;
		
	}
	
}

int sumArray(int* var, int count)
{
	int summation = 0;
	
	for (int $i = 0; $i < count; $i++)
	
	{
		summation += var[$i];
		
	}
	
	return summation;
	
}

int main (void)
{
	
	int N = 256; //N constant
	int sum; //the sum
	int* hostMem0 = (int*)malloc(sizeof(int) * N); //allocate one element of host memory
	int* hostMem1 = (int*)malloc(sizeof(int) * N); //allocate one element of host memory
	int* hostMem2 = (int*)malloc(sizeof(int) * N); //allocate one element of host memory
	
	
	
	
	addNumber(hostMem0,N);
	addNumber(hostMem1,N);
	zeroArray(hostMem2,N);
	
	
	
	
	int* cudaMem; //allocate one element of device memory
	
	cudaMalloc(&cudaMem, sizeof(int) * N); //this will allocate memory inside of the cuda device
    
	//~ hostMem[0] = 0; //just assign the host memory value to zero
    //~ cudaMemcpy(cudaMem,hostMem,sizeof(int) * N,cudaMemcpyHostToDevice); //copy memory from host to the device
			sum = sumArray(hostMem2,N);
			printf("Value %d\n",sum);
		
			dim3 threads(N,N);
			
			kernel<<<1,threads>>>(hostMem0,hostMem1,cudaMem); //call the cuda kernel function
			
			
			printf("Sleeping for 2 \n"); //sleeping
			sleep(2); //sleep for 5 seconds
			
			
			cudaMemcpy(hostMem2,cudaMem,sizeof(int) * N,cudaMemcpyDeviceToHost); //copy memory from device to the host
			
			
			sum = sumArray(hostMem2,N);
			
			printf("Value %d\n\n",(uint)sum); //the new value
			
			//~ cudaMemcpy(cudaMem,hostMem,sizeof(int) * 1,cudaMemcpyHostToDevice); //copy memory from host to the device
		
			
			
				free(hostMem0); //free the host memory
				free(hostMem1); //free the host memory
				free(hostMem2); //free the host memory
				
				cudaFree(cudaMem); //free device memory
		
    
				return 0; //return 0
		

}
