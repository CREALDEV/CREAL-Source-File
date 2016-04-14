//this is used to take json data and turn them into creal nodes

#include <jansson.h> //json interpreter


/* The structure looks like this:
 * 
 * 
 *		char name[64]; //this is the name of the node
		long value; //this is the value that will be changed
		uint index; //this is the index of the array that will be changed
		char directive; // this is used to initiate a certain routine
		
		* 
		* 
		* 
*/

crea_node creatCreaNodes(char const *filePath, int *N)
{
	
	json_t *root;
    json_error_t error;
	FILE *fp;
	char ch='\0';
	
	
	int charCount = 0;
		
		
		fp=fopen(filePath, "r") ;
	
		if (fp == NULL)
		{
			return NULL;
		}
	
					while(ch!=EOF) 
					{
					
						ch=fgetc(fp);
						charCount++;
					}
					
			fclose(fp);
			
	char jsonFileData[charCount];
	
	fp=fopen(filePath, "r");
	int num = fread(jsonFileData,1,charCount,fp);
		if (fp == NULL)
		{
		return NULL;
		}
		
		fclose(fp);
		
			root = json_loads(jsonFileData, 0, &error);
				if(!root)
				{		
					return NULL;
				}
					
						if(!json_is_array(root))
						{
							return NULL;
						}
	
		int i = 0;
	
		json_t *innerarray, *outerarray;
			char const *message_text;
		int arraySize = json_array_size(root);
		crea_node tempCreaNodes = returnCreaNodeMemHost(arraySize);
			
			
			
		//~ *passedCreaNode = returnCreaNodeMemHost(arraySize);
		//~ *passedCreaNode = (crea_node) calloc(arraySize, sizeof(pre_crea_node));	
		
		
		for(i = 0; i < arraySize; i++)
		{
			outerarray = json_array_get(root, i);
				
				if(!json_is_array(outerarray))
				{
						return NULL;
				}
				
										//the node name
										innerarray = json_array_get(outerarray, 0);
										message_text = json_string_value(innerarray);
																				
											if(message_text == NULL)
											{
													return NULL;
											}
										strcpy(tempCreaNodes[i].name,message_text);
										
										//the node value THEY ARE LONGS NOW!
										innerarray = json_array_get(outerarray, 1);
										message_text = json_string_value(innerarray);
										
										if(message_text == NULL)
											{
													return NULL;
											}
										tempCreaNodes[i].value = atol(message_text);
										
										//the node change index
										innerarray = json_array_get(outerarray, 2);
										message_text = json_string_value(innerarray);
										
										if(message_text == NULL)
											{
													return NULL;
											}
										tempCreaNodes[i].index = (uint)atoi(message_text);

										//the node directive
										innerarray = json_array_get(outerarray, 3);
										message_text = json_string_value(innerarray);
										
										if(message_text == NULL)
											{
													return NULL;
											}
										tempCreaNodes[i].directive = (char)atoi(message_text);


				
				//change the bottom from iteration to just adding the values in manually... there are only four values from json to add
							//~ for (k = 0 ; k < json_array_size(outerarray); k++)
							//~ {
										
								
							//~ }

		}
		
					json_decref(root);
	
	*N = arraySize;
	return tempCreaNodes; //return this back to the calling function
	
}
