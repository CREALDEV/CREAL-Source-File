#include <stdio.h> //standard library
#include "/usr/include/linux/cuda.h" //cuda library
#include <stdlib.h>	
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "simplePrintf/cuPrintf.cu" //including the cuda simple printf stuff


char const ADD = 0x01;
char const DEL = 0x02;



 struct node
 {
	 
	char *name; //this is the name of the node
	int value; //this is the value that will be changed
	uint index; //this is the index of the array that will be changed
	char directive; // this is used to initiate a certain routine
	struct node *link; //link to a node 
	
	 
 };
 
	typedef struct node pre_crea_node; 
	typedef pre_crea_node *crea_node;


crea_node returnCreaNodeMemHost(uint num)
{
	
	
	//remember you have to cast malloc with cuda	
	//~ return (crea_node)malloc(sizeof(pre_crea_node) * num); //make sure you allocate
	return (crea_node) calloc(num, sizeof(pre_crea_node));	
}




void main()
{
	
	
	
	
	
	
}
