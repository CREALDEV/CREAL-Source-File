#include <stdio.h> //standard library
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h> //for file descriptor stuff


#include "struct_definitions.h" //struct definitions

int printOutStaticActionList(uint actionCount, uint conditionCount,  FILE **stream )
{
	
	/* This is where we pring out what the hell is going on here */
	fprintf(*stream, " struct pre_actions actionsList[%d]; \n struct pre_conditionlist conditionlist[%d];  \n", actionCount, conditionCount);
	

return 0; //everything is ok
} //this is used to finish the 

						


void main()
{

	puts(PRE_ACTION_STRUCT); //action 
	puts(PRE_CONDITIONLIST_STRUCT); //conditions
	
	
	
	puts(PRE_ACTION_LIST); //the action list
	
	printOutStaticActionList(5, 5,  &stdout ); //this is used to print out the contents of the 
	puts(CLOSE_THE_STRUCT_CURLY); //end the curly brace for action list
	
	


}
