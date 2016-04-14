//this file is just used to test out the json stuff

#include <stdio.h> //standard library
#include <stdlib.h>	
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "jsmn.c" //a json parser that is fast and efficient
#define defaultJsonFile "jsonFile.json"

int main(void)
	{	
		
		
		puts("This is a json tester"); // tittle
		
		/* file openning stuff */
		FILE *jsonFileHandle;
		char *line = NULL;
        size_t len = 0;
        ssize_t read;
        jsonFileHandle = fopen(defaultJsonFile, "r");
           if (jsonFileHandle == NULL)
           {
               exit(EXIT_FAILURE);
		   }
		   
		/* Json stuff added here */ 			
		int errorTrap;
		jsmn_parser jsonParser;
		jsmntok_t jsonToken[10];
		const char *jsonString; //a json stirng 
		int totalStringSpace;
		char tempString[48];
		char *temp;
		/*parsing the files */ 
		
		while ((read = getline(&line, &len, jsonFileHandle)) != -1) {
               //~ printf("Retrieved line of length %zu :\n", read);
               //~ printf("%s", line);
				
				jsonString = line;
				jsmn_init(&jsonParser); //initializes the jsmn parser pointer *Must be done after string declaration
				puts(line);
				errorTrap = jsmn_parse(&jsonParser, jsonString, jsonToken, 10);
				if ( errorTrap >= 0 )
				{
					printf("%d :: Success\n",errorTrap);
					int i = 0;
					for (; i < 10; i++)
					{
						
						totalStringSpace = (jsonToken[i].start - jsonToken[i].end);
						//~ strncpy(tempString, line+10, totalStringSpace);
						printf("%s", line);


						//~ memcpy( tempString, &line[2], totalStringSpace );
						//~ tempString[totalStringSpace] = '\0';

						//~ printf("Start : %d\n",jsonToken[i].start);
						//~ printf("End : %d\n",jsonToken[i].end);
						//~ printf("Size : %d\n",jsonToken[i].size);
						//~ 
						
					}
				}
				else
				{
					puts("Error parsing the json string");
					
					
				}
				
				
				}
		
		
			
		jsonString = "errs";
		//~ js = "{}";
		
		
		
		fclose(jsonFileHandle); // close the json file handle
		free(line); //free this line
        exit(EXIT_SUCCESS); // close the json file handle

	}


/*

The json parser will take a string and parse the json stuff right out of there, 
and then return where I can find the coordinates with the substring to extract the data 
* ############### jsmn tokent structure below
* 
* typedef struct {
	jsmntype_t type;
	int start;
	int end;
	int size;
#ifdef JSMN_PARENT_LINKS
	int parent;
#endif
} jsmntok_t;
* 
* 
*/

