//this is used to take json data and turn them into creal nodes

#include <jansson.h> //json interpreter


int returnNumberOfCrealNodes(json_t **root); //used to return the expression

int returnNumberOfCrealProperties(json_t **root); //returns the number of creal properties
int returnHighestCrealPropertyID(json_t **root); //returns the highest creal property id in the json data
int returnCrealPropertyValues(creal_t propertiesArray[], struct helperDataForProperties propertiesHelper[] ,json_t **root, int numOfCrealNodes); //this returns the json data to the actual array of creal properties
uint returnHighestPropertyStringLength(creal_t propertiesArray[], json_t **root, int numOfCrealNodes);

int returnCrealActionListAndConditions(struct pre_actionlist  actionArrayList[], struct actionConditionsMetaHelp helpersForActions[], struct helperDataForActions helperDataList[], json_t **root, int numOfCrealNodes, struct garbageList **hostGarbage); //this is used for action lists
creal_d evaluateCrealEquation(const char *string, uint indexCpuNum); //this is used to evaluate the equation and return the value

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


creal_t *generateProperties(NULL);


int returnNumberOfCrealNodes(json_t **root)
{
		
		
		return (int) json_array_size(*root);
}

int returnNumberOfCrealProperties(json_t **root)
{
		
	
	json_t *jsonPropertiesList, *temp0; //json properties, actions, etc
			
		int propertiesCount = 0; //this is the property count	
					

	int count = (int) json_array_size(*root); //the count of the elements, for multithreading
	int i = 0;
			for (i = 0; i < count; i++)
			{
				
				temp0 = json_array_get(*root, i); //this is used temporary to get the value for the object

					 if(!json_is_object(temp0))
						{
							//~ printf("Array element : %d is not considered a json object!!\n",i);
							return -1;
						}
						else
						{
							jsonPropertiesList = json_object_get(temp0, "properties");
								 if(!json_is_object(jsonPropertiesList))
								{	
									//not ideal, something weird happens here where I cannot exit out of this fucking thing if something goes sour
									//~ printf("Element : %d contains properties that is not considered a json object!!\n",i);											
									//~ quitWithError("json array element was not an object!"); //this happens when json data is all messed up
								
								}
								else
								{
									//add the accumulations of properties for one unified array
									//elements in the creal stuff should be quick sorted
									
									
									
									propertiesCount += (int) json_object_size(jsonPropertiesList); //increase summation
									
					
									}
			
							
					}
		
		
		
		}
			
			
	return propertiesCount;
}


int returnHighestCrealPropertyID(json_t **root)
{
		
	const char *key = NULL;
	json_t *jsonPropertiesList, *temp0; //json properties, actions, etc
	void *iter; //used for iteration
	
	
					int highestPropertyNumber = 0; //used to compare
					int tempValue = 0; //used for temp value

	int count = (int) json_array_size(*root); //the count of the elements, for multithreading
	int i = 0;
			for (i = 0; i < count; i++)
			{
				
				temp0 = json_array_get(*root, i); //this is used temporary to get the value for the object

					 if(!json_is_object(temp0))
						{
							//~ printf("Array element : %d is not considered a json object!!\n",i);
							return -1;
						}
						else
						{
							jsonPropertiesList = json_object_get(temp0, "properties");
								 if(!json_is_object(jsonPropertiesList))
								{	
									//not ideal, something weird happens here where I cannot exit out of this fucking thing if something goes sour
									//~ printf("Element : %d contains properties that is not considered a json object!!\n",i);											
									//~ quitWithError("json array element was not an object!"); //this happens when json data is all messed up
								
								}
								else
								{
									//add the accumulations of properties for one unified array
									//elements in the creal stuff should be quick sorted
									
										iter = json_object_iter(jsonPropertiesList); //this is needed, the golden ticket
										while(iter)
										{
											key = json_object_iter_key(iter);
											
											tempValue = atoi(key);
											if (tempValue > highestPropertyNumber)
											{
												highestPropertyNumber = tempValue; //assign 
												
											}
											//~ puts(key); //use this to debug the key stuff
											
											
										iter = json_object_iter_next(jsonPropertiesList, iter); //this iterates through the json data	
										}
									
									//~ propertiesCount += (int) json_object_size(jsonPropertiesList); //increase summation
									
					
									}
			
							
					}
		
		
		
		}
		//~ json_decref(jsonPropertiesList); //free jansson parsing data
		//~ json_decref(temp0); //free jansson parsing data
		//~ free(iter); //free jansson parsing data
			
	return highestPropertyNumber; //return the highest number
}

int returnHighestCrealActionID(json_t **root)
{
		
	const char *key = NULL;
	json_t *jsonPropertiesList, *temp0; //json properties, actions, etc
	void *iter; //used for iteration
	
	
					int highestPropertyNumber = 0; //used to compare
					int tempValue = 0; //used for temp value

	int count = (int) json_array_size(*root); //the count of the elements, for multithreading
	int i = 0;
			for (i = 0; i < count; i++)
			{
				
				temp0 = json_array_get(*root, i); //this is used temporary to get the value for the object

					 if(!json_is_object(temp0))
						{
							//~ printf("Array element : %d is not considered a json object!!\n",i);
							return -1;
						}
						else
						{
							jsonPropertiesList = json_object_get(temp0, "action list");
								 if(!json_is_object(jsonPropertiesList))
								{	
									//not ideal, something weird happens here where I cannot exit out of this fucking thing if something goes sour
									//~ printf("Element : %d contains properties that is not considered a json object!!\n",i);											
									//~ quitWithError("json array element was not an object!"); //this happens when json data is all messed up
								
								}
								else
								{
									//add the accumulations of properties for one unified array
									//elements in the creal stuff should be quick sorted
									
										iter = json_object_iter(jsonPropertiesList); //this is needed, the golden ticket
										while(iter)
										{
											key = json_object_iter_key(iter);
											
											tempValue = atoi(key);
											if (tempValue > highestPropertyNumber)
											{
												highestPropertyNumber = tempValue; //assign 
												
											}
											//~ puts(key); //use this to debug the key stuff
											
											
										iter = json_object_iter_next(jsonPropertiesList, iter); //this iterates through the json data	
										}
									
									//~ propertiesCount += (int) json_object_size(jsonPropertiesList); //increase summation
									
					
									}
			
							
					}
		
		
		
		}
			
		//~ json_decref(jsonPropertiesList); //free jansson parsing data
		//~ json_decref(temp0); //free jansson parsing data
		//~ free(iter); //free jansson parsing data
		
	return highestPropertyNumber; //return the highest number
}

int returnCrealPropertyValues(creal_t propertiesArray[], struct helperDataForProperties propertiesHelper[] ,json_t **root, int numOfCrealNodes,garbageList **hostGarbage)
{
		
	const char *key, *key0;
	key = key0  = NULL; //hehe
	json_t *jsonPropertiesList, *temp0, *temp1, *value, *type; //json properties, actions, etc
	void *iter, *iter0; //used for iteration
	char *text = NULL; //this is used to slurp all of the json data into a string
	char *text2 = NULL; //this is used to slurp all of the json data into a string
	int stringLength = 0;
	int check = 0;
	//~ int count = (int) json_array_size(*root); //the count of the elements, for multithreading
	int i = 0;
	int n = 0;
			for (i = 0; i < numOfCrealNodes; i++)
			{
				
				temp0 = json_array_get(*root, i); //this is used temporary to get the value for the object

					 if(!json_is_object(temp0))
						{
							//~ printf("Array element : %d is not considered a json object!!\n",i);
							return -1;
						}
						else
						{
							jsonPropertiesList = json_object_get(temp0, "properties");
								 if(!json_is_object(jsonPropertiesList))
								{	
									//not ideal, something weird happens here where I cannot exit out of this fucking thing if something goes sour
									//~ printf("Element : %d contains properties that is not considered a json object!!\n",i);											
									//~ quitWithError("json array element was not an object!"); //this happens when json data is all messed up
								
								}
								else
								{
									//add the accumulations of properties for one unified array
									//elements in the creal stuff should be quick sorted
									
										iter = json_object_iter(jsonPropertiesList); //this is needed, the golden ticket
										while(iter)
										{
											key = json_object_iter_key(iter);
											temp1 = json_object_iter_value(iter);
												
											if(!json_is_object(temp1))
												{												
												
														return -1; //this happens when json data is all messed up
												
												}
												else
												{
													//~ iter0 = json_object_iter(temp1); //this is needed, the golden ticket
													//~ while(iter0)								
													//~ {
															//~ key0 = json_object_iter_key(iter0); //this is the key 
															//~ value = json_object_iter_value(iter0); //the value of the json key right here
													//~ 
														//~ if(!json_is_string(value))
									//~ 
														//~ {												
																	//~ return -1; //this happens when json data is all messed up
														//~ 
														//~ }
														//~ else
														//~ {			
															
														type =	json_object_get(temp1,"type");
														if (type == NULL)
														{
															
															return -1;
														}
														
		json_unpack(type,"s",&text); //this unpacks the value right into value
	
		//~ puts(text);
		
//~ 
		
//~ 
		value =	json_object_get(temp1,"value");
			
			if (value == NULL) 
		
				{
					return -1;
				}
		
		
		json_unpack(value,"s",&text2); //this unpacks the value right into value
		
		
		
		stringLength = strlen(text2);	
				
		
		n = atoi(key);
														
		if (strcmp(text, "number") == 0)
		{

		
		
															
		
			propertiesArray[n] = atof(text2); //adding data to the proper place in array
			
			if (!(stringLength <= 0))
			{
																			//COMMENT OUT!
			 																//~ propertiesHelper[n].expressionString = (char *) calloc(stringLength,sizeof(char)); //adding data to the proper place in array
		
				strcpy(propertiesHelper[n].expressionString,text2);
		
																			
			}
			else
			{
					//~ propertiesHelper[n].expressionString = NULL;
					propertiesHelper[n].stringIsNull = 1; //diverting nulling a pointer
			}
			
															
		}
		
		else
		{
			
			//else add the string data anyways to the helper structure
			
			if (!(stringLength <= 0))
			{
																			//COMMENT OUT!
			 																//~ propertiesHelper[n].expressionString = (char *) calloc(stringLength,sizeof(char)); //adding data to the proper place in array
			
			
				strcpy(propertiesHelper[n].expressionString,text2);
			
																			
			}
			else
			{
					propertiesHelper[n].stringIsNull = 1; //diverting nulling a pointer
					
			}
		
			
		}
		
		
		
			text = text2 = NULL; //reset the string data to NULL
		
		
		setBracketPointsForExpressionP(propertiesHelper, n, *hostGarbage); //this processes everything
																																																															
																					
																					
																					
		findTargetBetweenBracketsP(propertiesHelper, n); //this puts the brackets in the helper list for actions
																		
																		
															//doing string comparisons here
															//~ printf("Unpack value %d\n",); //deprecated
										
															
															//~ if (strcmp(key0, "type") == 0)
																	//~ {
																		//~ 
																		//~ 
																		//~ 
																	//~ }
															//~ if (strcmp(key0, "name") == 0)
																	//~ {
																		//~ 
																	//~ }
															//~ if (strcmp(key0, "value") == 0)
																	//~ {
																		//~ 
																	//~ }
															//~ 
																	
																	
																	//~ iter0 = json_object_iter_next(temp1, iter0); //this iterates through the json data
														//~ }
													}
												//~ }
											
										iter = json_object_iter_next(jsonPropertiesList, iter); //this iterates through the json data	
										}
									
									//~ propertiesCount += (int) json_object_size(jsonPropertiesList); //increase summation
									
					
									}
			
							
					}
		
		
		
		}
			
			
	return 1; //return the highest number
}


int returnCrealActionListAndConditions(struct pre_actionlist  crealActions[], struct helperDataForActions actionHelper[], struct actionConditionsMetaHelp helpersForActions[], json_t **root, int numOfCrealNodes, struct garbageList **hostGarbage)
{
 //this is used for action lists
	const char *key, *key0;
	key = key0  = NULL; //hehe
	json_t *tempArrayProperty, *temp0, *temp1, *value, *jsonActionList, *temp2; //json properties, actions, etc
	void *iter, *iter0; //used for iteration
	char *text = NULL; //this is used to slurp all of the json data into a string
	const char *text2 = NULL; //this is used to slurp all of the json data into a string
					
					
					int i, k,tempArraySize, textStringLength, n;
					i = k = tempArraySize = textStringLength = n =0;
			for (i = 0; i < numOfCrealNodes; i++)
				{
					
					temp0 = json_array_get(*root, i); //this is used temporary to get the value for the object

					 if(!json_is_object(temp0))
						{
							printf("Array element : %d is not considered a json object!!\n",i);
							quitWithError("json array element was not an object!"); //this happens when json data is all messed up
						}
						else
						{
							
							jsonActionList = json_object_get(temp0, "action list");
							
								 if(!json_is_object(jsonActionList))
								{	
									//not ideal, something weird happens here where I cannot exit out of this fucking thing if something goes sour
									printf("Element : %d contains properties that is not considered a json object!!\n",i);											
									//~ quitWithError("json array element was not an object!"); //this happens when json data is all messed up
								
								}
								else
								
								{
									//add the accumulations of properties for one unified array
									//elements in the creal stuff should be quick sorted
									//~ mainCrealNode[i].numberOfProperties = (uint) json_object_size(jsonPropertiesList); //add the number of properties to the crea node structure
									printf("Number of properties in the %d array element : %d\n",i,json_object_size(jsonActionList));
									
									//~ crealPropertiesSummation += (int) json_object_size(jsonPropertiesList); //increase summation
									
										iter = json_object_iter(jsonActionList); //this is needed, the golden ticket
										
										while(iter)
										{
											key = json_object_iter_key(iter);
											//~ puts("THIS IS WHERE IM AT RIGHT NOW");
											puts(key); //use this to debug the key stuff
											temp1 = json_object_iter_value(iter);
											n = atoi(key); //use this for the index
											
											if(json_is_array(temp1))
												{			
													puts("Element is an array");									
													//~ quitWithError("json array element was not an object!"); //this happens when json data is all messed up
												
												}
												if(json_is_object(temp1))
												{			
													puts("Element is an object");									
													//~ quitWithError("json array element was not an object!"); //this happens when json data is all messed up
													iter0 = json_object_iter(temp1); //this is needed, the golden ticket
														
														while(iter0)
														{
														
														
															key0 = json_object_iter_key(iter0); //this is the key 
															value = json_object_iter_value(iter0);
															puts(key0); //debug
															//the actions transpire below for collecting the data 
															
															
															if (strcmp(key0, "actions") == 0) //actions is true
															{
																
																	puts("This is a action list");
																	
																	if(json_is_array(value))
																		{			
																			puts("The action element is an array!!");									
																			//~ quitWithError("json array element was not an object!"); //this happens when json data is all messed up
																			
																		
																			
																						tempArraySize = json_array_size(value); // geting the size for the array
																	
																		
																		
																			//~ mainCrealNode[i].actionlist = (struct pre_actionlist *) calloc(tempArraySize, sizeof(struct pre_actionlist)); //calloc some values
																			
																			crealActions[n].numberOfActions = tempArraySize; //here is the creal actions
																			helpersForActions[n].countOfActions = tempArraySize; //this is the count of the number of strings 
																			if (tempArraySize <= 0)
																			{
																				crealActions[n].actionListIsNull = 1;
																				
																			}
																			
																			for (k = 0; k < tempArraySize; k++)
																			{
																				temp2 = json_array_get(value, k); //this is used temporary to get the value for the object
																				
																				if(json_is_object(temp2))
																				{
																					
																						//~ "action_type": "1",
																						//~ "target_id": "5",
																						//~ "target_value": "10"
																					
																					
																					tempArrayProperty = json_object_get(temp2, "action_type");
																					puts("action_type");
																					//~ json_unpack(tempArrayProperty,"s",&text2); //this unpacks the value right into value
																					text2 = json_string_value(tempArrayProperty);
																					puts(text2); 
																					//assignment
																					crealActions[n].actionsList[k].actionType = atoi(text2);
																					tempArrayProperty = json_object_get(temp2, "target_id");
																					puts("target_id");
																					//~ json_unpack(tempArrayProperty,"s",&text2); //this unpacks the value right into value
																					text2 = json_string_value(tempArrayProperty);
																					puts(text2);
																					//assignment
																					crealActions[n].actionsList[k].targetID = atoi(text2);
																					
																					tempArrayProperty = json_object_get(temp2, "target_value");
																					puts("target_value");
																					//~ json_unpack(tempArrayProperty,"s",&text2); //this unpacks the value right into value
																					text2 = json_string_value(tempArrayProperty);
																					puts(text2);
																					//assignment
																					crealActions[n].actionsList[k].targetValue = atof(text2);
																					textStringLength = strlen(text2);
																				
																					if (!(textStringLength <= 0))
																					{
																						
																						//~ actionHelper[atoi(key)].expressionString = (char *) calloc(textStringLength,sizeof(char));
																						//~ addElementToGarbageList(actionHelper[atoi(key)].expressionString,*hostGarbage); //add to the garbage list
																						
																						strcpy(helpersForActions[n].actionStrings[k].expressionString, text2); //copy the string to the array
																						//~ strcpy(actionHelper[n].expressionString, text2); //copy the string to the array
																						puts(helpersForActions[n].actionStrings[k].expressionString); //debug
																					}
																					else
																					{
																						//~ actionHelper[atoi(key)].expressionString = NULL;
																						helpersForActions[n].actionStrings[k].stringIsNull = 1;
																						actionHelper[n].stringIsNull = 1;
																						//diverting nulling a pointer
																						
																					}
																					
																					setBracketPointsForExpression(helpersForActions[n].actionStrings, k, *hostGarbage); //this processes everything
																					//~ setBracketPointsForExpression(actionHelper, n, *hostGarbage); //this processes everything
																																																															
																					
																					
																					
																					findTargetBetweenBrackets(helpersForActions[n].actionStrings, k); //this puts the brackets in the helper list for actions
																					//~ findTargetBetweenBrackets(actionHelper, n); //this puts the brackets in the helper list for actions
																				}
																				
																				//~ json_decref(temp2); //free jansson parsing data
																				
																			}
																		}
																
																	//~ //puts(key0); //use this to debug the key stuff	
															}
															
															
															if (strcmp(key0, "conditions") == 0)
															{
																	puts("This is a condition");
																	//~ //puts(key0); //use this to debug the key stuff	
																	if(json_is_array(value))
																		{			
																			puts("The condition element is an array!!");									
																			
																			
																		
																			tempArraySize = json_array_size(value); // geting the size for the array
																			
																			crealActions[n].numberOfConditions = tempArraySize; //get the count of the array size to allow for iterations iterate over it 
																			helpersForActions[n].countOfConditions = tempArraySize; //this is the count of the number of strings
																			if ((tempArraySize <= 0))
																			{
																				
																				
																				crealActions[n].conditionListIsNull = 1; //if there are no elements, then nullify the pointer!
																				
																				
																				//~ crealActions[atoi(key)].conditionlist = (struct pre_conditionlist *) calloc(tempArraySize, sizeof(struct pre_conditionlist)); //calloc some values
																				
																				//~ addElementToGarbageList(crealActions[atoi(key)].conditionlist, *hostGarbage); //add to garbage list
																				
																			
																				
																			}
																			for (k = 0; k < tempArraySize; k++)
																			{
																				temp2 = json_array_get(value, k); //this is used temporary to get the value for the object
																				
																				if(json_is_object(temp2))
																				{
																					
																					//~ "field": "11",
																					//~ "relation": "2",
																					//~ "value": "1"
																					
																					tempArrayProperty = json_object_get(temp2, "field");
																					puts("field");
																					
																					//~ json_unpack(tempArrayProperty,"s",&text2); //this unpacks the value right into value
																					text2 = json_string_value(tempArrayProperty);
																					puts(text2);
																					crealActions[n].conditionlist[k].field = atoi(text2);
																				
																					tempArrayProperty = json_object_get(temp2, "relation");
																					puts("relation");
																					
																					//~ json_unpack(tempArrayProperty,"s",&text2); //this unpacks the value right into value
																					text2 = json_string_value(tempArrayProperty);
																					puts(text2);
																					crealActions[n].conditionlist[k].relationType = atoi(text2);
																					
																					tempArrayProperty = json_object_get(temp2, "value");
																					puts("value");
																					
																					//~ json_unpack(tempArrayProperty,"s",&text2); //this unpacks the value right into value
																					text2 = json_string_value(tempArrayProperty);
																					puts(text2);
																					crealActions[n].conditionlist[k].value = atof(text2); //convert this to a double type!!
																					textStringLength = strlen(text2);
																				
																					if (!(textStringLength <= 0))
																					{
																				
																						strcpy(helpersForActions[n].conditionStrings[k].expressionString, text2);
																						puts(helpersForActions[n].conditionStrings[k].expressionString);
																					}
																					
																					else
																					{
																						
																						helpersForActions[n].conditionStrings[k].stringIsNull = 1;
																						
																					}
																					
																					
																					setBracketPointsForExpression(helpersForActions[n].conditionStrings, k, *hostGarbage); //this processes everything
																					//~ setBracketPointsForExpression(actionHelper, n, *hostGarbage); //this processes everything
																																																															
																					
																					
																					
																					findTargetBetweenBrackets(helpersForActions[n].conditionStrings, k); //this puts the brackets in the helper list for actions
																				
																				
																				}
																				
																				
																				//~ json_decref(temp2); //free jansson parsing data
																			}
																		
																		}
															}
															
															
															
															
															//..iterate throught this stuff right here	
															
															
															iter0 = json_object_iter_next(temp1, iter0); //this iterates through the json data
															
															
														}
												}

											
											iter = json_object_iter_next(jsonActionList, iter); //this iterates through the json data
											//~ json_decref(temp1); //free jansson parsing data
							}
									
									
									
						}
								
									
				}
				//dereference
				
				
		}

		return 1;
}


creal_d evaluateCrealEquation(const char *string, uint indexCpuNum)
{
	
	char *bufferString; //this is used for a temporary location
	char *outputLocation;
	
	uint stringLength; //used to get the string length
	int fd, findTerminatorRange, errorTrap;
	creal_d returnValue; //the file descriptor
	fd = returnValue = findTerminatorRange = 0; //cool
	asprintf(&outputLocation, "/dev/shm/temp_pipe_%u",indexCpuNum);
	
	errorTrap = mkfifo(outputLocation,0777); //set the default mask for the process
					if (errorTrap < 0) 
					{ //something bad fucking happened 
						perror("Something bad happened when trying to make a pipe\n");	
					}
	
	asprintf(&bufferString, "php -r 'print %s;' 2>> %s > %s &",string, ERROR_FILE, outputLocation);
	
	puts(bufferString); //debug
	
	system(bufferString);
	stringLength = strlen(bufferString); //get the string length
	
	memset(bufferString, 0 ,sizeof(char) * stringLength); //clear out the string
	
	fd = open(outputLocation, O_RDONLY);
	
	if (!(fd < 0 ))
	{
			
			findTerminatorRange = read(fd, bufferString, stringLength);
			
			if (!(findTerminatorRange < 0))
			{
					bufferString[findTerminatorRange] += '\0';
					returnValue = atof(bufferString);
			}
		
	}
	
		puts(bufferString); //debug
	
		free(bufferString); //free the buffer string
		
		close(fd);
		
		unlink(outputLocation);
		free(outputLocation); //the path
		return returnValue; //return this value right here
	
	 //openning the location
	
	
	
	//~ %u_thread%u
		//~ php -r 'print 1.56*exp(10,4);' 2> /dev/null > hello &
	
}


uint returnHighestPropertyStringLength(creal_t propertiesArray[], json_t **root, int numOfCrealNodes)
{
		
	const char *key, *key0;
	key = key0  = NULL; //hehe
	json_t *jsonPropertiesList, *temp0, *temp1, *value; //json properties, actions, etc
	void *iter, *iter0; //used for iteration
	char *text = NULL; //this is used to slurp all of the json data into a string
	uint stringLength, highestStringLength;
	int check = 0;
	//~ int count = (int) json_array_size(*root); //the count of the elements, for multithreading
	
	stringLength = highestStringLength = 0; //this is used to return
	int i = 0;
			for (i = 0; i < numOfCrealNodes; i++)
			{
				
				temp0 = json_array_get(*root, i); //this is used temporary to get the value for the object

					 if(!json_is_object(temp0))
						{
							//~ printf("Array element : %d is not considered a json object!!\n",i);
							return -1;
						}
						else
						{
							jsonPropertiesList = json_object_get(temp0, "properties");
								 if(!json_is_object(jsonPropertiesList))
								{	
									//not ideal, something weird happens here where I cannot exit out of this fucking thing if something goes sour
									//~ printf("Element : %d contains properties that is not considered a json object!!\n",i);											
									//~ quitWithError("json array element was not an object!"); //this happens when json data is all messed up
								
								}
								else
								{
									//add the accumulations of properties for one unified array
									//elements in the creal stuff should be quick sorted
									
										iter = json_object_iter(jsonPropertiesList); //this is needed, the golden ticket
										while(iter)
										{
											key = json_object_iter_key(iter);
											temp1 = json_object_iter_value(iter);
												
											if(!json_is_object(temp1))
												{												
												
														return -1; //this happens when json data is all messed up
												
												}
												else
												{
													iter0 = json_object_iter(temp1); //this is needed, the golden ticket
													while(iter0)								
													{
															key0 = json_object_iter_key(iter0); //this is the key 
															value = json_object_iter_value(iter0); //the value of the json key right here
													
														if(!json_is_string(value))
									
														{												
																	return -1; //this happens when json data is all messed up
														
														}
														else
														{			
															//doing string comparisons here
															//~ printf("Unpack value %d\n",); //deprecated
															json_unpack(value,"s",&text); //this unpacks the value right into value
															
															if (strcmp(key0, "type") == 0)
																	{
																		
																	}
															if (strcmp(key0, "name") == 0)
																	{
																		
																	}
															if (strcmp(key0, "value") == 0)
																	{
																		stringLength = strlen(text);
																		//~ propertiesArray[atoi(key)] = atoi(text); //adding data to the proper place in array
																		if (stringLength > highestStringLength)
																		{
																			//This is used to just get the maximum string length
																			highestStringLength = stringLength; 	//ASSIGNMENT
																			
																			
																		}
																		
																		
																		
																	}
															
																	
																	
																	iter0 = json_object_iter_next(temp1, iter0); //this iterates through the json data
														}
													}
												}
											
										iter = json_object_iter_next(jsonPropertiesList, iter); //this iterates through the json data	
										}
									
									//~ propertiesCount += (int) json_object_size(jsonPropertiesList); //increase summation
									
					
									}
			
							
					}
		
		
		
		}
			
			
	return highestStringLength; //return the highest number
}




/*
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
*/

