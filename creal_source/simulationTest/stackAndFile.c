#include <stdio.h> 
#include <stdlib.h> 
#include <sys/time.h>
#include <sys/resource.h>


FILE ***returnFileStructures(uint count, uint count2);
void freeFileArray(FILE ***fileArray, uint count);
int setStackSize(uint num);
int createFiles(FILE ***fileArray, uint count);
int closeFiles(FILE ***fileArray, uint count);



int main()
{
	//~ uint_fast64_t
	
				setStackSize(64);

				FILE ***TEST = returnFileStructures(4, 4);
				
				createFiles(TEST,4);
								
				closeFiles(TEST,4);
	
				freeFileArray(TEST,4);
							
				exit(EXIT_SUCCESS);
				


}


FILE ***returnFileStructures(uint count, uint count2)
{
	int i = 0;
	
	FILE ***mainFileArray = malloc(sizeof(FILE *) * count);
	
	for(; i < count; i++)
	{
		
		mainFileArray[i] = malloc(sizeof(FILE ) * count2);
	
	}
	
	
	return mainFileArray;
	
}


void freeFileArray(FILE ***fileArray, uint count)
{
	int i = 0;
	
	
	for(; i < count; i++)
	{
	
		free(fileArray[i]);
	}
	
	
			free(fileArray);
	
}



int setStackSize(uint num)
{
	const rlim_t kStackSize = num * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl;
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result == 0)
    {
        if (rl.rlim_cur < kStackSize)
        {
            
            /*printf("Current Stack : %d\n",rl.rlim_cur);
			  printf("New Stack : %d\n",kStackSize);
            */
            
            rl.rlim_cur = kStackSize;
            result = setrlimit(RLIMIT_STACK, &rl);
            if (result != 0)
            {
                return -1;
            }
        }
    }
	
	
	return 0;
}


int createFiles(FILE ***fileArray, uint count)
{	
	int i = 0;
	char filename[256];
		
		for (; i < count; i++)
		{
			sprintf(filename,"test_%d.dat",i);
			fileArray[i][i] = fopen(filename,"w");
			if (fileArray[i][i] == NULL)
			{
				return -1;
			}

		}
		
		return 0;
}

int closeFiles(FILE ***fileArray, uint count)
{	
	int i = 0;
	
		
		for (; i < count; i++)
		{

			
				fclose(fileArray[i][i]);
	
		}
		
		return 0;
}
