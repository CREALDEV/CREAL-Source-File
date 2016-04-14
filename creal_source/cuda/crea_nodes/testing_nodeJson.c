#include <stdio.h> //standard library
#include "/usr/include/linux/cuda.h" //cuda library
#include <stdlib.h>	
#include <unistd.h>
#include <string.h>
#include <time.h>


#include "libcudacreal.h" //a json parser that is fast and efficient


crea_node addValue(int *N)
{
	crea_node nodeT = returnCreaNodeMemHost(2);
	nodeT[0].value = 9;
	nodeT[1].value = 9;
	
	//~ *nodeT = 
	//~ nodeT[0]->value = 9;
	*N = 450;
	return nodeT;
	
	
}




int main(void)
{
	
	
	
	int hello = 0;
	//~ crea_node mainNodes = addValue(&hello);
	crea_node mainNodes = creatCreaNodes("jsonTest.json",&hello);
	
	//~ int N = creatCreaNodes("jsonTest.json",&hello);
	printf("%d\n",hello);
	//~ if ( N < 0) {puts("FAILED");}
	return 0;
}
