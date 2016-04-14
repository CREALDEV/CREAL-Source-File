#include <stdio.h> 
#include <stdlib.h> 
#include <errno.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <time.h> 
#include <fcntl.h> 
#include <math.h> 
#include <pthread.h> 
#include <omp.h>
 #define NONRELATION 0 //no action 
 #define EQUAL 1 //used for addition 
 #define GREATERTHAN 2 //used for deletion 
 #define LESSERTHAN 3 //used for changing 
 #define GREATERTHANEQUALTO 4 //used for maintaining 
 #define LESSERTHANEQUALTO 5 //used for transporting 
 #define NOTEQUAL 6 //used for transporting 
  
 #define NONACTION 0 //no action 
 #define INCREASE 1 //used for addition 
 #define DECREASE 2 //used for deletion 
 #define CHANGE 3 //used for changing 
 #define MAINTAIN 4 //used for maintaining 
 #define TRANSPORT 5 //used for transporting 
 #define NOTEQUAL 6 //used for transporting 
  
   #define USAGE "Input a file with a range, and input a time" 
 uint minRange, maxRange, speedAdjustVar; //these are used for taking the maximum and minumum values, also adjusting the speed of the application 
 long double crealTime, timeIncrementer; //these are used for keeping up with time 
 uint numOfRange; 
 long double count; //the counting variable 
 #define MAX_PROPERTIES 55
#define MAX_ACTION_LISTS 55
#define MAX_ACTIONS_AND_CONDITIONS 55
#define MAX_CREAL_NODES 55
typedef double creal_t; 
typedef creal_t (*actionFunctionPointer)( void); 
struct pre_actions 
 { 
 uint aID; 
 char actionType; 
 uint targetID; 
 actionFunctionPointer actionFunction;	
 creal_t targetValue; 
 }; 
struct pre_conditionlist 
 { 
 uint cID; 
 char relationType; 
 uint field; 
 actionFunctionPointer conditionFunction; 
 creal_t value; 
 }; 
 struct pre_actionlist 
 { 
 uint alID; 
 char actionListIsNull; 
 char conditionListIsNull; 
 uint numberOfActionItems; 
 uint numberOfConditions; 
 struct pre_actions actions[10]; 
 struct pre_conditionlist conditions[10];  
 
 }; 
 


   struct crealNodeStruct { 
 	
 		/* May need to modify the datatypes */ 
 		
 		uint iD; //this is the id
 		uint numberOfProperties; //the number of properties
 		uint numberOfActions; //the number of actions 
 		char notNull; //this is to make sure that the data structure is not null
 		
		uint pID[1000];
		creal_t *properties[1000];
		struct pre_actionlist  *actionsList[1000];
};


 struct csvNodeDataStruct{ 
 
 			uint nodeNumber; //the number of the node
 			uint count; //the count of all the properties
 			creal_t *properties; //the properties of the node
 
 };
 
 
 struct csvStruct
 {
 
 	struct csvNodeDataStruct *nodes;
 	uint count; //the count of all the nodes
 	long double currentTimeValue;
 
 };
 struct crealNodeStruct crealNodes[1000];
creal_t crealProperties[1000];
creal_t sumVector[1000];
struct pre_actionlist crealActions[1000];


 void printOutDataInCrealNodes(struct crealNodeStruct nodes[]); //this will be used to print out all of the junk
  int processActionsAndConditions(struct crealNodeStruct nodes[], creal_t properties[], creal_t returnVector[]); //this is the main function to process the creal nodes
  int processProperties(creal_t returnVector[], creal_t properties[]); //process the properties
  void crealInit(void); //this function will be used to initialize all of the data structures
  /* These functions below are to grab file information, could be placed in a wrapper function */
  
  int grabRangesFromFile(const char *string, uint rangePointer[]);
  int returnLineCountOfFile(const char *string);
  //this function will write out 
   
  /* Add these selection function to cerebro */
  int processSelectedActionsAndConditions(struct crealNodeStruct nodes[], creal_t properties[], creal_t returnVector[], uint rangePointer[], uint rangeSize); //this is the main function to process the creal nodes... through a selection!
  void printOutSelectedDataInCrealNodes(struct crealNodeStruct nodes[], uint rangePointer[], uint rangeSize); //this will only utilize selections
 
  uint evaluateConditions(struct crealNodeStruct *node, creal_t properties[], uint actionListIndex); //this is ok
  uint processActions(struct crealNodeStruct *node, creal_t properties[], creal_t returnVector[], uint actionListIndex); //this is ok too
  
  int writeOutDataFileFor(struct crealNodeStruct nodes[], uint rangePointer[], uint rangeIndex, long double *currenTime);
  int transferDataFileDataFileIndex(struct crealNodeStruct *node, uint nodeIndex, long double *currenTime); 
  int processProperties(creal_t returnVector[], creal_t properties[]); //process the properties
  int writeSelectedDataFile(struct crealNodeStruct *node, uint nodeIndex, uint propIndex, long double *currentTime);
  
  /* These are purely functional types of functions for multiprocessing */
  uint findNumOfProperties(struct crealNodeStruct *node); //this is used to find the number of properties
  uint findNumOfActions(uint rangeIndex, struct crealNodeStruct nodes[]); //this is used to find the number of actions
  uint findNumOfActionItems(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[]); //this is used to find the number of action items
  uint findNumOfConditions(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[]); //this is used to find the number of action items
  
  uint returnValueOfProperties(uint rangeIndex, struct crealNodeStruct nodes[], creal_t returnArray[]); //this is used to find the number of properties
  
  uint returnActionsTargetValues(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], creal_t returnArray[]); //returns action target values
  uint returnActionsTargetIDs(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[]); //returns actions target ids
  uint returnActionsActionTypes(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[]); //returns action types
  
  uint returnConditionFields(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[]); //returns condition fields
  uint returnConditionRelationTypes(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[]); //returns condition relations
  uint returnConditionValues(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], creal_t returnArray[]); //returns condition values
  
 creal_t actionFunction_367_0(void);
creal_t actionFunction_546_0(void);
creal_t conditionFunction_546_0(void);
creal_t conditionFunction_546_1(void);
creal_t actionFunction_536_0(void);
creal_t conditionFunction_536_0(void);
creal_t conditionFunction_536_1(void);
creal_t actionFunction_385_0(void);
creal_t conditionFunction_385_0(void);
creal_t conditionFunction_385_1(void);
creal_t actionFunction_523_0(void);
creal_t conditionFunction_523_0(void);
creal_t conditionFunction_523_1(void);
creal_t actionFunction_474_0(void);
creal_t conditionFunction_474_0(void);
creal_t actionFunction_537_0(void);
creal_t conditionFunction_537_0(void);
creal_t conditionFunction_537_1(void);
creal_t actionFunction_538_0(void);
creal_t conditionFunction_538_0(void);
creal_t conditionFunction_538_1(void);
creal_t actionFunction_545_0(void);
creal_t conditionFunction_545_0(void);
creal_t conditionFunction_545_1(void);
creal_t actionFunction_522_0(void);
creal_t conditionFunction_522_0(void);
creal_t actionFunction_547_0(void);
creal_t conditionFunction_547_0(void);
creal_t conditionFunction_547_1(void);
creal_t actionFunction_524_0(void);
creal_t conditionFunction_524_0(void);
creal_t conditionFunction_524_1(void);
creal_t actionFunction_548_0(void);
creal_t conditionFunction_548_0(void);
creal_t conditionFunction_548_1(void);
creal_t actionFunction_525_0(void);
creal_t conditionFunction_525_0(void);
creal_t conditionFunction_525_1(void);
creal_t actionFunction_549_0(void);
creal_t conditionFunction_549_0(void);
creal_t conditionFunction_549_1(void);
creal_t actionFunction_526_0(void);
creal_t conditionFunction_526_0(void);
creal_t conditionFunction_526_1(void);
creal_t actionFunction_550_0(void);
creal_t conditionFunction_550_0(void);
creal_t conditionFunction_550_1(void);
creal_t actionFunction_527_0(void);
creal_t conditionFunction_527_0(void);
creal_t conditionFunction_527_1(void);
creal_t actionFunction_551_0(void);
creal_t conditionFunction_551_0(void);
creal_t conditionFunction_551_1(void);
creal_t actionFunction_528_0(void);
creal_t conditionFunction_528_0(void);
creal_t conditionFunction_528_1(void);
creal_t actionFunction_535_0(void);
creal_t conditionFunction_535_0(void);
creal_t conditionFunction_535_1(void);
creal_t actionFunction_539_0(void);
creal_t conditionFunction_539_0(void);
creal_t conditionFunction_539_1(void);
creal_t actionFunction_544_0(void);
creal_t conditionFunction_544_0(void);
creal_t conditionFunction_544_1(void);
creal_t actionFunction_552_0(void);
creal_t conditionFunction_552_0(void);
creal_t conditionFunction_552_1(void);
creal_t actionFunction_553_0(void);
creal_t conditionFunction_553_0(void);
creal_t conditionFunction_553_1(void);
creal_t actionFunction_370_0(void);
creal_t conditionFunction_370_0(void);
creal_t actionFunction_371_0(void);
creal_t conditionFunction_371_0(void);
creal_t actionFunction_368_0(void);
creal_t conditionFunction_368_0(void);
creal_t actionFunction_372_0(void);
creal_t conditionFunction_372_0(void);
creal_t actionFunction_373_0(void);
creal_t conditionFunction_373_0(void);
creal_t actionFunction_374_0(void);
creal_t conditionFunction_374_0(void);
creal_t actionFunction_407_0(void);
creal_t conditionFunction_407_0(void);
creal_t actionFunction_394_0(void);
creal_t conditionFunction_394_0(void);
creal_t actionFunction_438_0(void);
creal_t conditionFunction_438_0(void);
creal_t actionFunction_401_0(void);
creal_t conditionFunction_401_0(void);
creal_t actionFunction_410_0(void);
creal_t conditionFunction_410_0(void);
creal_t actionFunction_444_0(void);
creal_t conditionFunction_444_0(void);
creal_t actionFunction_387_0(void);
creal_t conditionFunction_387_0(void);
creal_t actionFunction_404_0(void);
creal_t conditionFunction_404_0(void);
creal_t conditionFunction_404_1(void);
creal_t actionFunction_406_0(void);
creal_t conditionFunction_406_0(void);
creal_t actionFunction_393_0(void);
creal_t conditionFunction_393_0(void);
creal_t actionFunction_408_0(void);
creal_t conditionFunction_408_0(void);
creal_t actionFunction_395_0(void);
creal_t conditionFunction_395_0(void);
creal_t actionFunction_409_0(void);
creal_t conditionFunction_409_0(void);
creal_t actionFunction_396_0(void);
creal_t conditionFunction_396_0(void);
creal_t actionFunction_397_0(void);
creal_t conditionFunction_397_0(void);
creal_t actionFunction_398_0(void);
creal_t conditionFunction_398_0(void);
creal_t actionFunction_399_0(void);
creal_t conditionFunction_399_0(void);
creal_t actionFunction_437_0(void);
creal_t conditionFunction_437_0(void);
creal_t actionFunction_400_0(void);
creal_t conditionFunction_400_0(void);
creal_t actionFunction_439_0(void);
creal_t conditionFunction_439_0(void);
creal_t actionFunction_402_0(void);
creal_t conditionFunction_402_0(void);
creal_t actionFunction_403_0(void);
creal_t conditionFunction_403_0(void);
creal_t actionFunction_405_0(void);
creal_t actionFunction_405_1(void);
creal_t conditionFunction_405_0(void);
creal_t conditionFunction_405_1(void);
creal_t actionFunction_411_0(void);
creal_t conditionFunction_411_0(void);
creal_t actionFunction_412_0(void);
creal_t conditionFunction_412_0(void);
creal_t actionFunction_413_0(void);
creal_t conditionFunction_413_0(void);
creal_t actionFunction_414_0(void);
creal_t conditionFunction_414_0(void);
creal_t actionFunction_415_0(void);
creal_t conditionFunction_415_0(void);
creal_t actionFunction_416_0(void);
creal_t conditionFunction_416_0(void);
creal_t actionFunction_417_0(void);
creal_t conditionFunction_417_0(void);
creal_t actionFunction_419_0(void);
creal_t conditionFunction_419_0(void);
creal_t actionFunction_420_0(void);
creal_t conditionFunction_420_0(void);
creal_t actionFunction_421_0(void);
creal_t conditionFunction_421_0(void);
creal_t actionFunction_422_0(void);
creal_t conditionFunction_422_0(void);
creal_t actionFunction_423_0(void);
creal_t conditionFunction_423_0(void);
creal_t actionFunction_424_0(void);
creal_t conditionFunction_424_0(void);
creal_t actionFunction_425_0(void);
creal_t conditionFunction_425_0(void);
creal_t actionFunction_426_0(void);
creal_t conditionFunction_426_0(void);
creal_t actionFunction_427_0(void);
creal_t conditionFunction_427_0(void);
creal_t actionFunction_428_0(void);
creal_t conditionFunction_428_0(void);
creal_t actionFunction_429_0(void);
creal_t conditionFunction_429_0(void);
creal_t actionFunction_430_0(void);
creal_t conditionFunction_430_0(void);
creal_t actionFunction_431_0(void);
creal_t conditionFunction_431_0(void);
creal_t actionFunction_432_0(void);
creal_t conditionFunction_432_0(void);
creal_t actionFunction_433_0(void);
creal_t conditionFunction_433_0(void);
creal_t actionFunction_434_0(void);
creal_t conditionFunction_434_0(void);
creal_t actionFunction_435_0(void);
creal_t conditionFunction_435_0(void);
creal_t actionFunction_436_0(void);
creal_t conditionFunction_436_0(void);
creal_t actionFunction_440_0(void);
creal_t conditionFunction_440_0(void);
creal_t actionFunction_441_0(void);
creal_t conditionFunction_441_0(void);
creal_t actionFunction_442_0(void);
creal_t conditionFunction_442_0(void);
creal_t actionFunction_443_0(void);
creal_t conditionFunction_443_0(void);
creal_t actionFunction_445_0(void);
creal_t conditionFunction_445_0(void);
creal_t actionFunction_495_0(void);
creal_t conditionFunction_495_0(void);
creal_t actionFunction_496_0(void);
creal_t conditionFunction_496_0(void);
creal_t actionFunction_497_0(void);
creal_t conditionFunction_497_0(void);
creal_t actionFunction_498_0(void);
creal_t conditionFunction_498_0(void);
creal_t actionFunction_472_0(void);
creal_t conditionFunction_472_0(void);
creal_t conditionFunction_472_1(void);
creal_t actionFunction_469_0(void);
creal_t conditionFunction_469_0(void);
creal_t conditionFunction_469_1(void);
creal_t actionFunction_464_0(void);
creal_t conditionFunction_464_0(void);
creal_t conditionFunction_464_1(void);
creal_t actionFunction_466_0(void);
creal_t conditionFunction_466_0(void);
creal_t conditionFunction_466_1(void);
creal_t actionFunction_470_0(void);
creal_t conditionFunction_470_0(void);
creal_t conditionFunction_470_1(void);
creal_t actionFunction_467_0(void);
creal_t conditionFunction_467_0(void);
creal_t conditionFunction_467_1(void);
creal_t actionFunction_471_0(void);
creal_t conditionFunction_471_0(void);
creal_t conditionFunction_471_1(void);
creal_t actionFunction_468_0(void);
creal_t conditionFunction_468_0(void);
creal_t conditionFunction_468_1(void);
creal_t actionFunction_473_0(void);
creal_t conditionFunction_473_0(void);
creal_t conditionFunction_473_1(void);
creal_t actionFunction_460_0(void);
creal_t conditionFunction_460_0(void);
creal_t conditionFunction_460_1(void);
creal_t actionFunction_457_0(void);
creal_t conditionFunction_457_0(void);
creal_t actionFunction_458_0(void);
creal_t conditionFunction_458_0(void);
creal_t actionFunction_462_0(void);
creal_t conditionFunction_462_0(void);
creal_t conditionFunction_462_1(void);
creal_t actionFunction_459_0(void);
creal_t conditionFunction_459_0(void);
creal_t actionFunction_463_0(void);
creal_t conditionFunction_463_0(void);
creal_t conditionFunction_463_1(void);
creal_t actionFunction_490_0(void);
creal_t conditionFunction_490_0(void);
creal_t actionFunction_491_0(void);
creal_t conditionFunction_491_0(void);
creal_t conditionFunction_491_1(void);
creal_t conditionFunction_491_2(void);
creal_t conditionFunction_491_3(void);
creal_t conditionFunction_491_4(void);
creal_t actionFunction_492_0(void);
creal_t conditionFunction_492_0(void);
creal_t conditionFunction_492_1(void);
creal_t conditionFunction_492_2(void);
creal_t conditionFunction_492_3(void);
creal_t conditionFunction_492_4(void);
creal_t actionFunction_517_0(void);
creal_t conditionFunction_517_0(void);
creal_t actionFunction_520_0(void);
creal_t conditionFunction_520_0(void);
creal_t conditionFunction_520_1(void);
creal_t actionFunction_518_0(void);
creal_t conditionFunction_518_0(void);
creal_t conditionFunction_518_1(void);
creal_t actionFunction_521_0(void);
creal_t conditionFunction_521_0(void);
creal_t conditionFunction_521_1(void);
creal_t actionFunction_519_0(void);
creal_t conditionFunction_519_0(void);
creal_t conditionFunction_519_1(void);
creal_t actionFunction_502_0(void);
creal_t conditionFunction_502_0(void);
creal_t actionFunction_499_0(void);
creal_t conditionFunction_499_0(void);
creal_t actionFunction_500_0(void);
creal_t conditionFunction_500_0(void);
creal_t actionFunction_501_0(void);
creal_t conditionFunction_501_0(void);
creal_t actionFunction_503_0(void);
creal_t conditionFunction_503_0(void);
creal_t actionFunction_504_0(void);
creal_t conditionFunction_504_0(void);
creal_t conditionFunction_504_1(void);
creal_t actionFunction_505_0(void);
creal_t conditionFunction_505_0(void);
creal_t conditionFunction_505_1(void);
creal_t actionFunction_506_0(void);
creal_t conditionFunction_506_0(void);
creal_t conditionFunction_506_1(void);
creal_t actionFunction_510_0(void);
creal_t conditionFunction_510_0(void);
creal_t conditionFunction_510_1(void);
creal_t actionFunction_507_0(void);
creal_t conditionFunction_507_0(void);
creal_t conditionFunction_507_1(void);
creal_t actionFunction_508_0(void);
creal_t conditionFunction_508_0(void);
creal_t conditionFunction_508_1(void);
creal_t actionFunction_509_0(void);
creal_t conditionFunction_509_0(void);
creal_t conditionFunction_509_1(void);
creal_t actionFunction_531_0(void);
creal_t conditionFunction_531_0(void);
creal_t conditionFunction_531_1(void);
creal_t actionFunction_529_0(void);
creal_t conditionFunction_529_0(void);
creal_t actionFunction_530_0(void);
creal_t conditionFunction_530_0(void);
creal_t conditionFunction_530_1(void);
creal_t actionFunction_532_0(void);
creal_t conditionFunction_532_0(void);
creal_t conditionFunction_532_1(void);
creal_t actionFunction_533_0(void);
creal_t conditionFunction_533_0(void);
creal_t conditionFunction_533_1(void);
creal_t actionFunction_534_0(void);
int main(int argc, char **argv) 
 {
 					if (argc <= 2)		
 					{ 
 						
 							
 								//nothing was entered to start the application correctly
 								fputs(USAGE, stderr); //shows application usage	
 								exit(EXIT_FAILURE); // exit the application
 								
 								
 					}
 
 
 				//The ranges, add this into cerebro
 				uint *rangeArray, range; //for the ranges
 				range = (uint) returnLineCountOfFile(argv[1]); //geting the line count of the file
 				rangeArray = (uint *) alloca(sizeof(uint) * range); //allocating the array for functions
 
 				if (grabRangesFromFile(argv[1], rangeArray) < 0)
 				{
 						
 						
 							exit(EXIT_FAILURE);
 					
 				}
 				
 				
 				crealInit(); //initialize the creal properties
 				
 
 	
 		crealTime = atoi(argv[2]);
 		
 
  		for (count = 0; count < crealTime; count++)
  		{
 				memset(sumVector,0,1000*sizeof(creal_t)); //set the memory to zero
 				
  				srand(time(0)); //allowing the application to generate a random seed
  								
  				processSelectedActionsAndConditions(crealNodes, crealProperties, sumVector,rangeArray, range);
  				
  				processProperties(sumVector,crealProperties);
  				
  				writeOutDataFileFor(crealNodes, rangeArray, range, &count);
  				
  		}
 
 
 
 
 
 		exit(EXIT_SUCCESS);	
}
creal_t actionFunction_367_0(void)
{
 return fmod((crealProperties[898] + 1), 86400);
}
creal_t actionFunction_546_0(void)
{
 return 0.00176;
}
creal_t conditionFunction_546_0(void)
{
 return 43201;
}
creal_t conditionFunction_546_1(void)
{
 return 44280;
}
creal_t actionFunction_536_0(void)
{
 return 0.00607;
}
creal_t conditionFunction_536_0(void)
{
 return 19801;
}
creal_t conditionFunction_536_1(void)
{
 return 21600;
}
creal_t actionFunction_385_0(void)
{
 return 0.0000434400626666666;
}
creal_t conditionFunction_385_0(void)
{
 return 0;
}
creal_t conditionFunction_385_1(void)
{
 return 21600;
}
creal_t actionFunction_523_0(void)
{
 return 0.15111111111;
}
creal_t conditionFunction_523_0(void)
{
 return 22500;
}
creal_t conditionFunction_523_1(void)
{
 return 24300;
}
creal_t actionFunction_474_0(void)
{
 return 0.001354400626666666666;
}
creal_t conditionFunction_474_0(void)
{
 return 21600;
}
creal_t actionFunction_537_0(void)
{
 return 0.00176;
}
creal_t conditionFunction_537_0(void)
{
 return 21601;
}
creal_t conditionFunction_537_1(void)
{
 return 22680;
}
creal_t actionFunction_538_0(void)
{
 return 0.0162;
}
creal_t conditionFunction_538_0(void)
{
 return 22681;
}
creal_t conditionFunction_538_1(void)
{
 return 24480;
}
creal_t actionFunction_545_0(void)
{
 return 0.00607;
}
creal_t conditionFunction_545_0(void)
{
 return 41401;
}
creal_t conditionFunction_545_1(void)
{
 return 43200;
}
creal_t actionFunction_522_0(void)
{
 return 0.0001;
}
creal_t conditionFunction_522_0(void)
{
 return 22500;
}
creal_t actionFunction_547_0(void)
{
 return 0.0162;
}
creal_t conditionFunction_547_0(void)
{
 return 44281;
}
creal_t conditionFunction_547_1(void)
{
 return 46080;
}
creal_t actionFunction_524_0(void)
{
 return 0.01306930692;
}
creal_t conditionFunction_524_0(void)
{
 return 24300;
}
creal_t conditionFunction_524_1(void)
{
 return 44499;
}
creal_t actionFunction_548_0(void)
{
 return 0.0019;
}
creal_t conditionFunction_548_0(void)
{
 return 46081;
}
creal_t conditionFunction_548_1(void)
{
 return 57600;
}
creal_t actionFunction_525_0(void)
{
 return 0.15111111111;
}
creal_t conditionFunction_525_0(void)
{
 return 44500;
}
creal_t conditionFunction_525_1(void)
{
 return 46300;
}
creal_t actionFunction_549_0(void)
{
 return 0.000744;
}
creal_t conditionFunction_549_0(void)
{
 return 61200;
}
creal_t conditionFunction_549_1(void)
{
 return 63000;
}
creal_t actionFunction_526_0(void)
{
 return 0.01361386137;
}
creal_t conditionFunction_526_0(void)
{
 return 46300;
}
creal_t conditionFunction_526_1(void)
{
 return 66000;
}
creal_t actionFunction_550_0(void)
{
 return 0.00607;
}
creal_t conditionFunction_550_0(void)
{
 return 63001;
}
creal_t conditionFunction_550_1(void)
{
 return 64800;
}
creal_t actionFunction_527_0(void)
{
 return 0.15111111111;
}
creal_t conditionFunction_527_0(void)
{
 return 66000;
}
creal_t conditionFunction_527_1(void)
{
 return 68000;
}
creal_t actionFunction_551_0(void)
{
 return 0.00176;
}
creal_t conditionFunction_551_0(void)
{
 return 64801;
}
creal_t conditionFunction_551_1(void)
{
 return 65880;
}
creal_t actionFunction_528_0(void)
{
 return 0.01699009899;
}
creal_t conditionFunction_528_0(void)
{
 return 68000;
}
creal_t conditionFunction_528_1(void)
{
 return 86400;
}
creal_t actionFunction_535_0(void)
{
 return 0.000744;
}
creal_t conditionFunction_535_0(void)
{
 return 18000;
}
creal_t conditionFunction_535_1(void)
{
 return 19800;
}
creal_t actionFunction_539_0(void)
{
 return 0.0019;
}
creal_t conditionFunction_539_0(void)
{
 return 24481;
}
creal_t conditionFunction_539_1(void)
{
 return 36000;
}
creal_t actionFunction_544_0(void)
{
 return 0.000744;
}
creal_t conditionFunction_544_0(void)
{
 return 39600;
}
creal_t conditionFunction_544_1(void)
{
 return 41400;
}
creal_t actionFunction_552_0(void)
{
 return 0.0162;
}
creal_t conditionFunction_552_0(void)
{
 return 65881;
}
creal_t conditionFunction_552_1(void)
{
 return 67680;
}
creal_t actionFunction_553_0(void)
{
 return 0.0019;
}
creal_t conditionFunction_553_0(void)
{
 return 67681;
}
creal_t conditionFunction_553_1(void)
{
 return 79200;
}
creal_t actionFunction_370_0(void)
{
 return 180156;
}
creal_t conditionFunction_370_0(void)
{
 return 21601;
}
creal_t actionFunction_371_0(void)
{
 return 180156;
}
creal_t conditionFunction_371_0(void)
{
 return 43200;
}
creal_t actionFunction_368_0(void)
{
 return 180156;
}
creal_t conditionFunction_368_0(void)
{
 return 21600;
}
creal_t actionFunction_372_0(void)
{
 return 180156;
}
creal_t conditionFunction_372_0(void)
{
 return 43201;
}
creal_t actionFunction_373_0(void)
{
 return 180156;
}
creal_t conditionFunction_373_0(void)
{
 return 64800;
}
creal_t actionFunction_374_0(void)
{
 return 180156;
}
creal_t conditionFunction_374_0(void)
{
 return 64801;
}
creal_t actionFunction_407_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_407_0(void)
{
 return 55.825616;
}
creal_t actionFunction_394_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_394_0(void)
{
 return 3.987544;
}
creal_t actionFunction_438_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_438_0(void)
{
 return 71.775792;
}
creal_t actionFunction_401_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_401_0(void)
{
 return 31.900352;
}
creal_t actionFunction_410_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_410_0(void)
{
 return 67.788248;
}
creal_t actionFunction_444_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_444_0(void)
{
 return 95.701056;
}
creal_t actionFunction_387_0(void)
{
 return 34075;
}
creal_t conditionFunction_387_0(void)
{
 return 0;
}
creal_t actionFunction_404_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_404_0(void)
{
 return 43.862984;
}
creal_t conditionFunction_404_1(void)
{
 return 43.862984;
}
creal_t actionFunction_406_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_406_0(void)
{
 return 51.838072;
}
creal_t actionFunction_393_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_393_0(void)
{
 return 0;
}
creal_t actionFunction_408_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_408_0(void)
{
 return 59.81316;
}
creal_t actionFunction_395_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_395_0(void)
{
 return 7.975088;
}
creal_t actionFunction_409_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_409_0(void)
{
 return 63.800704;
}
creal_t actionFunction_396_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_396_0(void)
{
 return 11.962632;
}
creal_t actionFunction_397_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_397_0(void)
{
 return 15.950176;
}
creal_t actionFunction_398_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_398_0(void)
{
 return 19.93772;
}
creal_t actionFunction_399_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_399_0(void)
{
 return 23.925264;
}
creal_t actionFunction_437_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_437_0(void)
{
 return 67.788248;
}
creal_t actionFunction_400_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_400_0(void)
{
 return 27.912808;
}
creal_t actionFunction_439_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_439_0(void)
{
 return 75.763336;
}
creal_t actionFunction_402_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_402_0(void)
{
 return 35.887896;
}
creal_t actionFunction_403_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_403_0(void)
{
 return 39.87544;
}
creal_t actionFunction_405_0(void)
{
 return 39.87544;
}
creal_t actionFunction_405_1(void)
{
 return 3.987544;
}
creal_t conditionFunction_405_0(void)
{
 return 47.850528;
}
creal_t conditionFunction_405_1(void)
{
 return 47.850528;
}
creal_t actionFunction_411_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_411_0(void)
{
 return 71.775792;
}
creal_t actionFunction_412_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_412_0(void)
{
 return 75.763336;
}
creal_t actionFunction_413_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_413_0(void)
{
 return 79.75088;
}
creal_t actionFunction_414_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_414_0(void)
{
 return 83.738424;
}
creal_t actionFunction_415_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_415_0(void)
{
 return 87.725968;
}
creal_t actionFunction_416_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_416_0(void)
{
 return 91.713512;
}
creal_t actionFunction_417_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_417_0(void)
{
 return 95.701056;
}
creal_t actionFunction_419_0(void)
{
 return 3.987544;
}
creal_t conditionFunction_419_0(void)
{
 return 99.6886;
}
creal_t actionFunction_420_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_420_0(void)
{
 return 0;
}
creal_t actionFunction_421_0(void)
{
 return 0.0664590666666666666666666;
}
creal_t conditionFunction_421_0(void)
{
 return 3.987544;
}
creal_t actionFunction_422_0(void)
{
 return 0.06645906666666666;
}
creal_t conditionFunction_422_0(void)
{
 return 7.975088;
}
creal_t actionFunction_423_0(void)
{
 return 0.06645906666666666;
}
creal_t conditionFunction_423_0(void)
{
 return 11.962632;
}
creal_t actionFunction_424_0(void)
{
 return 0.0664590666666666666;
}
creal_t conditionFunction_424_0(void)
{
 return 15.950176;
}
creal_t actionFunction_425_0(void)
{
 return 0.06645906666666666;
}
creal_t conditionFunction_425_0(void)
{
 return 19.93772;
}
creal_t actionFunction_426_0(void)
{
 return 0.06645906666666;
}
creal_t conditionFunction_426_0(void)
{
 return 23.925264;
}
creal_t actionFunction_427_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_427_0(void)
{
 return 27.912808;
}
creal_t actionFunction_428_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_428_0(void)
{
 return 31.900352;
}
creal_t actionFunction_429_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_429_0(void)
{
 return 35.887896;
}
creal_t actionFunction_430_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_430_0(void)
{
 return 39.87544;
}
creal_t actionFunction_431_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_431_0(void)
{
 return 43.862984;
}
creal_t actionFunction_432_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_432_0(void)
{
 return 47.850528;
}
creal_t actionFunction_433_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_433_0(void)
{
 return 51.838072;
}
creal_t actionFunction_434_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_434_0(void)
{
 return 55.825616;
}
creal_t actionFunction_435_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_435_0(void)
{
 return 59.81316;
}
creal_t actionFunction_436_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_436_0(void)
{
 return 63.800704;
}
creal_t actionFunction_440_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_440_0(void)
{
 return 79.75088;
}
creal_t actionFunction_441_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_441_0(void)
{
 return 83.738424;
}
creal_t actionFunction_442_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_442_0(void)
{
 return 87.725968;
}
creal_t actionFunction_443_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_443_0(void)
{
 return 91.713512;
}
creal_t actionFunction_445_0(void)
{
 return 0.066459066666666666;
}
creal_t conditionFunction_445_0(void)
{
 return 99.6886;
}
creal_t actionFunction_495_0(void)
{
 return 0.01;
}
creal_t conditionFunction_495_0(void)
{
 return 1000;
}
creal_t actionFunction_496_0(void)
{
 return 0.001;
}
creal_t conditionFunction_496_0(void)
{
 return 1000;
}
creal_t actionFunction_497_0(void)
{
 return 0.01;
}
creal_t conditionFunction_497_0(void)
{
 return 1000;
}
creal_t actionFunction_498_0(void)
{
 return 0.001;
}
creal_t conditionFunction_498_0(void)
{
 return 1000;
}
creal_t actionFunction_472_0(void)
{
 return 0.01666666666666666666;
}
creal_t conditionFunction_472_0(void)
{
 return 43375;
}
creal_t conditionFunction_472_1(void)
{
 return 45175;
}
creal_t actionFunction_469_0(void)
{
 return 8.754;
}
creal_t conditionFunction_469_0(void)
{
 return 43205;
}
creal_t conditionFunction_469_1(void)
{
 return 63785;
}
creal_t actionFunction_464_0(void)
{
 return 8.754;
}
creal_t conditionFunction_464_0(void)
{
 return 21604;
}
creal_t conditionFunction_464_1(void)
{
 return 42184;
}
creal_t actionFunction_466_0(void)
{
 return 8.754;
}
creal_t conditionFunction_466_0(void)
{
 return 43204;
}
creal_t conditionFunction_466_1(void)
{
 return 63784;
}
creal_t actionFunction_470_0(void)
{
 return 8.754;
}
creal_t conditionFunction_470_0(void)
{
 return 64805;
}
creal_t conditionFunction_470_1(void)
{
 return 85385;
}
creal_t actionFunction_467_0(void)
{
 return 8.754;
}
creal_t conditionFunction_467_0(void)
{
 return 64804;
}
creal_t conditionFunction_467_1(void)
{
 return 85384;
}
creal_t actionFunction_471_0(void)
{
 return 0.01666666666666666;
}
creal_t conditionFunction_471_0(void)
{
 return 21775;
}
creal_t conditionFunction_471_1(void)
{
 return 23575;
}
creal_t actionFunction_468_0(void)
{
 return 8.754;
}
creal_t conditionFunction_468_0(void)
{
 return 21605;
}
creal_t conditionFunction_468_1(void)
{
 return 42185;
}
creal_t actionFunction_473_0(void)
{
 return 0.0166666666666666666666;
}
creal_t conditionFunction_473_0(void)
{
 return 64975;
}
creal_t conditionFunction_473_1(void)
{
 return 66775;
}
creal_t actionFunction_460_0(void)
{
 return 8.754;
}
creal_t conditionFunction_460_0(void)
{
 return 21603;
}
creal_t conditionFunction_460_1(void)
{
 return 42183;
}
creal_t actionFunction_457_0(void)
{
 return 181248;
}
creal_t conditionFunction_457_0(void)
{
 return 21602;
}
creal_t actionFunction_458_0(void)
{
 return 181248;
}
creal_t conditionFunction_458_0(void)
{
 return 43202;
}
creal_t actionFunction_462_0(void)
{
 return 8.754;
}
creal_t conditionFunction_462_0(void)
{
 return 43203;
}
creal_t conditionFunction_462_1(void)
{
 return 63783;
}
creal_t actionFunction_459_0(void)
{
 return 181248;
}
creal_t conditionFunction_459_0(void)
{
 return 64802;
}
creal_t actionFunction_463_0(void)
{
 return 8.754;
}
creal_t conditionFunction_463_0(void)
{
 return 64803;
}
creal_t conditionFunction_463_1(void)
{
 return 85383;
}
creal_t actionFunction_490_0(void)
{
 return 1;
}
creal_t conditionFunction_490_0(void)
{
 return 490;
}
creal_t actionFunction_491_0(void)
{
 return 1;
}
creal_t conditionFunction_491_0(void)
{
 return 491;
}
creal_t conditionFunction_491_1(void)
{
 return 491;
}
creal_t conditionFunction_491_2(void)
{
 return 491;
}
creal_t conditionFunction_491_3(void)
{
 return 491;
}
creal_t conditionFunction_491_4(void)
{
 return 491;
}
creal_t actionFunction_492_0(void)
{
 return 1;
}
creal_t conditionFunction_492_0(void)
{
 return 492;
}
creal_t conditionFunction_492_1(void)
{
 return 492;
}
creal_t conditionFunction_492_2(void)
{
 return 492;
}
creal_t conditionFunction_492_3(void)
{
 return 492;
}
creal_t conditionFunction_492_4(void)
{
 return 492;
}
creal_t actionFunction_517_0(void)
{
 return 0;
}
creal_t conditionFunction_517_0(void)
{
 return 517;
}
creal_t actionFunction_520_0(void)
{
 return 0.000022961;
}
creal_t conditionFunction_520_0(void)
{
 return 520;
}
creal_t conditionFunction_520_1(void)
{
 return 520;
}
creal_t actionFunction_518_0(void)
{
 return 0.006918;
}
creal_t conditionFunction_518_0(void)
{
 return 518;
}
creal_t conditionFunction_518_1(void)
{
 return 518;
}
creal_t actionFunction_521_0(void)
{
 return 0.00095;
}
creal_t conditionFunction_521_0(void)
{
 return 521;
}
creal_t conditionFunction_521_1(void)
{
 return 521;
}
creal_t actionFunction_519_0(void)
{
 return 0.000049;
}
creal_t conditionFunction_519_0(void)
{
 return 519;
}
creal_t conditionFunction_519_1(void)
{
 return 519;
}
creal_t actionFunction_502_0(void)
{
 return 0.0015;
}
creal_t conditionFunction_502_0(void)
{
 return 502;
}
creal_t actionFunction_499_0(void)
{
 return 0.015;
}
creal_t conditionFunction_499_0(void)
{
 return 499;
}
creal_t actionFunction_500_0(void)
{
 return 0.0015;
}
creal_t conditionFunction_500_0(void)
{
 return 500;
}
creal_t actionFunction_501_0(void)
{
 return 0.015;
}
creal_t conditionFunction_501_0(void)
{
 return 501;
}
creal_t actionFunction_503_0(void)
{
 return 0.001667;
}
creal_t conditionFunction_503_0(void)
{
 return 503;
}
creal_t actionFunction_504_0(void)
{
 return 0.016666;
}
creal_t conditionFunction_504_0(void)
{
 return 504;
}
creal_t conditionFunction_504_1(void)
{
 return 504;
}
creal_t actionFunction_505_0(void)
{
 return 0.008;
}
creal_t conditionFunction_505_0(void)
{
 return 505;
}
creal_t conditionFunction_505_1(void)
{
 return 505;
}
creal_t actionFunction_506_0(void)
{
 return 0.017;
}
creal_t conditionFunction_506_0(void)
{
 return 506;
}
creal_t conditionFunction_506_1(void)
{
 return 506;
}
creal_t actionFunction_510_0(void)
{
 return 0.007;
}
creal_t conditionFunction_510_0(void)
{
 return 510;
}
creal_t conditionFunction_510_1(void)
{
 return 510;
}
creal_t actionFunction_507_0(void)
{
 return 0.0075;
}
creal_t conditionFunction_507_0(void)
{
 return 507;
}
creal_t conditionFunction_507_1(void)
{
 return 507;
}
creal_t actionFunction_508_0(void)
{
 return 0.0167;
}
creal_t conditionFunction_508_0(void)
{
 return 508;
}
creal_t conditionFunction_508_1(void)
{
 return 508;
}
creal_t actionFunction_509_0(void)
{
 return 0.0000000000000000000000001;
}
creal_t conditionFunction_509_0(void)
{
 return 509;
}
creal_t conditionFunction_509_1(void)
{
 return 509;
}
creal_t actionFunction_531_0(void)
{
 return 0.000049;
}
creal_t conditionFunction_531_0(void)
{
 return 531;
}
creal_t conditionFunction_531_1(void)
{
 return 531;
}
creal_t actionFunction_529_0(void)
{
 return 0;
}
creal_t conditionFunction_529_0(void)
{
 return 529;
}
creal_t actionFunction_530_0(void)
{
 return 0.006918;
}
creal_t conditionFunction_530_0(void)
{
 return 530;
}
creal_t conditionFunction_530_1(void)
{
 return 530;
}
creal_t actionFunction_532_0(void)
{
 return 0.000022961;
}
creal_t conditionFunction_532_0(void)
{
 return 532;
}
creal_t conditionFunction_532_1(void)
{
 return 532;
}
creal_t actionFunction_533_0(void)
{
 return 0.00090;
}
creal_t conditionFunction_533_0(void)
{
 return 533;
}
creal_t conditionFunction_533_1(void)
{
 return 533;
}
creal_t actionFunction_534_0(void)
{
 return 1;
}
void printOutDataInCrealNodes(struct crealNodeStruct nodes[])
{
	//This function is just used to print the properties
	//~ *(crealNodes[1].properties[0])
	uint i, k, j; //make vars 
	i = k = j = 0; //set to zero
	
	printf("Printing out values of the data members!!\n\n\n");
	
	for (i = 1; i < 1000; i++)
	{
		for (k = 0; k < nodes[i].numberOfProperties; k++)
		{
			printf("The property Value of node %d, property %d is : %f\n",i,k,*(nodes[i].properties[k]));
		}
	
		for (k = 0; k < nodes[i].numberOfActions; k++)
		{
			//~ nodes[1]->actionsList[0].numberOfActionItems // add this in soon
			for (j = 0; j < nodes[i].actionsList[k]->numberOfActionItems; j++)
			{
				
				//~ these are the things witihin the actions
				printf("The action type in node %d, action list elements %d, and action %d is : %d\n",i,k,j,nodes[i].actionsList[k]->actions[j].actionType);
				printf("The target id in node %d, action list elements %d, and action %d is : %d\n",i,k,j,nodes[i].actionsList[k]->actions[j].targetID);
				printf("The target value in node %d, action list elements %d, and action %d is : %f\n",i,k,j,nodes[i].actionsList[k]->actions[j].targetValue);
				
			}
			
			
			for (j = 0; j < nodes[i].actionsList[k]->numberOfConditions; j++)
			{
				
				//~ these are the things witihin the actions
				printf("The field value in node %d, action list elements %d, and condition %d is : %d\n",i,k,j,nodes[i].actionsList[k]->conditions[j].field);
				printf("The relation type in node %d, action list elements %d, and condition %d is : %d\n",i,k,j,nodes[i].actionsList[k]->conditions[j].relationType);
				printf("The value in node %d, action list elements %d, and condition %d is : %f\n",i,k,j,nodes[i].actionsList[k]->conditions[j].value);
				
			}
		}
	}
	
	//~ .field = 11 ;
//~ crealActions[1].conditions[0].relationType = 2 ;
//~ crealActions[1].conditions[0].value = 1.000000 ;
	//Pointers to arrays inside of the struct have to be dereferenced at the base of the struct member.
	//Pointers to arrays of structs inside of a struct have to use the pointer symbol
	//cool, dont return anything	
	
	//nodes[i]).actionsList[k]->numberOfActionItems => this is how you access the members within the access list
}

void printOutSelectedDataInCrealNodes(struct crealNodeStruct nodes[], uint rangePointer[], uint rangeSize)
{
	//This function is just used to print the properties
	//~ *(crealNodes[1].properties[0])
	uint i, k, j; //make vars 
	i = k = j = 0; //set to zero
	
	printf("Printing out values of the data members!!\n\n\n");
	
	for (i = 0; i < rangeSize; i++)
	{
		for (k = 0; k < nodes[rangePointer[i]].numberOfProperties; k++)
		{
			printf("The property Value of node %d, property %d is : %f\n",rangePointer[i],k,*(nodes[rangePointer[i]].properties[k]));
		}
	
		for (k = 0; k < nodes[rangePointer[i]].numberOfActions; k++)
		{
			//~ nodes[1]->actionsList[0].numberOfActionItems // add this in soon
			for (j = 0; j < nodes[rangePointer[i]].actionsList[k]->numberOfActionItems; j++)
			{
				
				//~ these are the things witihin the actions
				printf("The action type in node %d, action list elements %d, and action %d is : %d\n",rangePointer[i],k,j,nodes[rangePointer[i]].actionsList[k]->actions[j].actionType);
				printf("The target id in node %d, action list elements %d, and action %d is : %d\n",rangePointer[i],k,j,nodes[rangePointer[i]].actionsList[k]->actions[j].targetID);
				printf("The target value in node %d, action list elements %d, and action %d is : %f\n",rangePointer[i],k,j,nodes[rangePointer[i]].actionsList[k]->actions[j].actionFunction());
				
			}
			
			
			for (j = 0; j < nodes[rangePointer[i]].actionsList[k]->numberOfConditions; j++)
			{
				
				//~ these are the things witihin the actions
				printf("The field value in node %d, action list elements %d, and condition %d is : %d\n",rangePointer[i],k,j,nodes[rangePointer[i]].actionsList[k]->conditions[j].field);
				printf("The relation type in node %d, action list elements %d, and condition %d is : %d\n",rangePointer[i],k,j,nodes[rangePointer[i]].actionsList[k]->conditions[j].relationType);
				printf("The value in node %d, action list elements %d, and condition %d is : %f\n",rangePointer[i],k,j,nodes[rangePointer[i]].actionsList[k]->conditions[j].conditionFunction());
				
			}
		}
	}
	

}


int processSelectedActionsAndConditions(struct crealNodeStruct nodes[], creal_t properties[], creal_t returnVector[], uint rangePointer[], uint rangeSize)
{	
	//this is the main function to process the creal nodes... through a selection!
	
		
	uint i, k, *actionTruFalseArray; //make vars 
	i = k = 0; //set to zero
	
	//~ memset(trueFalseArray, 0, sizeof(uint) * rangeSize);

	for (i = 0; i < rangeSize; i++)
	{
		
		
		actionTruFalseArray = (uint *) alloca(sizeof(uint) * nodes[rangePointer[i]].numberOfActions);
		
		memset(actionTruFalseArray, 0, sizeof(uint) * nodes[rangePointer[i]].numberOfActions);
		
		
		//~ #pragma omp parallel for //openMP parallel for loop
		for (k = 0; k < nodes[rangePointer[i]].numberOfActions; k++)
		{
	
			
			actionTruFalseArray[k] = evaluateConditions(&nodes[rangePointer[i]], properties, k);
			
		
		}//end of inner for iiteration
		
		//~ #pragma omp parallel for //openMP parallel for loop
		for (k = 0; k < nodes[rangePointer[i]].numberOfActions; k++)
		{
				if(actionTruFalseArray[k])
				{
					
					processActions(&nodes[rangePointer[i]], properties, returnVector, k);
					
				}
		
		}//end of inner for iiteration
		
		
	}//end of outer for iteration

						//end the function right here
	return 0; // everything was good	
}



uint evaluateConditions(struct crealNodeStruct *node, creal_t properties[], uint actionListIndex)
{
	/* This function will be used to return */ 
	
	uint i, k, j, conditionCounter; //make vars 
	i = k = j = conditionCounter = 0; //set to zero
	
	if (!(node->actionsList[actionListIndex]->numberOfConditions))
	{
		
		return 1; //this means there are no conditions set, so run the action anyways
		
		
	}
			for (j = 0; j < node->actionsList[actionListIndex]->numberOfConditions; j++)
			{
				//This iteration goes through the conditions
				
				switch (node->actionsList[actionListIndex]->conditions[j].relationType)
				{
					
					
					/* This is the main switch statement for determining the actions and conditions */ 
					
					
					case NONRELATION:
					{
								//~ nodes[i].actionsList[k]->conditions[j].field = A
								//~ nodes[i].actionsList[k]->conditions[j].value = B
						break;
					}
					
					case EQUAL:
					{
						
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] ==
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[node->actionsList[actionListIndex]->conditions[j].field] ==
						node->actionsList[actionListIndex]->conditions[j].conditionFunction())
						{
									
									conditionCounter++; //increase the condition counter
							
						}
						
						break;
					}
					
					case GREATERTHAN:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] >
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[node->actionsList[actionListIndex]->conditions[j].field] >
						node->actionsList[actionListIndex]->conditions[j].conditionFunction())
						{
							
							conditionCounter++; //increase the condition counter
							
						}
						break;
					}
					
					case LESSERTHAN:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] <
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[node->actionsList[actionListIndex]->conditions[j].field] <
						node->actionsList[actionListIndex]->conditions[j].conditionFunction())
						{
							conditionCounter++; //increase the condition counter
							
						}
						break;
					}
					
					case GREATERTHANEQUALTO:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] >=
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[node->actionsList[actionListIndex]->conditions[j].field] >=
						node->actionsList[actionListIndex]->conditions[j].conditionFunction())
						{
							conditionCounter++; //increase the condition counter
							
						}
						
						break;
					}
					
					case LESSERTHANEQUALTO:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] <=
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[node->actionsList[actionListIndex]->conditions[j].field] <=
						node->actionsList[actionListIndex]->conditions[j].conditionFunction())
						{
							conditionCounter++; //increase the condition counter
							
						}
						break;
					}
					
					case NOTEQUAL:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] !=
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[node->actionsList[actionListIndex]->conditions[j].field] !=
						node->actionsList[actionListIndex]->conditions[j].conditionFunction())
						{
							
							conditionCounter++; //increase the condition counter
							
						}
						
						break;
					}
					
					default:
					{
						//nothing happens here
						//play titily-winks Blah!
						break;
					}
					
				}//end of the switch statement
				
			}//end of the condition iteration

			if (conditionCounter == node->actionsList[actionListIndex]->numberOfConditions)
			{

				return 1; //everything is ok here
			}
			else
			{
				
				return 0; //everything is all bad here
			}
}

uint processActions(struct crealNodeStruct *node, creal_t properties[], creal_t returnVector[], uint actionListIndex)
{
	if (!(node->actionsList[actionListIndex]->numberOfActionItems))
	{
		return 0; //there are no action items to process, return 0
		
	}
	
	/* This function will process the actions */ 
	uint j; //make vars 
	j = 0; //set to zero
	
	
	creal_t tempDoubleVar0; //these are temporary variables for the actions
	tempDoubleVar0 = 0; //zeroing out everything
	

					//beginning 
					for (j = 0; j < node->actionsList[actionListIndex]->numberOfActionItems; j++)
					{
						
						/* This is where the action types are looked up */
						
						switch (node->actionsList[actionListIndex]->actions[j].actionType)
						{
							case INCREASE:
							{
								//increase
								
								//~ returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].targetValue;
								returnVector[node->actionsList[actionListIndex]->actions[j].targetID] += node->actionsList[actionListIndex]->actions[j].actionFunction();
								
									
									
								break;
								
							}
							
							case DECREASE:
							{
								//decrease
								
								//~ tempDoubleVar0 = (nodes[i].actionsList[k]->actions[j].targetValue * -1); //invert this value
								tempDoubleVar0 = (node->actionsList[actionListIndex]->actions[j].actionFunction() * -1); //invert this value
								returnVector[node->actionsList[actionListIndex]->actions[j].targetID] += tempDoubleVar0;
							
								break;
								
							}
							
							case CHANGE:
							{
								//change
								
								//~ returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].targetValue;
								//This has to be changed right here
								//~ returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].actionFunction();
								properties[node->actionsList[actionListIndex]->actions[j].targetID] = node->actionsList[actionListIndex]->actions[j].actionFunction();
								break;
							}
							
							case MAINTAIN:
							{
								//maintain
								
								//nothing implemented yet
							
								break;
								
							}
							
							case TRANSPORT:
							{
								//transport
								
								//nothing implemented yet
							
								break;
								
							}
							
							default: 
							{
								
								//nothing is suposed to happen here...
								break;
							}
							

							
							
						}//end of actions switch statement

						//~ printf("The action type in node %d, action list elements %d, and action %d is : %d\n",i,k,j,nodes[i].actionsList[k]->actions[j].actionType);
						//~ printf("The target id in node %d, action list elements %d, and action %d is : %d\n",i,k,j,nodes[i].actionsList[k]->actions[j].targetID);
						//~ printf("The target value in node %d, action list elements %d, and action %d is : %f\n",i,k,j,nodes[i].actionsList[k]->actions[j].targetValue);
						
					}//end of action item for iteration

	return 1;
	
}


int processActionsAndConditions(struct crealNodeStruct nodes[], creal_t properties[], creal_t returnVector[])
{
	//Take these constants out of here because they serve no purpose
//~ char NONRELATION = 0x00; //nothing a type of NULL action


/* =================================================== */

	uint i, k, j, conditionCounter; //make vars 
	i = k = j = conditionCounter = 0; //set to zero
	
	creal_t tempDoubleVar0, tempDoubleVar1, tempDoubleVar2, tempBuffer, tempBuffer0, tempBuffer1; //these are temporary variables for the actions
	tempBuffer = tempBuffer0 = tempBuffer1 = tempDoubleVar0 = tempDoubleVar1 = tempDoubleVar2 = 0; //zeroing out everything
	
	for (i = 1; i < 1000; i++)
	{
	
		//~ for (k = 0; k < nodes[i].numberOfProperties; k++)
		//~ {
	
		//~ }
		
		conditionCounter = 0; //reset the condition counter
		
		for (k = 0; k < nodes[i].numberOfActions; k++)
		{
	
		
			for (j = 0; j < nodes[i].actionsList[k]->numberOfConditions; j++)
			{
				//This iteration goes through the conditions
				
				switch (nodes[i].actionsList[k]->conditions[j].relationType)
				{
					
					
					/* This is the main switch statement for determining the actions and conditions */ 
					
					
					case NONRELATION:
					{
								//~ nodes[i].actionsList[k]->conditions[j].field = A
								//~ nodes[i].actionsList[k]->conditions[j].value = B
						break;
					}
					
					case EQUAL:
					{
						
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] ==
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[nodes[i].actionsList[k]->conditions[j].field] ==
						nodes[i].actionsList[k]->conditions[j].conditionFunction())
						{
									
									conditionCounter++; //increase the condition counter
							
						}
						
						break;
					}
					
					case GREATERTHAN:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] >
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[nodes[i].actionsList[k]->conditions[j].field] >
						nodes[i].actionsList[k]->conditions[j].conditionFunction())
						{
							
							conditionCounter++; //increase the condition counter
							
						}
						break;
					}
					
					case LESSERTHAN:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] <
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[nodes[i].actionsList[k]->conditions[j].field] <
						nodes[i].actionsList[k]->conditions[j].conditionFunction())
						{
							conditionCounter++; //increase the condition counter
							
						}
						break;
					}
					
					case GREATERTHANEQUALTO:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] >=
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[nodes[i].actionsList[k]->conditions[j].field] >=
						nodes[i].actionsList[k]->conditions[j].conditionFunction())
						{
							conditionCounter++; //increase the condition counter
							
						}
						
						break;
					}
					
					case LESSERTHANEQUALTO:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] <=
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[nodes[i].actionsList[k]->conditions[j].field] <=
						nodes[i].actionsList[k]->conditions[j].conditionFunction())
						{
							conditionCounter++; //increase the condition counter
							
						}
						break;
					}
					
					case NOTEQUAL:
					{
						//~ if (properties[nodes[i].actionsList[k]->conditions[j].field] !=
						//~ nodes[i].actionsList[k]->conditions[j].value)
						if (properties[nodes[i].actionsList[k]->conditions[j].field] !=
						nodes[i].actionsList[k]->conditions[j].conditionFunction())
						{
							
							conditionCounter++; //increase the condition counter
							
						}
						
						break;
					}
					
					default:
					{
						//nothing happens here
						//play titily-winks Blah!
						break;
					}
					
				}//end of the switch statement
				
			}//end of the condition iteration
			
			
			//~ if (conditionCounter == nodes[i].actionsList[k]->numberOfConditions) //if the its non-zero
			//~ {
						/* Right here is where we process the actual actions taking place */
						
					for (j = 0; j < nodes[i].actionsList[k]->numberOfActionItems; j++)
					{
						
						/* This is where the action types are looked up */
						
						switch (nodes[i].actionsList[k]->actions[j].actionType)
						{
							case INCREASE:
							{
								//increase
								
								//~ returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].targetValue;
								returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].actionFunction();
								
									
									
								break;
								
							}
							
							case DECREASE:
							{
								//decrease
								
								//~ tempDoubleVar0 = (nodes[i].actionsList[k]->actions[j].targetValue * -1); //invert this value
								tempDoubleVar0 = (nodes[i].actionsList[k]->actions[j].actionFunction() * -1); //invert this value
								returnVector[nodes[i].actionsList[k]->actions[j].targetID] += tempDoubleVar0;
							
								break;
								
							}
							
							case CHANGE:
							{
								//change
								
								//~ returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].targetValue;
								//This has to be changed right here
								//~ returnVector[nodes[i].actionsList[k]->actions[j].targetID] += nodes[i].actionsList[k]->actions[j].actionFunction();
								properties[nodes[i].actionsList[k]->actions[j].targetID] = nodes[i].actionsList[k]->actions[j].actionFunction();
								break;
							}
							
							case MAINTAIN:
							{
								//maintain
								
								//nothing implemented yet
							
								break;
								
							}
							
							case TRANSPORT:
							{
								//transport
								
								//nothing implemented yet
							
								break;
								
							}
							
							default: 
							{
								
								//nothing is suposed to happen here...
								break;
							}
							

							
							
						}//end of actions switch statement

						//~ printf("The action type in node %d, action list elements %d, and action %d is : %d\n",i,k,j,nodes[i].actionsList[k]->actions[j].actionType);
						//~ printf("The target id in node %d, action list elements %d, and action %d is : %d\n",i,k,j,nodes[i].actionsList[k]->actions[j].targetID);
						//~ printf("The target value in node %d, action list elements %d, and action %d is : %f\n",i,k,j,nodes[i].actionsList[k]->actions[j].targetValue);
						
					}//end of action item for iteration

				
				/* right here is where we apply the actions to the nice vector container */ 
				
			//~ }//end of the true condition counter
			
		}//end of inner for iiteration
	}//end of outer for iteration

	//end the function right here
	return 0; // everything was good	
} //end of the function


int processProperties(creal_t returnVector[], creal_t properties[])
{
	
		
		int i;
		i = 0;
		
			#pragma omp parallel for //openMP parallel for loop
			for (i = 0; i < 1000; i++)
			{
					properties[i] += returnVector[i];
						
					
			}
			return 0; //blah!!!
}


int grabRangesFromFile(const char *string, uint rangePointer[])
{
		FILE *fp = NULL; //the main file pointer

	//good...
	fp = fopen(string, "r");
	if (fp == NULL)
	{
		return -1; //bad
		
	}
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	size_t count = 0;
       
			
			count = 0;
           
          while ((read = getline(&line, &len, fp)) != -1) {
               
               
               if (!(read <= 1))
               {
				
				    rangePointer[count] = atoi(line);
					count++;
				   
			   }
               
               
           }

          
           
			free(line);
			fclose(fp);
			return count; //everything was good
}


int returnLineCountOfFile(const char *string)
{
	
		FILE *fp = NULL; //the main file pointer

	//good...
	fp = fopen(string, "r");
	if (fp == NULL)
	{
		return -1; //bad
		
	}
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	size_t count = 0;
       
			
			count = 0;
           
          while ((read = getline(&line, &len, fp)) != -1) {
               
               
               if (!(read <= 1))
               {
				
				    //~ rangePointer[count] = atoi(line);
					count++;
				   
			   }
               
               
           }

          
           
			free(line);
			fclose(fp);
			return count; //everything was good
			
	   }

	   
int writeOutDataFileFor(struct crealNodeStruct nodes[], uint rangePointer[], uint rangeIndex, long double *currentTime)
{
	
	/* In this function we append to a file handle and we take care of thing in terms of
	 * writing out the stuff for the graph information */ 
		
	int i = 0;
	//~ #pragma omp parallel for //openMP parallel for loop
	for(i = 0; i < rangeIndex; i++)
	{
		
			transferDataFileDataFileIndex(&nodes[rangePointer[i]], rangePointer[i] , currentTime);
		
		
		
	}
		
	return 1; //everything went good	
}


int transferDataFileDataFileIndex(struct crealNodeStruct *node, uint nodeIndex, long double *currentTime)
{
	int k = 0;
	
	uint numProp = findNumOfProperties(node); //find the number of properties
	
	//~ #pragma omp parallel for //openMP parallel for loop
	for(k = 0; k < numProp; k++)
	{
		
			writeSelectedDataFile(node, nodeIndex, k, currentTime);
	
		
	}
	
	
	
	return 1;
}


int writeSelectedDataFile(struct crealNodeStruct *node, uint nodeIndex, uint propIndex, long double *currentTime)
{
	
	/* In this function we append to a file handle and we take care of thing in terms of
	 * writing out the stuff for the graph information */ 
	
	FILE *fp = NULL; //the main file pointer
	
	char path[1024], tempString[1024]; // Good.... maybe the size should be increased eventually
	
	memset(path , 0 , sizeof(char) * 1024); // this is just setting the memory to zero
	
	sprintf(path,"%d_%d.dat\0", nodeIndex, propIndex);
	
	fp = fopen(path, "a"); //MAKE SURE TO OPEN THIS THING UP FOR APPENDING
	//~ 
	if (fp == NULL)
	{
		
		return -1; //bad
		
		
	}
	
	flockfile(fp); //lock the file handle.. like a semaphore
	
	fprintf(fp,"%d %f\n",(uint) *currentTime, *node->properties[propIndex] ); //use fprintf to write directly to the file so we can write everything out to a file
	
 
	
	funlockfile(fp);
	fclose(fp); //close the file pointer
				//~ 
	return 1; //everything went good	
}	   
	   
	   //oh oh oh ohhh...

/* A lot of these utilities are used for a functional approach to multiprocessing */

uint findNumOfProperties(struct crealNodeStruct *node)
{
		//this function returns the number of properties
		return node->numberOfProperties;
	
}



uint findNumOfActions(uint rangeIndex, struct crealNodeStruct nodes[])
{
		//this function returns the number of actions
		return nodes[rangeIndex].numberOfActions;
	
}


uint returnValueOfProperties(uint rangeIndex, struct crealNodeStruct nodes[], creal_t returnArray[])
{
	//this function returns values to the properties
	if (nodes[rangeIndex].numberOfProperties <= 0) {return 0;}
	
	int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].numberOfProperties; i++)
	{
		
			returnArray[i] = *(nodes[rangeIndex].properties[i]);
		
	}
	
		return nodes[rangeIndex].numberOfProperties;
	
}

uint findNumOfActionItems(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[])
{
	
	//this function returns the number of action items
	return nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems;
	
	
}


uint returnActionsTargetValues(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], creal_t returnArray[])
{
	// this function returns the target values of selected actions
	if (nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems <= 0) { return 0;} //there is nothing here to process
	
	
		int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems; i++)
	{
		
		//~ returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->actions[i].targetValue;
		returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->actions[i].actionFunction();
		
	}
	
	return nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems;
	
}


uint returnActionsTargetIDs(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[])
{
	// this function returns the target ids
	if (nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems <= 0) { return 0;} //there is nothing here to process
	
	
		int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems; i++)
	{
		
		returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->actions[i].targetID;
		
	}
	
	return nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems;
	
}

uint returnActionsActionTypes(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[])
{
	// this function returns action types
	if (nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems <= 0) { return 0;} //there is nothing here to process
	
	
		int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems; i++)
	{
		
		returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->actions[i].actionType;
		
	}
	
	return nodes[rangeIndex].actionsList[listIndex]->numberOfActionItems;
	
}

uint findNumOfConditions(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[])
{
	
	//this function returns the number of conditions

	return nodes[rangeIndex].actionsList[listIndex]->numberOfConditions;
	
	
	
}


uint returnConditionFields(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[])
{
	// this function returns condition fields
	if (nodes[rangeIndex].actionsList[listIndex]->numberOfConditions <= 0) { return 0;} //there is nothing here to process
	
	
		int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].actionsList[listIndex]->numberOfConditions; i++)
	{
		
		returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->conditions[i].field;
		
	}
	
	return nodes[rangeIndex].actionsList[listIndex]->numberOfConditions;
	
}


uint returnConditionRelationTypes(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], uint returnArray[])
{
	// this function returns relationship types
	if (nodes[rangeIndex].actionsList[listIndex]->numberOfConditions <= 0) { return 0;} //there is nothing here to process
	
	
		int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].actionsList[listIndex]->numberOfConditions; i++)
	{
		
		returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->conditions[i].relationType;
		
	}
	
	return nodes[rangeIndex].actionsList[listIndex]->numberOfConditions;
	
}


uint returnConditionValues(uint rangeIndex,uint listIndex, struct crealNodeStruct nodes[], creal_t returnArray[])
{
	// this function returns relationship types
	if (nodes[rangeIndex].actionsList[listIndex]->numberOfConditions <= 0) { return 0;} //there is nothing here to process
	
	
		int i = 0;
	
	#pragma omp parallel for //openMP parallel for loop
	for (i = 0; i < nodes[rangeIndex].actionsList[listIndex]->numberOfConditions; i++)
	{
		
		//~ returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->conditions[i].value;
		returnArray[i] = nodes[rangeIndex].actionsList[listIndex]->conditions[i].conditionFunction();
		
	}
	
	return nodes[rangeIndex].actionsList[listIndex]->numberOfConditions;
	
}

void crealInit(void)
{crealNodes[679].numberOfProperties = 1;
crealNodes[679].properties[0] = &crealProperties[898];
crealProperties[898] = 0.000000;
crealNodes[679].numberOfActions = 1;
crealNodes[679].actionsList[0] = &crealActions[367];
crealActions[367].alID = 367;
crealActions[367].numberOfActionItems = 1;
crealActions[367].actions[0].actionType = 3;
crealActions[367].actions[0].targetID = 898;
crealActions[367].actions[0].targetValue = 0.000000;
crealActions[367].actions[0].actionFunction = &actionFunction_367_0;
crealActions[367].numberOfConditions = 0;
crealNodes[681].numberOfProperties = 3;
crealNodes[681].properties[0] = &crealProperties[903];
crealProperties[903] = 50.000000;
crealNodes[681].properties[1] = &crealProperties[904];
crealProperties[904] = 100.000000;
crealNodes[681].properties[2] = &crealProperties[905];
crealProperties[905] = 78.500000;
crealNodes[681].numberOfActions = 24;
crealNodes[681].actionsList[0] = &crealActions[546];
crealActions[546].alID = 546;
crealActions[546].numberOfActionItems = 1;
crealActions[546].actions[0].actionType = 2;
crealActions[546].actions[0].targetID = 904;
crealActions[546].actions[0].targetValue = 0.001760;
crealActions[546].actions[0].actionFunction = &actionFunction_546_0;
crealActions[546].numberOfConditions = 2;
crealActions[546].conditions[0].field = 898 ;
crealActions[546].conditions[0].relationType = 4 ;
crealActions[546].conditions[0].value = 43201.000000 ;
crealActions[546].conditions[0].conditionFunction = &conditionFunction_546_0;
crealActions[546].conditions[1].field = 898 ;
crealActions[546].conditions[1].relationType = 5 ;
crealActions[546].conditions[1].value = 44280.000000 ;
crealActions[546].conditions[1].conditionFunction = &conditionFunction_546_1;
crealNodes[681].actionsList[1] = &crealActions[536];
crealActions[536].alID = 536;
crealActions[536].numberOfActionItems = 1;
crealActions[536].actions[0].actionType = 1;
crealActions[536].actions[0].targetID = 904;
crealActions[536].actions[0].targetValue = 0.006070;
crealActions[536].actions[0].actionFunction = &actionFunction_536_0;
crealActions[536].numberOfConditions = 2;
crealActions[536].conditions[0].field = 898 ;
crealActions[536].conditions[0].relationType = 4 ;
crealActions[536].conditions[0].value = 19801.000000 ;
crealActions[536].conditions[0].conditionFunction = &conditionFunction_536_0;
crealActions[536].conditions[1].field = 898 ;
crealActions[536].conditions[1].relationType = 5 ;
crealActions[536].conditions[1].value = 21600.000000 ;
crealActions[536].conditions[1].conditionFunction = &conditionFunction_536_1;
crealNodes[681].actionsList[2] = &crealActions[385];
crealActions[385].alID = 385;
crealActions[385].numberOfActionItems = 1;
crealActions[385].actions[0].actionType = 2;
crealActions[385].actions[0].targetID = 905;
crealActions[385].actions[0].targetValue = 0.000043;
crealActions[385].actions[0].actionFunction = &actionFunction_385_0;
crealActions[385].numberOfConditions = 2;
crealActions[385].conditions[0].field = 898 ;
crealActions[385].conditions[0].relationType = 2 ;
crealActions[385].conditions[0].value = 0.000000 ;
crealActions[385].conditions[0].conditionFunction = &conditionFunction_385_0;
crealActions[385].conditions[1].field = 898 ;
crealActions[385].conditions[1].relationType = 3 ;
crealActions[385].conditions[1].value = 21600.000000 ;
crealActions[385].conditions[1].conditionFunction = &conditionFunction_385_1;
crealNodes[681].actionsList[3] = &crealActions[523];
crealActions[523].alID = 523;
crealActions[523].numberOfActionItems = 1;
crealActions[523].actions[0].actionType = 1;
crealActions[523].actions[0].targetID = 903;
crealActions[523].actions[0].targetValue = 0.151111;
crealActions[523].actions[0].actionFunction = &actionFunction_523_0;
crealActions[523].numberOfConditions = 2;
crealActions[523].conditions[0].field = 898 ;
crealActions[523].conditions[0].relationType = 2 ;
crealActions[523].conditions[0].value = 22500.000000 ;
crealActions[523].conditions[0].conditionFunction = &conditionFunction_523_0;
crealActions[523].conditions[1].field = 898 ;
crealActions[523].conditions[1].relationType = 3 ;
crealActions[523].conditions[1].value = 24300.000000 ;
crealActions[523].conditions[1].conditionFunction = &conditionFunction_523_1;
crealNodes[681].actionsList[4] = &crealActions[474];
crealActions[474].alID = 474;
crealActions[474].numberOfActionItems = 1;
crealActions[474].actions[0].actionType = 2;
crealActions[474].actions[0].targetID = 905;
crealActions[474].actions[0].targetValue = 0.001354;
crealActions[474].actions[0].actionFunction = &actionFunction_474_0;
crealActions[474].numberOfConditions = 1;
crealActions[474].conditions[0].field = 898 ;
crealActions[474].conditions[0].relationType = 4 ;
crealActions[474].conditions[0].value = 21600.000000 ;
crealActions[474].conditions[0].conditionFunction = &conditionFunction_474_0;
crealNodes[681].actionsList[5] = &crealActions[537];
crealActions[537].alID = 537;
crealActions[537].numberOfActionItems = 1;
crealActions[537].actions[0].actionType = 2;
crealActions[537].actions[0].targetID = 904;
crealActions[537].actions[0].targetValue = 0.001760;
crealActions[537].actions[0].actionFunction = &actionFunction_537_0;
crealActions[537].numberOfConditions = 2;
crealActions[537].conditions[0].field = 898 ;
crealActions[537].conditions[0].relationType = 4 ;
crealActions[537].conditions[0].value = 21601.000000 ;
crealActions[537].conditions[0].conditionFunction = &conditionFunction_537_0;
crealActions[537].conditions[1].field = 898 ;
crealActions[537].conditions[1].relationType = 5 ;
crealActions[537].conditions[1].value = 22680.000000 ;
crealActions[537].conditions[1].conditionFunction = &conditionFunction_537_1;
crealNodes[681].actionsList[6] = &crealActions[538];
crealActions[538].alID = 538;
crealActions[538].numberOfActionItems = 1;
crealActions[538].actions[0].actionType = 2;
crealActions[538].actions[0].targetID = 904;
crealActions[538].actions[0].targetValue = 0.016200;
crealActions[538].actions[0].actionFunction = &actionFunction_538_0;
crealActions[538].numberOfConditions = 2;
crealActions[538].conditions[0].field = 898 ;
crealActions[538].conditions[0].relationType = 4 ;
crealActions[538].conditions[0].value = 22681.000000 ;
crealActions[538].conditions[0].conditionFunction = &conditionFunction_538_0;
crealActions[538].conditions[1].field = 898 ;
crealActions[538].conditions[1].relationType = 5 ;
crealActions[538].conditions[1].value = 24480.000000 ;
crealActions[538].conditions[1].conditionFunction = &conditionFunction_538_1;
crealNodes[681].actionsList[7] = &crealActions[545];
crealActions[545].alID = 545;
crealActions[545].numberOfActionItems = 1;
crealActions[545].actions[0].actionType = 1;
crealActions[545].actions[0].targetID = 904;
crealActions[545].actions[0].targetValue = 0.006070;
crealActions[545].actions[0].actionFunction = &actionFunction_545_0;
crealActions[545].numberOfConditions = 2;
crealActions[545].conditions[0].field = 898 ;
crealActions[545].conditions[0].relationType = 4 ;
crealActions[545].conditions[0].value = 41401.000000 ;
crealActions[545].conditions[0].conditionFunction = &conditionFunction_545_0;
crealActions[545].conditions[1].field = 898 ;
crealActions[545].conditions[1].relationType = 5 ;
crealActions[545].conditions[1].value = 43200.000000 ;
crealActions[545].conditions[1].conditionFunction = &conditionFunction_545_1;
crealNodes[681].actionsList[8] = &crealActions[522];
crealActions[522].alID = 522;
crealActions[522].numberOfActionItems = 1;
crealActions[522].actions[0].actionType = 2;
crealActions[522].actions[0].targetID = 903;
crealActions[522].actions[0].targetValue = 0.000100;
crealActions[522].actions[0].actionFunction = &actionFunction_522_0;
crealActions[522].numberOfConditions = 1;
crealActions[522].conditions[0].field = 898 ;
crealActions[522].conditions[0].relationType = 5 ;
crealActions[522].conditions[0].value = 22500.000000 ;
crealActions[522].conditions[0].conditionFunction = &conditionFunction_522_0;
crealNodes[681].actionsList[9] = &crealActions[547];
crealActions[547].alID = 547;
crealActions[547].numberOfActionItems = 1;
crealActions[547].actions[0].actionType = 2;
crealActions[547].actions[0].targetID = 904;
crealActions[547].actions[0].targetValue = 0.016200;
crealActions[547].actions[0].actionFunction = &actionFunction_547_0;
crealActions[547].numberOfConditions = 2;
crealActions[547].conditions[0].field = 898 ;
crealActions[547].conditions[0].relationType = 4 ;
crealActions[547].conditions[0].value = 44281.000000 ;
crealActions[547].conditions[0].conditionFunction = &conditionFunction_547_0;
crealActions[547].conditions[1].field = 898 ;
crealActions[547].conditions[1].relationType = 5 ;
crealActions[547].conditions[1].value = 46080.000000 ;
crealActions[547].conditions[1].conditionFunction = &conditionFunction_547_1;
crealNodes[681].actionsList[10] = &crealActions[524];
crealActions[524].alID = 524;
crealActions[524].numberOfActionItems = 1;
crealActions[524].actions[0].actionType = 2;
crealActions[524].actions[0].targetID = 903;
crealActions[524].actions[0].targetValue = 0.013069;
crealActions[524].actions[0].actionFunction = &actionFunction_524_0;
crealActions[524].numberOfConditions = 2;
crealActions[524].conditions[0].field = 898 ;
crealActions[524].conditions[0].relationType = 4 ;
crealActions[524].conditions[0].value = 24300.000000 ;
crealActions[524].conditions[0].conditionFunction = &conditionFunction_524_0;
crealActions[524].conditions[1].field = 898 ;
crealActions[524].conditions[1].relationType = 5 ;
crealActions[524].conditions[1].value = 44499.000000 ;
crealActions[524].conditions[1].conditionFunction = &conditionFunction_524_1;
crealNodes[681].actionsList[11] = &crealActions[548];
crealActions[548].alID = 548;
crealActions[548].numberOfActionItems = 1;
crealActions[548].actions[0].actionType = 1;
crealActions[548].actions[0].targetID = 904;
crealActions[548].actions[0].targetValue = 0.001900;
crealActions[548].actions[0].actionFunction = &actionFunction_548_0;
crealActions[548].numberOfConditions = 2;
crealActions[548].conditions[0].field = 898 ;
crealActions[548].conditions[0].relationType = 4 ;
crealActions[548].conditions[0].value = 46081.000000 ;
crealActions[548].conditions[0].conditionFunction = &conditionFunction_548_0;
crealActions[548].conditions[1].field = 898 ;
crealActions[548].conditions[1].relationType = 5 ;
crealActions[548].conditions[1].value = 57600.000000 ;
crealActions[548].conditions[1].conditionFunction = &conditionFunction_548_1;
crealNodes[681].actionsList[12] = &crealActions[525];
crealActions[525].alID = 525;
crealActions[525].numberOfActionItems = 1;
crealActions[525].actions[0].actionType = 1;
crealActions[525].actions[0].targetID = 903;
crealActions[525].actions[0].targetValue = 0.151111;
crealActions[525].actions[0].actionFunction = &actionFunction_525_0;
crealActions[525].numberOfConditions = 2;
crealActions[525].conditions[0].field = 898 ;
crealActions[525].conditions[0].relationType = 2 ;
crealActions[525].conditions[0].value = 44500.000000 ;
crealActions[525].conditions[0].conditionFunction = &conditionFunction_525_0;
crealActions[525].conditions[1].field = 898 ;
crealActions[525].conditions[1].relationType = 3 ;
crealActions[525].conditions[1].value = 46300.000000 ;
crealActions[525].conditions[1].conditionFunction = &conditionFunction_525_1;
crealNodes[681].actionsList[13] = &crealActions[549];
crealActions[549].alID = 549;
crealActions[549].numberOfActionItems = 1;
crealActions[549].actions[0].actionType = 2;
crealActions[549].actions[0].targetID = 904;
crealActions[549].actions[0].targetValue = 0.000744;
crealActions[549].actions[0].actionFunction = &actionFunction_549_0;
crealActions[549].numberOfConditions = 2;
crealActions[549].conditions[0].field = 898 ;
crealActions[549].conditions[0].relationType = 4 ;
crealActions[549].conditions[0].value = 61200.000000 ;
crealActions[549].conditions[0].conditionFunction = &conditionFunction_549_0;
crealActions[549].conditions[1].field = 898 ;
crealActions[549].conditions[1].relationType = 5 ;
crealActions[549].conditions[1].value = 63000.000000 ;
crealActions[549].conditions[1].conditionFunction = &conditionFunction_549_1;
crealNodes[681].actionsList[14] = &crealActions[526];
crealActions[526].alID = 526;
crealActions[526].numberOfActionItems = 1;
crealActions[526].actions[0].actionType = 2;
crealActions[526].actions[0].targetID = 903;
crealActions[526].actions[0].targetValue = 0.013614;
crealActions[526].actions[0].actionFunction = &actionFunction_526_0;
crealActions[526].numberOfConditions = 2;
crealActions[526].conditions[0].field = 898 ;
crealActions[526].conditions[0].relationType = 2 ;
crealActions[526].conditions[0].value = 46300.000000 ;
crealActions[526].conditions[0].conditionFunction = &conditionFunction_526_0;
crealActions[526].conditions[1].field = 898 ;
crealActions[526].conditions[1].relationType = 3 ;
crealActions[526].conditions[1].value = 66000.000000 ;
crealActions[526].conditions[1].conditionFunction = &conditionFunction_526_1;
crealNodes[681].actionsList[15] = &crealActions[550];
crealActions[550].alID = 550;
crealActions[550].numberOfActionItems = 1;
crealActions[550].actions[0].actionType = 1;
crealActions[550].actions[0].targetID = 904;
crealActions[550].actions[0].targetValue = 0.006070;
crealActions[550].actions[0].actionFunction = &actionFunction_550_0;
crealActions[550].numberOfConditions = 2;
crealActions[550].conditions[0].field = 898 ;
crealActions[550].conditions[0].relationType = 4 ;
crealActions[550].conditions[0].value = 63001.000000 ;
crealActions[550].conditions[0].conditionFunction = &conditionFunction_550_0;
crealActions[550].conditions[1].field = 898 ;
crealActions[550].conditions[1].relationType = 5 ;
crealActions[550].conditions[1].value = 64800.000000 ;
crealActions[550].conditions[1].conditionFunction = &conditionFunction_550_1;
crealNodes[681].actionsList[16] = &crealActions[527];
crealActions[527].alID = 527;
crealActions[527].numberOfActionItems = 1;
crealActions[527].actions[0].actionType = 1;
crealActions[527].actions[0].targetID = 903;
crealActions[527].actions[0].targetValue = 0.151111;
crealActions[527].actions[0].actionFunction = &actionFunction_527_0;
crealActions[527].numberOfConditions = 2;
crealActions[527].conditions[0].field = 898 ;
crealActions[527].conditions[0].relationType = 2 ;
crealActions[527].conditions[0].value = 66000.000000 ;
crealActions[527].conditions[0].conditionFunction = &conditionFunction_527_0;
crealActions[527].conditions[1].field = 898 ;
crealActions[527].conditions[1].relationType = 3 ;
crealActions[527].conditions[1].value = 68000.000000 ;
crealActions[527].conditions[1].conditionFunction = &conditionFunction_527_1;
crealNodes[681].actionsList[17] = &crealActions[551];
crealActions[551].alID = 551;
crealActions[551].numberOfActionItems = 1;
crealActions[551].actions[0].actionType = 2;
crealActions[551].actions[0].targetID = 904;
crealActions[551].actions[0].targetValue = 0.001760;
crealActions[551].actions[0].actionFunction = &actionFunction_551_0;
crealActions[551].numberOfConditions = 2;
crealActions[551].conditions[0].field = 898 ;
crealActions[551].conditions[0].relationType = 4 ;
crealActions[551].conditions[0].value = 64801.000000 ;
crealActions[551].conditions[0].conditionFunction = &conditionFunction_551_0;
crealActions[551].conditions[1].field = 898 ;
crealActions[551].conditions[1].relationType = 5 ;
crealActions[551].conditions[1].value = 65880.000000 ;
crealActions[551].conditions[1].conditionFunction = &conditionFunction_551_1;
crealNodes[681].actionsList[18] = &crealActions[528];
crealActions[528].alID = 528;
crealActions[528].numberOfActionItems = 1;
crealActions[528].actions[0].actionType = 2;
crealActions[528].actions[0].targetID = 903;
crealActions[528].actions[0].targetValue = 0.016990;
crealActions[528].actions[0].actionFunction = &actionFunction_528_0;
crealActions[528].numberOfConditions = 2;
crealActions[528].conditions[0].field = 898 ;
crealActions[528].conditions[0].relationType = 2 ;
crealActions[528].conditions[0].value = 68000.000000 ;
crealActions[528].conditions[0].conditionFunction = &conditionFunction_528_0;
crealActions[528].conditions[1].field = 898 ;
crealActions[528].conditions[1].relationType = 3 ;
crealActions[528].conditions[1].value = 86400.000000 ;
crealActions[528].conditions[1].conditionFunction = &conditionFunction_528_1;
crealNodes[681].actionsList[19] = &crealActions[535];
crealActions[535].alID = 535;
crealActions[535].numberOfActionItems = 1;
crealActions[535].actions[0].actionType = 2;
crealActions[535].actions[0].targetID = 904;
crealActions[535].actions[0].targetValue = 0.000744;
crealActions[535].actions[0].actionFunction = &actionFunction_535_0;
crealActions[535].numberOfConditions = 2;
crealActions[535].conditions[0].field = 898 ;
crealActions[535].conditions[0].relationType = 4 ;
crealActions[535].conditions[0].value = 18000.000000 ;
crealActions[535].conditions[0].conditionFunction = &conditionFunction_535_0;
crealActions[535].conditions[1].field = 898 ;
crealActions[535].conditions[1].relationType = 5 ;
crealActions[535].conditions[1].value = 19800.000000 ;
crealActions[535].conditions[1].conditionFunction = &conditionFunction_535_1;
crealNodes[681].actionsList[20] = &crealActions[539];
crealActions[539].alID = 539;
crealActions[539].numberOfActionItems = 1;
crealActions[539].actions[0].actionType = 1;
crealActions[539].actions[0].targetID = 904;
crealActions[539].actions[0].targetValue = 0.001900;
crealActions[539].actions[0].actionFunction = &actionFunction_539_0;
crealActions[539].numberOfConditions = 2;
crealActions[539].conditions[0].field = 898 ;
crealActions[539].conditions[0].relationType = 4 ;
crealActions[539].conditions[0].value = 24481.000000 ;
crealActions[539].conditions[0].conditionFunction = &conditionFunction_539_0;
crealActions[539].conditions[1].field = 898 ;
crealActions[539].conditions[1].relationType = 5 ;
crealActions[539].conditions[1].value = 36000.000000 ;
crealActions[539].conditions[1].conditionFunction = &conditionFunction_539_1;
crealNodes[681].actionsList[21] = &crealActions[544];
crealActions[544].alID = 544;
crealActions[544].numberOfActionItems = 1;
crealActions[544].actions[0].actionType = 2;
crealActions[544].actions[0].targetID = 904;
crealActions[544].actions[0].targetValue = 0.000744;
crealActions[544].actions[0].actionFunction = &actionFunction_544_0;
crealActions[544].numberOfConditions = 2;
crealActions[544].conditions[0].field = 898 ;
crealActions[544].conditions[0].relationType = 4 ;
crealActions[544].conditions[0].value = 39600.000000 ;
crealActions[544].conditions[0].conditionFunction = &conditionFunction_544_0;
crealActions[544].conditions[1].field = 898 ;
crealActions[544].conditions[1].relationType = 5 ;
crealActions[544].conditions[1].value = 41400.000000 ;
crealActions[544].conditions[1].conditionFunction = &conditionFunction_544_1;
crealNodes[681].actionsList[22] = &crealActions[552];
crealActions[552].alID = 552;
crealActions[552].numberOfActionItems = 1;
crealActions[552].actions[0].actionType = 2;
crealActions[552].actions[0].targetID = 904;
crealActions[552].actions[0].targetValue = 0.016200;
crealActions[552].actions[0].actionFunction = &actionFunction_552_0;
crealActions[552].numberOfConditions = 2;
crealActions[552].conditions[0].field = 898 ;
crealActions[552].conditions[0].relationType = 4 ;
crealActions[552].conditions[0].value = 65881.000000 ;
crealActions[552].conditions[0].conditionFunction = &conditionFunction_552_0;
crealActions[552].conditions[1].field = 898 ;
crealActions[552].conditions[1].relationType = 5 ;
crealActions[552].conditions[1].value = 67680.000000 ;
crealActions[552].conditions[1].conditionFunction = &conditionFunction_552_1;
crealNodes[681].actionsList[23] = &crealActions[553];
crealActions[553].alID = 553;
crealActions[553].numberOfActionItems = 1;
crealActions[553].actions[0].actionType = 1;
crealActions[553].actions[0].targetID = 904;
crealActions[553].actions[0].targetValue = 0.001900;
crealActions[553].actions[0].actionFunction = &actionFunction_553_0;
crealActions[553].numberOfConditions = 2;
crealActions[553].conditions[0].field = 898 ;
crealActions[553].conditions[0].relationType = 4 ;
crealActions[553].conditions[0].value = 67681.000000 ;
crealActions[553].conditions[0].conditionFunction = &conditionFunction_553_0;
crealActions[553].conditions[1].field = 898 ;
crealActions[553].conditions[1].relationType = 5 ;
crealActions[553].conditions[1].value = 79200.000000 ;
crealActions[553].conditions[1].conditionFunction = &conditionFunction_553_1;
crealNodes[682].numberOfProperties = 1;
crealNodes[682].properties[0] = &crealProperties[900];
crealProperties[900] = 0.000000;
crealNodes[682].numberOfActions = 6;
crealNodes[682].actionsList[0] = &crealActions[370];
crealActions[370].alID = 370;
crealActions[370].numberOfActionItems = 1;
crealActions[370].actions[0].actionType = 2;
crealActions[370].actions[0].targetID = 900;
crealActions[370].actions[0].targetValue = 180156.000000;
crealActions[370].actions[0].actionFunction = &actionFunction_370_0;
crealActions[370].numberOfConditions = 1;
crealActions[370].conditions[0].field = 898 ;
crealActions[370].conditions[0].relationType = 1 ;
crealActions[370].conditions[0].value = 21601.000000 ;
crealActions[370].conditions[0].conditionFunction = &conditionFunction_370_0;
crealNodes[682].actionsList[1] = &crealActions[371];
crealActions[371].alID = 371;
crealActions[371].numberOfActionItems = 1;
crealActions[371].actions[0].actionType = 1;
crealActions[371].actions[0].targetID = 900;
crealActions[371].actions[0].targetValue = 180156.000000;
crealActions[371].actions[0].actionFunction = &actionFunction_371_0;
crealActions[371].numberOfConditions = 1;
crealActions[371].conditions[0].field = 898 ;
crealActions[371].conditions[0].relationType = 1 ;
crealActions[371].conditions[0].value = 43200.000000 ;
crealActions[371].conditions[0].conditionFunction = &conditionFunction_371_0;
crealNodes[682].actionsList[2] = &crealActions[368];
crealActions[368].alID = 368;
crealActions[368].numberOfActionItems = 1;
crealActions[368].actions[0].actionType = 1;
crealActions[368].actions[0].targetID = 900;
crealActions[368].actions[0].targetValue = 180156.000000;
crealActions[368].actions[0].actionFunction = &actionFunction_368_0;
crealActions[368].numberOfConditions = 1;
crealActions[368].conditions[0].field = 898 ;
crealActions[368].conditions[0].relationType = 1 ;
crealActions[368].conditions[0].value = 21600.000000 ;
crealActions[368].conditions[0].conditionFunction = &conditionFunction_368_0;
crealNodes[682].actionsList[3] = &crealActions[372];
crealActions[372].alID = 372;
crealActions[372].numberOfActionItems = 1;
crealActions[372].actions[0].actionType = 2;
crealActions[372].actions[0].targetID = 900;
crealActions[372].actions[0].targetValue = 180156.000000;
crealActions[372].actions[0].actionFunction = &actionFunction_372_0;
crealActions[372].numberOfConditions = 1;
crealActions[372].conditions[0].field = 898 ;
crealActions[372].conditions[0].relationType = 1 ;
crealActions[372].conditions[0].value = 43201.000000 ;
crealActions[372].conditions[0].conditionFunction = &conditionFunction_372_0;
crealNodes[682].actionsList[4] = &crealActions[373];
crealActions[373].alID = 373;
crealActions[373].numberOfActionItems = 1;
crealActions[373].actions[0].actionType = 1;
crealActions[373].actions[0].targetID = 900;
crealActions[373].actions[0].targetValue = 180156.000000;
crealActions[373].actions[0].actionFunction = &actionFunction_373_0;
crealActions[373].numberOfConditions = 1;
crealActions[373].conditions[0].field = 898 ;
crealActions[373].conditions[0].relationType = 1 ;
crealActions[373].conditions[0].value = 64800.000000 ;
crealActions[373].conditions[0].conditionFunction = &conditionFunction_373_0;
crealNodes[682].actionsList[5] = &crealActions[374];
crealActions[374].alID = 374;
crealActions[374].numberOfActionItems = 1;
crealActions[374].actions[0].actionType = 2;
crealActions[374].actions[0].targetID = 900;
crealActions[374].actions[0].targetValue = 180156.000000;
crealActions[374].actions[0].actionFunction = &actionFunction_374_0;
crealActions[374].numberOfConditions = 1;
crealActions[374].conditions[0].field = 898 ;
crealActions[374].conditions[0].relationType = 1 ;
crealActions[374].conditions[0].value = 64801.000000 ;
crealActions[374].conditions[0].conditionFunction = &conditionFunction_374_0;
crealNodes[683].numberOfProperties = 1;
crealNodes[683].properties[0] = &crealProperties[899];
crealProperties[899] = 0.000000;
crealNodes[683].numberOfActions = 53;
crealNodes[683].actionsList[0] = &crealActions[407];
crealActions[407].alID = 407;
crealActions[407].numberOfActionItems = 1;
crealActions[407].actions[0].actionType = 2;
crealActions[407].actions[0].targetID = 899;
crealActions[407].actions[0].targetValue = 3.987544;
crealActions[407].actions[0].actionFunction = &actionFunction_407_0;
crealActions[407].numberOfConditions = 1;
crealActions[407].conditions[0].field = 899 ;
crealActions[407].conditions[0].relationType = 2 ;
crealActions[407].conditions[0].value = 55.825616 ;
crealActions[407].conditions[0].conditionFunction = &conditionFunction_407_0;
crealNodes[683].actionsList[1] = &crealActions[394];
crealActions[394].alID = 394;
crealActions[394].numberOfActionItems = 1;
crealActions[394].actions[0].actionType = 2;
crealActions[394].actions[0].targetID = 899;
crealActions[394].actions[0].targetValue = 3.987544;
crealActions[394].actions[0].actionFunction = &actionFunction_394_0;
crealActions[394].numberOfConditions = 1;
crealActions[394].conditions[0].field = 899 ;
crealActions[394].conditions[0].relationType = 2 ;
crealActions[394].conditions[0].value = 3.987544 ;
crealActions[394].conditions[0].conditionFunction = &conditionFunction_394_0;
crealNodes[683].actionsList[2] = &crealActions[438];
crealActions[438].alID = 438;
crealActions[438].numberOfActionItems = 1;
crealActions[438].actions[0].actionType = 1;
crealActions[438].actions[0].targetID = 905;
crealActions[438].actions[0].targetValue = 0.066459;
crealActions[438].actions[0].actionFunction = &actionFunction_438_0;
crealActions[438].numberOfConditions = 1;
crealActions[438].conditions[0].field = 899 ;
crealActions[438].conditions[0].relationType = 2 ;
crealActions[438].conditions[0].value = 71.775792 ;
crealActions[438].conditions[0].conditionFunction = &conditionFunction_438_0;
crealNodes[683].actionsList[3] = &crealActions[401];
crealActions[401].alID = 401;
crealActions[401].numberOfActionItems = 1;
crealActions[401].actions[0].actionType = 2;
crealActions[401].actions[0].targetID = 899;
crealActions[401].actions[0].targetValue = 3.987544;
crealActions[401].actions[0].actionFunction = &actionFunction_401_0;
crealActions[401].numberOfConditions = 1;
crealActions[401].conditions[0].field = 899 ;
crealActions[401].conditions[0].relationType = 2 ;
crealActions[401].conditions[0].value = 31.900352 ;
crealActions[401].conditions[0].conditionFunction = &conditionFunction_401_0;
crealNodes[683].actionsList[4] = &crealActions[410];
crealActions[410].alID = 410;
crealActions[410].numberOfActionItems = 1;
crealActions[410].actions[0].actionType = 2;
crealActions[410].actions[0].targetID = 899;
crealActions[410].actions[0].targetValue = 3.987544;
crealActions[410].actions[0].actionFunction = &actionFunction_410_0;
crealActions[410].numberOfConditions = 1;
crealActions[410].conditions[0].field = 899 ;
crealActions[410].conditions[0].relationType = 2 ;
crealActions[410].conditions[0].value = 67.788248 ;
crealActions[410].conditions[0].conditionFunction = &conditionFunction_410_0;
crealNodes[683].actionsList[5] = &crealActions[444];
crealActions[444].alID = 444;
crealActions[444].numberOfActionItems = 1;
crealActions[444].actions[0].actionType = 1;
crealActions[444].actions[0].targetID = 905;
crealActions[444].actions[0].targetValue = 0.066459;
crealActions[444].actions[0].actionFunction = &actionFunction_444_0;
crealActions[444].numberOfConditions = 1;
crealActions[444].conditions[0].field = 899 ;
crealActions[444].conditions[0].relationType = 2 ;
crealActions[444].conditions[0].value = 95.701056 ;
crealActions[444].conditions[0].conditionFunction = &conditionFunction_444_0;
crealNodes[683].actionsList[6] = &crealActions[387];
crealActions[387].alID = 387;
crealActions[387].numberOfActionItems = 1;
crealActions[387].actions[0].actionType = 1;
crealActions[387].actions[0].targetID = 899;
crealActions[387].actions[0].targetValue = 34075.000000;
crealActions[387].actions[0].actionFunction = &actionFunction_387_0;
crealActions[387].numberOfConditions = 1;
crealActions[387].conditions[0].field = 906 ;
crealActions[387].conditions[0].relationType = 2 ;
crealActions[387].conditions[0].value = 0.000000 ;
crealActions[387].conditions[0].conditionFunction = &conditionFunction_387_0;
crealNodes[683].actionsList[7] = &crealActions[404];
crealActions[404].alID = 404;
crealActions[404].numberOfActionItems = 1;
crealActions[404].actions[0].actionType = 2;
crealActions[404].actions[0].targetID = 899;
crealActions[404].actions[0].targetValue = 3.987544;
crealActions[404].actions[0].actionFunction = &actionFunction_404_0;
crealActions[404].numberOfConditions = 2;
crealActions[404].conditions[0].field = 899 ;
crealActions[404].conditions[0].relationType = 2 ;
crealActions[404].conditions[0].value = 43.862984 ;
crealActions[404].conditions[0].conditionFunction = &conditionFunction_404_0;
crealActions[404].conditions[1].field = 899 ;
crealActions[404].conditions[1].relationType = 2 ;
crealActions[404].conditions[1].value = 43.862984 ;
crealActions[404].conditions[1].conditionFunction = &conditionFunction_404_1;
crealNodes[683].actionsList[8] = &crealActions[406];
crealActions[406].alID = 406;
crealActions[406].numberOfActionItems = 1;
crealActions[406].actions[0].actionType = 2;
crealActions[406].actions[0].targetID = 899;
crealActions[406].actions[0].targetValue = 3.987544;
crealActions[406].actions[0].actionFunction = &actionFunction_406_0;
crealActions[406].numberOfConditions = 1;
crealActions[406].conditions[0].field = 899 ;
crealActions[406].conditions[0].relationType = 2 ;
crealActions[406].conditions[0].value = 51.838072 ;
crealActions[406].conditions[0].conditionFunction = &conditionFunction_406_0;
crealNodes[683].actionsList[9] = &crealActions[393];
crealActions[393].alID = 393;
crealActions[393].numberOfActionItems = 1;
crealActions[393].actions[0].actionType = 2;
crealActions[393].actions[0].targetID = 899;
crealActions[393].actions[0].targetValue = 3.987544;
crealActions[393].actions[0].actionFunction = &actionFunction_393_0;
crealActions[393].numberOfConditions = 1;
crealActions[393].conditions[0].field = 899 ;
crealActions[393].conditions[0].relationType = 2 ;
crealActions[393].conditions[0].value = 0.000000 ;
crealActions[393].conditions[0].conditionFunction = &conditionFunction_393_0;
crealNodes[683].actionsList[10] = &crealActions[408];
crealActions[408].alID = 408;
crealActions[408].numberOfActionItems = 1;
crealActions[408].actions[0].actionType = 2;
crealActions[408].actions[0].targetID = 899;
crealActions[408].actions[0].targetValue = 3.987544;
crealActions[408].actions[0].actionFunction = &actionFunction_408_0;
crealActions[408].numberOfConditions = 1;
crealActions[408].conditions[0].field = 899 ;
crealActions[408].conditions[0].relationType = 2 ;
crealActions[408].conditions[0].value = 59.813160 ;
crealActions[408].conditions[0].conditionFunction = &conditionFunction_408_0;
crealNodes[683].actionsList[11] = &crealActions[395];
crealActions[395].alID = 395;
crealActions[395].numberOfActionItems = 1;
crealActions[395].actions[0].actionType = 2;
crealActions[395].actions[0].targetID = 899;
crealActions[395].actions[0].targetValue = 3.987544;
crealActions[395].actions[0].actionFunction = &actionFunction_395_0;
crealActions[395].numberOfConditions = 1;
crealActions[395].conditions[0].field = 899 ;
crealActions[395].conditions[0].relationType = 2 ;
crealActions[395].conditions[0].value = 7.975088 ;
crealActions[395].conditions[0].conditionFunction = &conditionFunction_395_0;
crealNodes[683].actionsList[12] = &crealActions[409];
crealActions[409].alID = 409;
crealActions[409].numberOfActionItems = 1;
crealActions[409].actions[0].actionType = 2;
crealActions[409].actions[0].targetID = 899;
crealActions[409].actions[0].targetValue = 3.987544;
crealActions[409].actions[0].actionFunction = &actionFunction_409_0;
crealActions[409].numberOfConditions = 1;
crealActions[409].conditions[0].field = 899 ;
crealActions[409].conditions[0].relationType = 2 ;
crealActions[409].conditions[0].value = 63.800704 ;
crealActions[409].conditions[0].conditionFunction = &conditionFunction_409_0;
crealNodes[683].actionsList[13] = &crealActions[396];
crealActions[396].alID = 396;
crealActions[396].numberOfActionItems = 1;
crealActions[396].actions[0].actionType = 2;
crealActions[396].actions[0].targetID = 899;
crealActions[396].actions[0].targetValue = 3.987544;
crealActions[396].actions[0].actionFunction = &actionFunction_396_0;
crealActions[396].numberOfConditions = 1;
crealActions[396].conditions[0].field = 899 ;
crealActions[396].conditions[0].relationType = 2 ;
crealActions[396].conditions[0].value = 11.962632 ;
crealActions[396].conditions[0].conditionFunction = &conditionFunction_396_0;
crealNodes[683].actionsList[14] = &crealActions[397];
crealActions[397].alID = 397;
crealActions[397].numberOfActionItems = 1;
crealActions[397].actions[0].actionType = 2;
crealActions[397].actions[0].targetID = 899;
crealActions[397].actions[0].targetValue = 3.987544;
crealActions[397].actions[0].actionFunction = &actionFunction_397_0;
crealActions[397].numberOfConditions = 1;
crealActions[397].conditions[0].field = 899 ;
crealActions[397].conditions[0].relationType = 2 ;
crealActions[397].conditions[0].value = 15.950176 ;
crealActions[397].conditions[0].conditionFunction = &conditionFunction_397_0;
crealNodes[683].actionsList[15] = &crealActions[398];
crealActions[398].alID = 398;
crealActions[398].numberOfActionItems = 1;
crealActions[398].actions[0].actionType = 2;
crealActions[398].actions[0].targetID = 899;
crealActions[398].actions[0].targetValue = 3.987544;
crealActions[398].actions[0].actionFunction = &actionFunction_398_0;
crealActions[398].numberOfConditions = 1;
crealActions[398].conditions[0].field = 899 ;
crealActions[398].conditions[0].relationType = 2 ;
crealActions[398].conditions[0].value = 19.937720 ;
crealActions[398].conditions[0].conditionFunction = &conditionFunction_398_0;
crealNodes[683].actionsList[16] = &crealActions[399];
crealActions[399].alID = 399;
crealActions[399].numberOfActionItems = 1;
crealActions[399].actions[0].actionType = 2;
crealActions[399].actions[0].targetID = 899;
crealActions[399].actions[0].targetValue = 3.987544;
crealActions[399].actions[0].actionFunction = &actionFunction_399_0;
crealActions[399].numberOfConditions = 1;
crealActions[399].conditions[0].field = 899 ;
crealActions[399].conditions[0].relationType = 2 ;
crealActions[399].conditions[0].value = 23.925264 ;
crealActions[399].conditions[0].conditionFunction = &conditionFunction_399_0;
crealNodes[683].actionsList[17] = &crealActions[437];
crealActions[437].alID = 437;
crealActions[437].numberOfActionItems = 1;
crealActions[437].actions[0].actionType = 1;
crealActions[437].actions[0].targetID = 905;
crealActions[437].actions[0].targetValue = 0.066459;
crealActions[437].actions[0].actionFunction = &actionFunction_437_0;
crealActions[437].numberOfConditions = 1;
crealActions[437].conditions[0].field = 899 ;
crealActions[437].conditions[0].relationType = 2 ;
crealActions[437].conditions[0].value = 67.788248 ;
crealActions[437].conditions[0].conditionFunction = &conditionFunction_437_0;
crealNodes[683].actionsList[18] = &crealActions[400];
crealActions[400].alID = 400;
crealActions[400].numberOfActionItems = 1;
crealActions[400].actions[0].actionType = 2;
crealActions[400].actions[0].targetID = 899;
crealActions[400].actions[0].targetValue = 3.987544;
crealActions[400].actions[0].actionFunction = &actionFunction_400_0;
crealActions[400].numberOfConditions = 1;
crealActions[400].conditions[0].field = 899 ;
crealActions[400].conditions[0].relationType = 2 ;
crealActions[400].conditions[0].value = 27.912808 ;
crealActions[400].conditions[0].conditionFunction = &conditionFunction_400_0;
crealNodes[683].actionsList[19] = &crealActions[439];
crealActions[439].alID = 439;
crealActions[439].numberOfActionItems = 1;
crealActions[439].actions[0].actionType = 1;
crealActions[439].actions[0].targetID = 905;
crealActions[439].actions[0].targetValue = 0.066459;
crealActions[439].actions[0].actionFunction = &actionFunction_439_0;
crealActions[439].numberOfConditions = 1;
crealActions[439].conditions[0].field = 899 ;
crealActions[439].conditions[0].relationType = 2 ;
crealActions[439].conditions[0].value = 75.763336 ;
crealActions[439].conditions[0].conditionFunction = &conditionFunction_439_0;
crealNodes[683].actionsList[20] = &crealActions[402];
crealActions[402].alID = 402;
crealActions[402].numberOfActionItems = 1;
crealActions[402].actions[0].actionType = 2;
crealActions[402].actions[0].targetID = 899;
crealActions[402].actions[0].targetValue = 3.987544;
crealActions[402].actions[0].actionFunction = &actionFunction_402_0;
crealActions[402].numberOfConditions = 1;
crealActions[402].conditions[0].field = 899 ;
crealActions[402].conditions[0].relationType = 2 ;
crealActions[402].conditions[0].value = 35.887896 ;
crealActions[402].conditions[0].conditionFunction = &conditionFunction_402_0;
crealNodes[683].actionsList[21] = &crealActions[403];
crealActions[403].alID = 403;
crealActions[403].numberOfActionItems = 1;
crealActions[403].actions[0].actionType = 2;
crealActions[403].actions[0].targetID = 899;
crealActions[403].actions[0].targetValue = 3.987544;
crealActions[403].actions[0].actionFunction = &actionFunction_403_0;
crealActions[403].numberOfConditions = 1;
crealActions[403].conditions[0].field = 899 ;
crealActions[403].conditions[0].relationType = 2 ;
crealActions[403].conditions[0].value = 39.875440 ;
crealActions[403].conditions[0].conditionFunction = &conditionFunction_403_0;
crealNodes[683].actionsList[22] = &crealActions[405];
crealActions[405].alID = 405;
crealActions[405].numberOfActionItems = 2;
crealActions[405].actions[0].actionType = 1;
crealActions[405].actions[0].targetID = 0;
crealActions[405].actions[0].targetValue = 0.000000;
crealActions[405].actions[0].actionFunction = &actionFunction_405_0;
crealActions[405].actions[1].actionType = 2;
crealActions[405].actions[1].targetID = 899;
crealActions[405].actions[1].targetValue = 3.987544;
crealActions[405].actions[1].actionFunction = &actionFunction_405_1;
crealActions[405].numberOfConditions = 2;
crealActions[405].conditions[0].field = 899 ;
crealActions[405].conditions[0].relationType = 2 ;
crealActions[405].conditions[0].value = 47.850528 ;
crealActions[405].conditions[0].conditionFunction = &conditionFunction_405_0;
crealActions[405].conditions[1].field = 899 ;
crealActions[405].conditions[1].relationType = 2 ;
crealActions[405].conditions[1].value = 47.850528 ;
crealActions[405].conditions[1].conditionFunction = &conditionFunction_405_1;
crealNodes[683].actionsList[23] = &crealActions[411];
crealActions[411].alID = 411;
crealActions[411].numberOfActionItems = 1;
crealActions[411].actions[0].actionType = 2;
crealActions[411].actions[0].targetID = 925;
crealActions[411].actions[0].targetValue = 3.987544;
crealActions[411].actions[0].actionFunction = &actionFunction_411_0;
crealActions[411].numberOfConditions = 1;
crealActions[411].conditions[0].field = 899 ;
crealActions[411].conditions[0].relationType = 2 ;
crealActions[411].conditions[0].value = 71.775792 ;
crealActions[411].conditions[0].conditionFunction = &conditionFunction_411_0;
crealNodes[683].actionsList[24] = &crealActions[412];
crealActions[412].alID = 412;
crealActions[412].numberOfActionItems = 1;
crealActions[412].actions[0].actionType = 2;
crealActions[412].actions[0].targetID = 899;
crealActions[412].actions[0].targetValue = 3.987544;
crealActions[412].actions[0].actionFunction = &actionFunction_412_0;
crealActions[412].numberOfConditions = 1;
crealActions[412].conditions[0].field = 899 ;
crealActions[412].conditions[0].relationType = 2 ;
crealActions[412].conditions[0].value = 75.763336 ;
crealActions[412].conditions[0].conditionFunction = &conditionFunction_412_0;
crealNodes[683].actionsList[25] = &crealActions[413];
crealActions[413].alID = 413;
crealActions[413].numberOfActionItems = 1;
crealActions[413].actions[0].actionType = 2;
crealActions[413].actions[0].targetID = 899;
crealActions[413].actions[0].targetValue = 3.987544;
crealActions[413].actions[0].actionFunction = &actionFunction_413_0;
crealActions[413].numberOfConditions = 1;
crealActions[413].conditions[0].field = 899 ;
crealActions[413].conditions[0].relationType = 2 ;
crealActions[413].conditions[0].value = 79.750880 ;
crealActions[413].conditions[0].conditionFunction = &conditionFunction_413_0;
crealNodes[683].actionsList[26] = &crealActions[414];
crealActions[414].alID = 414;
crealActions[414].numberOfActionItems = 1;
crealActions[414].actions[0].actionType = 2;
crealActions[414].actions[0].targetID = 899;
crealActions[414].actions[0].targetValue = 3.987544;
crealActions[414].actions[0].actionFunction = &actionFunction_414_0;
crealActions[414].numberOfConditions = 1;
crealActions[414].conditions[0].field = 899 ;
crealActions[414].conditions[0].relationType = 2 ;
crealActions[414].conditions[0].value = 83.738424 ;
crealActions[414].conditions[0].conditionFunction = &conditionFunction_414_0;
crealNodes[683].actionsList[27] = &crealActions[415];
crealActions[415].alID = 415;
crealActions[415].numberOfActionItems = 1;
crealActions[415].actions[0].actionType = 2;
crealActions[415].actions[0].targetID = 899;
crealActions[415].actions[0].targetValue = 3.987544;
crealActions[415].actions[0].actionFunction = &actionFunction_415_0;
crealActions[415].numberOfConditions = 1;
crealActions[415].conditions[0].field = 899 ;
crealActions[415].conditions[0].relationType = 2 ;
crealActions[415].conditions[0].value = 87.725968 ;
crealActions[415].conditions[0].conditionFunction = &conditionFunction_415_0;
crealNodes[683].actionsList[28] = &crealActions[416];
crealActions[416].alID = 416;
crealActions[416].numberOfActionItems = 1;
crealActions[416].actions[0].actionType = 2;
crealActions[416].actions[0].targetID = 899;
crealActions[416].actions[0].targetValue = 3.987544;
crealActions[416].actions[0].actionFunction = &actionFunction_416_0;
crealActions[416].numberOfConditions = 1;
crealActions[416].conditions[0].field = 899 ;
crealActions[416].conditions[0].relationType = 2 ;
crealActions[416].conditions[0].value = 91.713512 ;
crealActions[416].conditions[0].conditionFunction = &conditionFunction_416_0;
crealNodes[683].actionsList[29] = &crealActions[417];
crealActions[417].alID = 417;
crealActions[417].numberOfActionItems = 1;
crealActions[417].actions[0].actionType = 2;
crealActions[417].actions[0].targetID = 899;
crealActions[417].actions[0].targetValue = 3.987544;
crealActions[417].actions[0].actionFunction = &actionFunction_417_0;
crealActions[417].numberOfConditions = 1;
crealActions[417].conditions[0].field = 899 ;
crealActions[417].conditions[0].relationType = 2 ;
crealActions[417].conditions[0].value = 95.701056 ;
crealActions[417].conditions[0].conditionFunction = &conditionFunction_417_0;
crealNodes[683].actionsList[30] = &crealActions[419];
crealActions[419].alID = 419;
crealActions[419].numberOfActionItems = 1;
crealActions[419].actions[0].actionType = 2;
crealActions[419].actions[0].targetID = 899;
crealActions[419].actions[0].targetValue = 3.987544;
crealActions[419].actions[0].actionFunction = &actionFunction_419_0;
crealActions[419].numberOfConditions = 1;
crealActions[419].conditions[0].field = 899 ;
crealActions[419].conditions[0].relationType = 2 ;
crealActions[419].conditions[0].value = 99.688600 ;
crealActions[419].conditions[0].conditionFunction = &conditionFunction_419_0;
crealNodes[683].actionsList[31] = &crealActions[420];
crealActions[420].alID = 420;
crealActions[420].numberOfActionItems = 1;
crealActions[420].actions[0].actionType = 1;
crealActions[420].actions[0].targetID = 905;
crealActions[420].actions[0].targetValue = 0.066459;
crealActions[420].actions[0].actionFunction = &actionFunction_420_0;
crealActions[420].numberOfConditions = 1;
crealActions[420].conditions[0].field = 899 ;
crealActions[420].conditions[0].relationType = 2 ;
crealActions[420].conditions[0].value = 0.000000 ;
crealActions[420].conditions[0].conditionFunction = &conditionFunction_420_0;
crealNodes[683].actionsList[32] = &crealActions[421];
crealActions[421].alID = 421;
crealActions[421].numberOfActionItems = 1;
crealActions[421].actions[0].actionType = 1;
crealActions[421].actions[0].targetID = 905;
crealActions[421].actions[0].targetValue = 0.066459;
crealActions[421].actions[0].actionFunction = &actionFunction_421_0;
crealActions[421].numberOfConditions = 1;
crealActions[421].conditions[0].field = 899 ;
crealActions[421].conditions[0].relationType = 2 ;
crealActions[421].conditions[0].value = 3.987544 ;
crealActions[421].conditions[0].conditionFunction = &conditionFunction_421_0;
crealNodes[683].actionsList[33] = &crealActions[422];
crealActions[422].alID = 422;
crealActions[422].numberOfActionItems = 1;
crealActions[422].actions[0].actionType = 1;
crealActions[422].actions[0].targetID = 905;
crealActions[422].actions[0].targetValue = 0.066459;
crealActions[422].actions[0].actionFunction = &actionFunction_422_0;
crealActions[422].numberOfConditions = 1;
crealActions[422].conditions[0].field = 899 ;
crealActions[422].conditions[0].relationType = 2 ;
crealActions[422].conditions[0].value = 7.975088 ;
crealActions[422].conditions[0].conditionFunction = &conditionFunction_422_0;
crealNodes[683].actionsList[34] = &crealActions[423];
crealActions[423].alID = 423;
crealActions[423].numberOfActionItems = 1;
crealActions[423].actions[0].actionType = 1;
crealActions[423].actions[0].targetID = 905;
crealActions[423].actions[0].targetValue = 0.066459;
crealActions[423].actions[0].actionFunction = &actionFunction_423_0;
crealActions[423].numberOfConditions = 1;
crealActions[423].conditions[0].field = 899 ;
crealActions[423].conditions[0].relationType = 2 ;
crealActions[423].conditions[0].value = 11.962632 ;
crealActions[423].conditions[0].conditionFunction = &conditionFunction_423_0;
crealNodes[683].actionsList[35] = &crealActions[424];
crealActions[424].alID = 424;
crealActions[424].numberOfActionItems = 1;
crealActions[424].actions[0].actionType = 1;
crealActions[424].actions[0].targetID = 905;
crealActions[424].actions[0].targetValue = 0.066459;
crealActions[424].actions[0].actionFunction = &actionFunction_424_0;
crealActions[424].numberOfConditions = 1;
crealActions[424].conditions[0].field = 899 ;
crealActions[424].conditions[0].relationType = 2 ;
crealActions[424].conditions[0].value = 15.950176 ;
crealActions[424].conditions[0].conditionFunction = &conditionFunction_424_0;
crealNodes[683].actionsList[36] = &crealActions[425];
crealActions[425].alID = 425;
crealActions[425].numberOfActionItems = 1;
crealActions[425].actions[0].actionType = 1;
crealActions[425].actions[0].targetID = 905;
crealActions[425].actions[0].targetValue = 0.066459;
crealActions[425].actions[0].actionFunction = &actionFunction_425_0;
crealActions[425].numberOfConditions = 1;
crealActions[425].conditions[0].field = 899 ;
crealActions[425].conditions[0].relationType = 2 ;
crealActions[425].conditions[0].value = 19.937720 ;
crealActions[425].conditions[0].conditionFunction = &conditionFunction_425_0;
crealNodes[683].actionsList[37] = &crealActions[426];
crealActions[426].alID = 426;
crealActions[426].numberOfActionItems = 1;
crealActions[426].actions[0].actionType = 1;
crealActions[426].actions[0].targetID = 905;
crealActions[426].actions[0].targetValue = 0.066459;
crealActions[426].actions[0].actionFunction = &actionFunction_426_0;
crealActions[426].numberOfConditions = 1;
crealActions[426].conditions[0].field = 899 ;
crealActions[426].conditions[0].relationType = 2 ;
crealActions[426].conditions[0].value = 23.925264 ;
crealActions[426].conditions[0].conditionFunction = &conditionFunction_426_0;
crealNodes[683].actionsList[38] = &crealActions[427];
crealActions[427].alID = 427;
crealActions[427].numberOfActionItems = 1;
crealActions[427].actions[0].actionType = 1;
crealActions[427].actions[0].targetID = 905;
crealActions[427].actions[0].targetValue = 0.066459;
crealActions[427].actions[0].actionFunction = &actionFunction_427_0;
crealActions[427].numberOfConditions = 1;
crealActions[427].conditions[0].field = 899 ;
crealActions[427].conditions[0].relationType = 2 ;
crealActions[427].conditions[0].value = 27.912808 ;
crealActions[427].conditions[0].conditionFunction = &conditionFunction_427_0;
crealNodes[683].actionsList[39] = &crealActions[428];
crealActions[428].alID = 428;
crealActions[428].numberOfActionItems = 1;
crealActions[428].actions[0].actionType = 1;
crealActions[428].actions[0].targetID = 905;
crealActions[428].actions[0].targetValue = 0.066459;
crealActions[428].actions[0].actionFunction = &actionFunction_428_0;
crealActions[428].numberOfConditions = 1;
crealActions[428].conditions[0].field = 899 ;
crealActions[428].conditions[0].relationType = 2 ;
crealActions[428].conditions[0].value = 31.900352 ;
crealActions[428].conditions[0].conditionFunction = &conditionFunction_428_0;
crealNodes[683].actionsList[40] = &crealActions[429];
crealActions[429].alID = 429;
crealActions[429].numberOfActionItems = 1;
crealActions[429].actions[0].actionType = 1;
crealActions[429].actions[0].targetID = 905;
crealActions[429].actions[0].targetValue = 0.066459;
crealActions[429].actions[0].actionFunction = &actionFunction_429_0;
crealActions[429].numberOfConditions = 1;
crealActions[429].conditions[0].field = 899 ;
crealActions[429].conditions[0].relationType = 2 ;
crealActions[429].conditions[0].value = 35.887896 ;
crealActions[429].conditions[0].conditionFunction = &conditionFunction_429_0;
crealNodes[683].actionsList[41] = &crealActions[430];
crealActions[430].alID = 430;
crealActions[430].numberOfActionItems = 1;
crealActions[430].actions[0].actionType = 1;
crealActions[430].actions[0].targetID = 905;
crealActions[430].actions[0].targetValue = 0.066459;
crealActions[430].actions[0].actionFunction = &actionFunction_430_0;
crealActions[430].numberOfConditions = 1;
crealActions[430].conditions[0].field = 899 ;
crealActions[430].conditions[0].relationType = 2 ;
crealActions[430].conditions[0].value = 39.875440 ;
crealActions[430].conditions[0].conditionFunction = &conditionFunction_430_0;
crealNodes[683].actionsList[42] = &crealActions[431];
crealActions[431].alID = 431;
crealActions[431].numberOfActionItems = 1;
crealActions[431].actions[0].actionType = 1;
crealActions[431].actions[0].targetID = 905;
crealActions[431].actions[0].targetValue = 0.066459;
crealActions[431].actions[0].actionFunction = &actionFunction_431_0;
crealActions[431].numberOfConditions = 1;
crealActions[431].conditions[0].field = 899 ;
crealActions[431].conditions[0].relationType = 2 ;
crealActions[431].conditions[0].value = 43.862984 ;
crealActions[431].conditions[0].conditionFunction = &conditionFunction_431_0;
crealNodes[683].actionsList[43] = &crealActions[432];
crealActions[432].alID = 432;
crealActions[432].numberOfActionItems = 1;
crealActions[432].actions[0].actionType = 1;
crealActions[432].actions[0].targetID = 905;
crealActions[432].actions[0].targetValue = 0.066459;
crealActions[432].actions[0].actionFunction = &actionFunction_432_0;
crealActions[432].numberOfConditions = 1;
crealActions[432].conditions[0].field = 899 ;
crealActions[432].conditions[0].relationType = 2 ;
crealActions[432].conditions[0].value = 47.850528 ;
crealActions[432].conditions[0].conditionFunction = &conditionFunction_432_0;
crealNodes[683].actionsList[44] = &crealActions[433];
crealActions[433].alID = 433;
crealActions[433].numberOfActionItems = 1;
crealActions[433].actions[0].actionType = 1;
crealActions[433].actions[0].targetID = 905;
crealActions[433].actions[0].targetValue = 0.066459;
crealActions[433].actions[0].actionFunction = &actionFunction_433_0;
crealActions[433].numberOfConditions = 1;
crealActions[433].conditions[0].field = 899 ;
crealActions[433].conditions[0].relationType = 2 ;
crealActions[433].conditions[0].value = 51.838072 ;
crealActions[433].conditions[0].conditionFunction = &conditionFunction_433_0;
crealNodes[683].actionsList[45] = &crealActions[434];
crealActions[434].alID = 434;
crealActions[434].numberOfActionItems = 1;
crealActions[434].actions[0].actionType = 1;
crealActions[434].actions[0].targetID = 905;
crealActions[434].actions[0].targetValue = 0.066459;
crealActions[434].actions[0].actionFunction = &actionFunction_434_0;
crealActions[434].numberOfConditions = 1;
crealActions[434].conditions[0].field = 899 ;
crealActions[434].conditions[0].relationType = 2 ;
crealActions[434].conditions[0].value = 55.825616 ;
crealActions[434].conditions[0].conditionFunction = &conditionFunction_434_0;
crealNodes[683].actionsList[46] = &crealActions[435];
crealActions[435].alID = 435;
crealActions[435].numberOfActionItems = 1;
crealActions[435].actions[0].actionType = 1;
crealActions[435].actions[0].targetID = 905;
crealActions[435].actions[0].targetValue = 0.066459;
crealActions[435].actions[0].actionFunction = &actionFunction_435_0;
crealActions[435].numberOfConditions = 1;
crealActions[435].conditions[0].field = 899 ;
crealActions[435].conditions[0].relationType = 2 ;
crealActions[435].conditions[0].value = 59.813160 ;
crealActions[435].conditions[0].conditionFunction = &conditionFunction_435_0;
crealNodes[683].actionsList[47] = &crealActions[436];
crealActions[436].alID = 436;
crealActions[436].numberOfActionItems = 1;
crealActions[436].actions[0].actionType = 1;
crealActions[436].actions[0].targetID = 905;
crealActions[436].actions[0].targetValue = 0.066459;
crealActions[436].actions[0].actionFunction = &actionFunction_436_0;
crealActions[436].numberOfConditions = 1;
crealActions[436].conditions[0].field = 899 ;
crealActions[436].conditions[0].relationType = 2 ;
crealActions[436].conditions[0].value = 63.800704 ;
crealActions[436].conditions[0].conditionFunction = &conditionFunction_436_0;
crealNodes[683].actionsList[48] = &crealActions[440];
crealActions[440].alID = 440;
crealActions[440].numberOfActionItems = 1;
crealActions[440].actions[0].actionType = 1;
crealActions[440].actions[0].targetID = 905;
crealActions[440].actions[0].targetValue = 0.066459;
crealActions[440].actions[0].actionFunction = &actionFunction_440_0;
crealActions[440].numberOfConditions = 1;
crealActions[440].conditions[0].field = 899 ;
crealActions[440].conditions[0].relationType = 2 ;
crealActions[440].conditions[0].value = 79.750880 ;
crealActions[440].conditions[0].conditionFunction = &conditionFunction_440_0;
crealNodes[683].actionsList[49] = &crealActions[441];
crealActions[441].alID = 441;
crealActions[441].numberOfActionItems = 1;
crealActions[441].actions[0].actionType = 1;
crealActions[441].actions[0].targetID = 905;
crealActions[441].actions[0].targetValue = 0.066459;
crealActions[441].actions[0].actionFunction = &actionFunction_441_0;
crealActions[441].numberOfConditions = 1;
crealActions[441].conditions[0].field = 899 ;
crealActions[441].conditions[0].relationType = 2 ;
crealActions[441].conditions[0].value = 83.738424 ;
crealActions[441].conditions[0].conditionFunction = &conditionFunction_441_0;
crealNodes[683].actionsList[50] = &crealActions[442];
crealActions[442].alID = 442;
crealActions[442].numberOfActionItems = 1;
crealActions[442].actions[0].actionType = 1;
crealActions[442].actions[0].targetID = 905;
crealActions[442].actions[0].targetValue = 0.066459;
crealActions[442].actions[0].actionFunction = &actionFunction_442_0;
crealActions[442].numberOfConditions = 1;
crealActions[442].conditions[0].field = 899 ;
crealActions[442].conditions[0].relationType = 2 ;
crealActions[442].conditions[0].value = 87.725968 ;
crealActions[442].conditions[0].conditionFunction = &conditionFunction_442_0;
crealNodes[683].actionsList[51] = &crealActions[443];
crealActions[443].alID = 443;
crealActions[443].numberOfActionItems = 1;
crealActions[443].actions[0].actionType = 1;
crealActions[443].actions[0].targetID = 905;
crealActions[443].actions[0].targetValue = 0.066459;
crealActions[443].actions[0].actionFunction = &actionFunction_443_0;
crealActions[443].numberOfConditions = 1;
crealActions[443].conditions[0].field = 899 ;
crealActions[443].conditions[0].relationType = 2 ;
crealActions[443].conditions[0].value = 91.713512 ;
crealActions[443].conditions[0].conditionFunction = &conditionFunction_443_0;
crealNodes[683].actionsList[52] = &crealActions[445];
crealActions[445].alID = 445;
crealActions[445].numberOfActionItems = 1;
crealActions[445].actions[0].actionType = 1;
crealActions[445].actions[0].targetID = 905;
crealActions[445].actions[0].targetValue = 0.066459;
crealActions[445].actions[0].actionFunction = &actionFunction_445_0;
crealActions[445].numberOfConditions = 1;
crealActions[445].conditions[0].field = 899 ;
crealActions[445].conditions[0].relationType = 2 ;
crealActions[445].conditions[0].value = 99.688600 ;
crealActions[445].conditions[0].conditionFunction = &conditionFunction_445_0;
crealNodes[684].numberOfActions = 4;
crealNodes[684].actionsList[0] = &crealActions[495];
crealActions[495].alID = 495;
crealActions[495].numberOfActionItems = 1;
crealActions[495].actions[0].actionType = 2;
crealActions[495].actions[0].targetID = 903;
crealActions[495].actions[0].targetValue = 0.010000;
crealActions[495].actions[0].actionFunction = &actionFunction_495_0;
crealActions[495].numberOfConditions = 1;
crealActions[495].conditions[0].field = 905 ;
crealActions[495].conditions[0].relationType = 2 ;
crealActions[495].conditions[0].value = 1000.000000 ;
crealActions[495].conditions[0].conditionFunction = &conditionFunction_495_0;
crealNodes[684].actionsList[1] = &crealActions[496];
crealActions[496].alID = 496;
crealActions[496].numberOfActionItems = 1;
crealActions[496].actions[0].actionType = 2;
crealActions[496].actions[0].targetID = 903;
crealActions[496].actions[0].targetValue = 0.001000;
crealActions[496].actions[0].actionFunction = &actionFunction_496_0;
crealActions[496].numberOfConditions = 1;
crealActions[496].conditions[0].field = 905 ;
crealActions[496].conditions[0].relationType = 3 ;
crealActions[496].conditions[0].value = 1000.000000 ;
crealActions[496].conditions[0].conditionFunction = &conditionFunction_496_0;
crealNodes[684].actionsList[2] = &crealActions[497];
crealActions[497].alID = 497;
crealActions[497].numberOfActionItems = 1;
crealActions[497].actions[0].actionType = 2;
crealActions[497].actions[0].targetID = 904;
crealActions[497].actions[0].targetValue = 0.010000;
crealActions[497].actions[0].actionFunction = &actionFunction_497_0;
crealActions[497].numberOfConditions = 1;
crealActions[497].conditions[0].field = 905 ;
crealActions[497].conditions[0].relationType = 2 ;
crealActions[497].conditions[0].value = 1000.000000 ;
crealActions[497].conditions[0].conditionFunction = &conditionFunction_497_0;
crealNodes[684].actionsList[3] = &crealActions[498];
crealActions[498].alID = 498;
crealActions[498].numberOfActionItems = 1;
crealActions[498].actions[0].actionType = 2;
crealActions[498].actions[0].targetID = 904;
crealActions[498].actions[0].targetValue = 0.001000;
crealActions[498].actions[0].actionFunction = &actionFunction_498_0;
crealActions[498].numberOfConditions = 1;
crealActions[498].conditions[0].field = 905 ;
crealActions[498].conditions[0].relationType = 3 ;
crealActions[498].conditions[0].value = 1000.000000 ;
crealActions[498].conditions[0].conditionFunction = &conditionFunction_498_0;
crealNodes[688].numberOfProperties = 1;
crealNodes[688].properties[0] = &crealProperties[909];
crealProperties[909] = 0.000000;
crealNodes[688].numberOfActions = 9;
crealNodes[688].actionsList[0] = &crealActions[472];
crealActions[472].alID = 472;
crealActions[472].numberOfActionItems = 1;
crealActions[472].actions[0].actionType = 1;
crealActions[472].actions[0].targetID = 905;
crealActions[472].actions[0].targetValue = 0.016667;
crealActions[472].actions[0].actionFunction = &actionFunction_472_0;
crealActions[472].numberOfConditions = 2;
crealActions[472].conditions[0].field = 898 ;
crealActions[472].conditions[0].relationType = 4 ;
crealActions[472].conditions[0].value = 43375.000000 ;
crealActions[472].conditions[0].conditionFunction = &conditionFunction_472_0;
crealActions[472].conditions[1].field = 898 ;
crealActions[472].conditions[1].relationType = 5 ;
crealActions[472].conditions[1].value = 45175.000000 ;
crealActions[472].conditions[1].conditionFunction = &conditionFunction_472_1;
crealNodes[688].actionsList[1] = &crealActions[469];
crealActions[469].alID = 469;
crealActions[469].numberOfActionItems = 1;
crealActions[469].actions[0].actionType = 2;
crealActions[469].actions[0].targetID = 909;
crealActions[469].actions[0].targetValue = 8.754000;
crealActions[469].actions[0].actionFunction = &actionFunction_469_0;
crealActions[469].numberOfConditions = 2;
crealActions[469].conditions[0].field = 898 ;
crealActions[469].conditions[0].relationType = 2 ;
crealActions[469].conditions[0].value = 43205.000000 ;
crealActions[469].conditions[0].conditionFunction = &conditionFunction_469_0;
crealActions[469].conditions[1].field = 898 ;
crealActions[469].conditions[1].relationType = 3 ;
crealActions[469].conditions[1].value = 63785.000000 ;
crealActions[469].conditions[1].conditionFunction = &conditionFunction_469_1;
crealNodes[688].actionsList[2] = &crealActions[464];
crealActions[464].alID = 464;
crealActions[464].numberOfActionItems = 1;
crealActions[464].actions[0].actionType = 1;
crealActions[464].actions[0].targetID = 909;
crealActions[464].actions[0].targetValue = 8.754000;
crealActions[464].actions[0].actionFunction = &actionFunction_464_0;
crealActions[464].numberOfConditions = 2;
crealActions[464].conditions[0].field = 898 ;
crealActions[464].conditions[0].relationType = 2 ;
crealActions[464].conditions[0].value = 21604.000000 ;
crealActions[464].conditions[0].conditionFunction = &conditionFunction_464_0;
crealActions[464].conditions[1].field = 898 ;
crealActions[464].conditions[1].relationType = 3 ;
crealActions[464].conditions[1].value = 42184.000000 ;
crealActions[464].conditions[1].conditionFunction = &conditionFunction_464_1;
crealNodes[688].actionsList[3] = &crealActions[466];
crealActions[466].alID = 466;
crealActions[466].numberOfActionItems = 1;
crealActions[466].actions[0].actionType = 1;
crealActions[466].actions[0].targetID = 909;
crealActions[466].actions[0].targetValue = 8.754000;
crealActions[466].actions[0].actionFunction = &actionFunction_466_0;
crealActions[466].numberOfConditions = 2;
crealActions[466].conditions[0].field = 898 ;
crealActions[466].conditions[0].relationType = 2 ;
crealActions[466].conditions[0].value = 43204.000000 ;
crealActions[466].conditions[0].conditionFunction = &conditionFunction_466_0;
crealActions[466].conditions[1].field = 898 ;
crealActions[466].conditions[1].relationType = 3 ;
crealActions[466].conditions[1].value = 63784.000000 ;
crealActions[466].conditions[1].conditionFunction = &conditionFunction_466_1;
crealNodes[688].actionsList[4] = &crealActions[470];
crealActions[470].alID = 470;
crealActions[470].numberOfActionItems = 1;
crealActions[470].actions[0].actionType = 2;
crealActions[470].actions[0].targetID = 909;
crealActions[470].actions[0].targetValue = 8.754000;
crealActions[470].actions[0].actionFunction = &actionFunction_470_0;
crealActions[470].numberOfConditions = 2;
crealActions[470].conditions[0].field = 898 ;
crealActions[470].conditions[0].relationType = 2 ;
crealActions[470].conditions[0].value = 64805.000000 ;
crealActions[470].conditions[0].conditionFunction = &conditionFunction_470_0;
crealActions[470].conditions[1].field = 898 ;
crealActions[470].conditions[1].relationType = 3 ;
crealActions[470].conditions[1].value = 85385.000000 ;
crealActions[470].conditions[1].conditionFunction = &conditionFunction_470_1;
crealNodes[688].actionsList[5] = &crealActions[467];
crealActions[467].alID = 467;
crealActions[467].numberOfActionItems = 1;
crealActions[467].actions[0].actionType = 1;
crealActions[467].actions[0].targetID = 909;
crealActions[467].actions[0].targetValue = 8.754000;
crealActions[467].actions[0].actionFunction = &actionFunction_467_0;
crealActions[467].numberOfConditions = 2;
crealActions[467].conditions[0].field = 898 ;
crealActions[467].conditions[0].relationType = 2 ;
crealActions[467].conditions[0].value = 64804.000000 ;
crealActions[467].conditions[0].conditionFunction = &conditionFunction_467_0;
crealActions[467].conditions[1].field = 898 ;
crealActions[467].conditions[1].relationType = 3 ;
crealActions[467].conditions[1].value = 85384.000000 ;
crealActions[467].conditions[1].conditionFunction = &conditionFunction_467_1;
crealNodes[688].actionsList[6] = &crealActions[471];
crealActions[471].alID = 471;
crealActions[471].numberOfActionItems = 1;
crealActions[471].actions[0].actionType = 1;
crealActions[471].actions[0].targetID = 905;
crealActions[471].actions[0].targetValue = 0.016667;
crealActions[471].actions[0].actionFunction = &actionFunction_471_0;
crealActions[471].numberOfConditions = 2;
crealActions[471].conditions[0].field = 898 ;
crealActions[471].conditions[0].relationType = 4 ;
crealActions[471].conditions[0].value = 21775.000000 ;
crealActions[471].conditions[0].conditionFunction = &conditionFunction_471_0;
crealActions[471].conditions[1].field = 898 ;
crealActions[471].conditions[1].relationType = 5 ;
crealActions[471].conditions[1].value = 23575.000000 ;
crealActions[471].conditions[1].conditionFunction = &conditionFunction_471_1;
crealNodes[688].actionsList[7] = &crealActions[468];
crealActions[468].alID = 468;
crealActions[468].numberOfActionItems = 1;
crealActions[468].actions[0].actionType = 2;
crealActions[468].actions[0].targetID = 909;
crealActions[468].actions[0].targetValue = 8.754000;
crealActions[468].actions[0].actionFunction = &actionFunction_468_0;
crealActions[468].numberOfConditions = 2;
crealActions[468].conditions[0].field = 898 ;
crealActions[468].conditions[0].relationType = 4 ;
crealActions[468].conditions[0].value = 21605.000000 ;
crealActions[468].conditions[0].conditionFunction = &conditionFunction_468_0;
crealActions[468].conditions[1].field = 898 ;
crealActions[468].conditions[1].relationType = 3 ;
crealActions[468].conditions[1].value = 42185.000000 ;
crealActions[468].conditions[1].conditionFunction = &conditionFunction_468_1;
crealNodes[688].actionsList[8] = &crealActions[473];
crealActions[473].alID = 473;
crealActions[473].numberOfActionItems = 1;
crealActions[473].actions[0].actionType = 1;
crealActions[473].actions[0].targetID = 905;
crealActions[473].actions[0].targetValue = 0.016667;
crealActions[473].actions[0].actionFunction = &actionFunction_473_0;
crealActions[473].numberOfConditions = 2;
crealActions[473].conditions[0].field = 898 ;
crealActions[473].conditions[0].relationType = 4 ;
crealActions[473].conditions[0].value = 64975.000000 ;
crealActions[473].conditions[0].conditionFunction = &conditionFunction_473_0;
crealActions[473].conditions[1].field = 898 ;
crealActions[473].conditions[1].relationType = 5 ;
crealActions[473].conditions[1].value = 66775.000000 ;
crealActions[473].conditions[1].conditionFunction = &conditionFunction_473_1;
crealNodes[689].numberOfProperties = 1;
crealNodes[689].properties[0] = &crealProperties[910];
crealProperties[910] = 0.000000;
crealNodes[689].numberOfActions = 6;
crealNodes[689].actionsList[0] = &crealActions[460];
crealActions[460].alID = 460;
crealActions[460].numberOfActionItems = 1;
crealActions[460].actions[0].actionType = 2;
crealActions[460].actions[0].targetID = 910;
crealActions[460].actions[0].targetValue = 8.754000;
crealActions[460].actions[0].actionFunction = &actionFunction_460_0;
crealActions[460].numberOfConditions = 2;
crealActions[460].conditions[0].field = 898 ;
crealActions[460].conditions[0].relationType = 4 ;
crealActions[460].conditions[0].value = 21603.000000 ;
crealActions[460].conditions[0].conditionFunction = &conditionFunction_460_0;
crealActions[460].conditions[1].field = 898 ;
crealActions[460].conditions[1].relationType = 5 ;
crealActions[460].conditions[1].value = 42183.000000 ;
crealActions[460].conditions[1].conditionFunction = &conditionFunction_460_1;
crealNodes[689].actionsList[1] = &crealActions[457];
crealActions[457].alID = 457;
crealActions[457].numberOfActionItems = 1;
crealActions[457].actions[0].actionType = 1;
crealActions[457].actions[0].targetID = 910;
crealActions[457].actions[0].targetValue = 181248.000000;
crealActions[457].actions[0].actionFunction = &actionFunction_457_0;
crealActions[457].numberOfConditions = 1;
crealActions[457].conditions[0].field = 898 ;
crealActions[457].conditions[0].relationType = 1 ;
crealActions[457].conditions[0].value = 21602.000000 ;
crealActions[457].conditions[0].conditionFunction = &conditionFunction_457_0;
crealNodes[689].actionsList[2] = &crealActions[458];
crealActions[458].alID = 458;
crealActions[458].numberOfActionItems = 1;
crealActions[458].actions[0].actionType = 1;
crealActions[458].actions[0].targetID = 910;
crealActions[458].actions[0].targetValue = 181248.000000;
crealActions[458].actions[0].actionFunction = &actionFunction_458_0;
crealActions[458].numberOfConditions = 1;
crealActions[458].conditions[0].field = 898 ;
crealActions[458].conditions[0].relationType = 1 ;
crealActions[458].conditions[0].value = 43202.000000 ;
crealActions[458].conditions[0].conditionFunction = &conditionFunction_458_0;
crealNodes[689].actionsList[3] = &crealActions[462];
crealActions[462].alID = 462;
crealActions[462].numberOfActionItems = 1;
crealActions[462].actions[0].actionType = 2;
crealActions[462].actions[0].targetID = 910;
crealActions[462].actions[0].targetValue = 8.754000;
crealActions[462].actions[0].actionFunction = &actionFunction_462_0;
crealActions[462].numberOfConditions = 2;
crealActions[462].conditions[0].field = 898 ;
crealActions[462].conditions[0].relationType = 4 ;
crealActions[462].conditions[0].value = 43203.000000 ;
crealActions[462].conditions[0].conditionFunction = &conditionFunction_462_0;
crealActions[462].conditions[1].field = 898 ;
crealActions[462].conditions[1].relationType = 5 ;
crealActions[462].conditions[1].value = 63783.000000 ;
crealActions[462].conditions[1].conditionFunction = &conditionFunction_462_1;
crealNodes[689].actionsList[4] = &crealActions[459];
crealActions[459].alID = 459;
crealActions[459].numberOfActionItems = 1;
crealActions[459].actions[0].actionType = 1;
crealActions[459].actions[0].targetID = 910;
crealActions[459].actions[0].targetValue = 181248.000000;
crealActions[459].actions[0].actionFunction = &actionFunction_459_0;
crealActions[459].numberOfConditions = 1;
crealActions[459].conditions[0].field = 898 ;
crealActions[459].conditions[0].relationType = 1 ;
crealActions[459].conditions[0].value = 64802.000000 ;
crealActions[459].conditions[0].conditionFunction = &conditionFunction_459_0;
crealNodes[689].actionsList[5] = &crealActions[463];
crealActions[463].alID = 463;
crealActions[463].numberOfActionItems = 1;
crealActions[463].actions[0].actionType = 2;
crealActions[463].actions[0].targetID = 910;
crealActions[463].actions[0].targetValue = 8.754000;
crealActions[463].actions[0].actionFunction = &actionFunction_463_0;
crealActions[463].numberOfConditions = 2;
crealActions[463].conditions[0].field = 898 ;
crealActions[463].conditions[0].relationType = 4 ;
crealActions[463].conditions[0].value = 64803.000000 ;
crealActions[463].conditions[0].conditionFunction = &conditionFunction_463_0;
crealActions[463].conditions[1].field = 898 ;
crealActions[463].conditions[1].relationType = 5 ;
crealActions[463].conditions[1].value = 85383.000000 ;
crealActions[463].conditions[1].conditionFunction = &conditionFunction_463_1;
crealNodes[699].numberOfProperties = 1;
crealNodes[699].properties[0] = &crealProperties[918];
crealProperties[918] = 1.000000;
crealNodes[699].numberOfActions = 1;
crealNodes[699].actionsList[0] = &crealActions[490];
crealActions[490].alID = 490;
crealActions[490].numberOfActionItems = 1;
crealActions[490].actions[0].actionType = 1;
crealActions[490].actions[0].targetID = 918;
crealActions[490].actions[0].targetValue = 1.000000;
crealActions[490].actions[0].actionFunction = &actionFunction_490_0;
crealActions[490].numberOfConditions = 1;
crealActions[490].conditions[0].field = 918 ;
crealActions[490].conditions[0].relationType = 6 ;
crealActions[490].conditions[0].value = 490.000000 ;
crealActions[490].conditions[0].conditionFunction = &conditionFunction_490_0;
crealNodes[700].numberOfProperties = 1;
crealNodes[700].properties[0] = &crealProperties[919];
crealProperties[919] = 10.000000;
crealNodes[700].numberOfActions = 2;
crealNodes[700].actionsList[0] = &crealActions[491];
crealActions[491].alID = 491;
crealActions[491].numberOfActionItems = 1;
crealActions[491].actions[0].actionType = 2;
crealActions[491].actions[0].targetID = 919;
crealActions[491].actions[0].targetValue = 1.000000;
crealActions[491].actions[0].actionFunction = &actionFunction_491_0;
crealActions[491].numberOfConditions = 5;
crealActions[491].conditions[0].field = 898 ;
crealActions[491].conditions[0].relationType = 1 ;
crealActions[491].conditions[0].value = 491.000000 ;
crealActions[491].conditions[0].conditionFunction = &conditionFunction_491_0;
crealActions[491].conditions[1].field = 898 ;
crealActions[491].conditions[1].relationType = 1 ;
crealActions[491].conditions[1].value = 491.000000 ;
crealActions[491].conditions[1].conditionFunction = &conditionFunction_491_1;
crealActions[491].conditions[2].field = 898 ;
crealActions[491].conditions[2].relationType = 1 ;
crealActions[491].conditions[2].value = 491.000000 ;
crealActions[491].conditions[2].conditionFunction = &conditionFunction_491_2;
crealActions[491].conditions[3].field = 898 ;
crealActions[491].conditions[3].relationType = 1 ;
crealActions[491].conditions[3].value = 491.000000 ;
crealActions[491].conditions[3].conditionFunction = &conditionFunction_491_3;
crealActions[491].conditions[4].field = 898 ;
crealActions[491].conditions[4].relationType = 1 ;
crealActions[491].conditions[4].value = 491.000000 ;
crealActions[491].conditions[4].conditionFunction = &conditionFunction_491_4;
crealNodes[700].actionsList[1] = &crealActions[492];
crealActions[492].alID = 492;
crealActions[492].numberOfActionItems = 1;
crealActions[492].actions[0].actionType = 1;
crealActions[492].actions[0].targetID = 919;
crealActions[492].actions[0].targetValue = 1.000000;
crealActions[492].actions[0].actionFunction = &actionFunction_492_0;
crealActions[492].numberOfConditions = 5;
crealActions[492].conditions[0].field = 898 ;
crealActions[492].conditions[0].relationType = 1 ;
crealActions[492].conditions[0].value = 492.000000 ;
crealActions[492].conditions[0].conditionFunction = &conditionFunction_492_0;
crealActions[492].conditions[1].field = 898 ;
crealActions[492].conditions[1].relationType = 1 ;
crealActions[492].conditions[1].value = 492.000000 ;
crealActions[492].conditions[1].conditionFunction = &conditionFunction_492_1;
crealActions[492].conditions[2].field = 898 ;
crealActions[492].conditions[2].relationType = 1 ;
crealActions[492].conditions[2].value = 492.000000 ;
crealActions[492].conditions[2].conditionFunction = &conditionFunction_492_2;
crealActions[492].conditions[3].field = 898 ;
crealActions[492].conditions[3].relationType = 1 ;
crealActions[492].conditions[3].value = 492.000000 ;
crealActions[492].conditions[3].conditionFunction = &conditionFunction_492_3;
crealActions[492].conditions[4].field = 898 ;
crealActions[492].conditions[4].relationType = 1 ;
crealActions[492].conditions[4].value = 492.000000 ;
crealActions[492].conditions[4].conditionFunction = &conditionFunction_492_4;
crealNodes[701].numberOfProperties = 1;
crealNodes[701].properties[0] = &crealProperties[920];
crealProperties[920] = 65.000000;
crealNodes[701].numberOfActions = 5;
crealNodes[701].actionsList[0] = &crealActions[517];
crealActions[517].alID = 517;
crealActions[517].numberOfActionItems = 1;
crealActions[517].actions[0].actionType = 1;
crealActions[517].actions[0].targetID = 920;
crealActions[517].actions[0].targetValue = 0.000000;
crealActions[517].actions[0].actionFunction = &actionFunction_517_0;
crealActions[517].numberOfConditions = 1;
crealActions[517].conditions[0].field = 898 ;
crealActions[517].conditions[0].relationType = 3 ;
crealActions[517].conditions[0].value = 517.000000 ;
crealActions[517].conditions[0].conditionFunction = &conditionFunction_517_0;
crealNodes[701].actionsList[1] = &crealActions[520];
crealActions[520].alID = 520;
crealActions[520].numberOfActionItems = 1;
crealActions[520].actions[0].actionType = 1;
crealActions[520].actions[0].targetID = 920;
crealActions[520].actions[0].targetValue = 0.000023;
crealActions[520].actions[0].actionFunction = &actionFunction_520_0;
crealActions[520].numberOfConditions = 2;
crealActions[520].conditions[0].field = 898 ;
crealActions[520].conditions[0].relationType = 4 ;
crealActions[520].conditions[0].value = 520.000000 ;
crealActions[520].conditions[0].conditionFunction = &conditionFunction_520_0;
crealActions[520].conditions[1].field = 898 ;
crealActions[520].conditions[1].relationType = 3 ;
crealActions[520].conditions[1].value = 520.000000 ;
crealActions[520].conditions[1].conditionFunction = &conditionFunction_520_1;
crealNodes[701].actionsList[2] = &crealActions[518];
crealActions[518].alID = 518;
crealActions[518].numberOfActionItems = 1;
crealActions[518].actions[0].actionType = 1;
crealActions[518].actions[0].targetID = 920;
crealActions[518].actions[0].targetValue = 0.006918;
crealActions[518].actions[0].actionFunction = &actionFunction_518_0;
crealActions[518].numberOfConditions = 2;
crealActions[518].conditions[0].field = 898 ;
crealActions[518].conditions[0].relationType = 4 ;
crealActions[518].conditions[0].value = 518.000000 ;
crealActions[518].conditions[0].conditionFunction = &conditionFunction_518_0;
crealActions[518].conditions[1].field = 898 ;
crealActions[518].conditions[1].relationType = 3 ;
crealActions[518].conditions[1].value = 518.000000 ;
crealActions[518].conditions[1].conditionFunction = &conditionFunction_518_1;
crealNodes[701].actionsList[3] = &crealActions[521];
crealActions[521].alID = 521;
crealActions[521].numberOfActionItems = 1;
crealActions[521].actions[0].actionType = 2;
crealActions[521].actions[0].targetID = 920;
crealActions[521].actions[0].targetValue = 0.000950;
crealActions[521].actions[0].actionFunction = &actionFunction_521_0;
crealActions[521].numberOfConditions = 2;
crealActions[521].conditions[0].field = 898 ;
crealActions[521].conditions[0].relationType = 4 ;
crealActions[521].conditions[0].value = 521.000000 ;
crealActions[521].conditions[0].conditionFunction = &conditionFunction_521_0;
crealActions[521].conditions[1].field = 898 ;
crealActions[521].conditions[1].relationType = 3 ;
crealActions[521].conditions[1].value = 521.000000 ;
crealActions[521].conditions[1].conditionFunction = &conditionFunction_521_1;
crealNodes[701].actionsList[4] = &crealActions[519];
crealActions[519].alID = 519;
crealActions[519].numberOfActionItems = 1;
crealActions[519].actions[0].actionType = 1;
crealActions[519].actions[0].targetID = 920;
crealActions[519].actions[0].targetValue = 0.000049;
crealActions[519].actions[0].actionFunction = &actionFunction_519_0;
crealActions[519].numberOfConditions = 2;
crealActions[519].conditions[0].field = 898 ;
crealActions[519].conditions[0].relationType = 4 ;
crealActions[519].conditions[0].value = 519.000000 ;
crealActions[519].conditions[0].conditionFunction = &conditionFunction_519_0;
crealActions[519].conditions[1].field = 898 ;
crealActions[519].conditions[1].relationType = 3 ;
crealActions[519].conditions[1].value = 519.000000 ;
crealActions[519].conditions[1].conditionFunction = &conditionFunction_519_1;
crealNodes[702].numberOfActions = 4;
crealNodes[702].actionsList[0] = &crealActions[502];
crealActions[502].alID = 502;
crealActions[502].numberOfActionItems = 1;
crealActions[502].actions[0].actionType = 1;
crealActions[502].actions[0].targetID = 904;
crealActions[502].actions[0].targetValue = 0.001500;
crealActions[502].actions[0].actionFunction = &actionFunction_502_0;
crealActions[502].numberOfConditions = 1;
crealActions[502].conditions[0].field = 905 ;
crealActions[502].conditions[0].relationType = 3 ;
crealActions[502].conditions[0].value = 502.000000 ;
crealActions[502].conditions[0].conditionFunction = &conditionFunction_502_0;
crealNodes[702].actionsList[1] = &crealActions[499];
crealActions[499].alID = 499;
crealActions[499].numberOfActionItems = 1;
crealActions[499].actions[0].actionType = 1;
crealActions[499].actions[0].targetID = 903;
crealActions[499].actions[0].targetValue = 0.015000;
crealActions[499].actions[0].actionFunction = &actionFunction_499_0;
crealActions[499].numberOfConditions = 1;
crealActions[499].conditions[0].field = 905 ;
crealActions[499].conditions[0].relationType = 2 ;
crealActions[499].conditions[0].value = 499.000000 ;
crealActions[499].conditions[0].conditionFunction = &conditionFunction_499_0;
crealNodes[702].actionsList[2] = &crealActions[500];
crealActions[500].alID = 500;
crealActions[500].numberOfActionItems = 1;
crealActions[500].actions[0].actionType = 1;
crealActions[500].actions[0].targetID = 903;
crealActions[500].actions[0].targetValue = 0.001500;
crealActions[500].actions[0].actionFunction = &actionFunction_500_0;
crealActions[500].numberOfConditions = 1;
crealActions[500].conditions[0].field = 905 ;
crealActions[500].conditions[0].relationType = 3 ;
crealActions[500].conditions[0].value = 500.000000 ;
crealActions[500].conditions[0].conditionFunction = &conditionFunction_500_0;
crealNodes[702].actionsList[3] = &crealActions[501];
crealActions[501].alID = 501;
crealActions[501].numberOfActionItems = 1;
crealActions[501].actions[0].actionType = 1;
crealActions[501].actions[0].targetID = 904;
crealActions[501].actions[0].targetValue = 0.015000;
crealActions[501].actions[0].actionFunction = &actionFunction_501_0;
crealActions[501].numberOfConditions = 1;
crealActions[501].conditions[0].field = 905 ;
crealActions[501].conditions[0].relationType = 2 ;
crealActions[501].conditions[0].value = 501.000000 ;
crealActions[501].conditions[0].conditionFunction = &conditionFunction_501_0;
crealNodes[703].numberOfProperties = 1;
crealNodes[703].properties[0] = &crealProperties[921];
crealProperties[921] = 319.000000;
crealNodes[703].numberOfActions = 8;
crealNodes[703].actionsList[0] = &crealActions[503];
crealActions[503].alID = 503;
crealActions[503].numberOfActionItems = 1;
crealActions[503].actions[0].actionType = 2;
crealActions[503].actions[0].targetID = 921;
crealActions[503].actions[0].targetValue = 0.001667;
crealActions[503].actions[0].actionFunction = &actionFunction_503_0;
crealActions[503].numberOfConditions = 1;
crealActions[503].conditions[0].field = 898 ;
crealActions[503].conditions[0].relationType = 3 ;
crealActions[503].conditions[0].value = 503.000000 ;
crealActions[503].conditions[0].conditionFunction = &conditionFunction_503_0;
crealNodes[703].actionsList[1] = &crealActions[504];
crealActions[504].alID = 504;
crealActions[504].numberOfActionItems = 1;
crealActions[504].actions[0].actionType = 1;
crealActions[504].actions[0].targetID = 921;
crealActions[504].actions[0].targetValue = 0.016666;
crealActions[504].actions[0].actionFunction = &actionFunction_504_0;
crealActions[504].numberOfConditions = 2;
crealActions[504].conditions[0].field = 898 ;
crealActions[504].conditions[0].relationType = 4 ;
crealActions[504].conditions[0].value = 504.000000 ;
crealActions[504].conditions[0].conditionFunction = &conditionFunction_504_0;
crealActions[504].conditions[1].field = 898 ;
crealActions[504].conditions[1].relationType = 3 ;
crealActions[504].conditions[1].value = 504.000000 ;
crealActions[504].conditions[1].conditionFunction = &conditionFunction_504_1;
crealNodes[703].actionsList[2] = &crealActions[505];
crealActions[505].alID = 505;
crealActions[505].numberOfActionItems = 1;
crealActions[505].actions[0].actionType = 2;
crealActions[505].actions[0].targetID = 921;
crealActions[505].actions[0].targetValue = 0.008000;
crealActions[505].actions[0].actionFunction = &actionFunction_505_0;
crealActions[505].numberOfConditions = 2;
crealActions[505].conditions[0].field = 898 ;
crealActions[505].conditions[0].relationType = 4 ;
crealActions[505].conditions[0].value = 505.000000 ;
crealActions[505].conditions[0].conditionFunction = &conditionFunction_505_0;
crealActions[505].conditions[1].field = 898 ;
crealActions[505].conditions[1].relationType = 3 ;
crealActions[505].conditions[1].value = 505.000000 ;
crealActions[505].conditions[1].conditionFunction = &conditionFunction_505_1;
crealNodes[703].actionsList[3] = &crealActions[506];
crealActions[506].alID = 506;
crealActions[506].numberOfActionItems = 1;
crealActions[506].actions[0].actionType = 1;
crealActions[506].actions[0].targetID = 921;
crealActions[506].actions[0].targetValue = 0.017000;
crealActions[506].actions[0].actionFunction = &actionFunction_506_0;
crealActions[506].numberOfConditions = 2;
crealActions[506].conditions[0].field = 898 ;
crealActions[506].conditions[0].relationType = 4 ;
crealActions[506].conditions[0].value = 506.000000 ;
crealActions[506].conditions[0].conditionFunction = &conditionFunction_506_0;
crealActions[506].conditions[1].field = 898 ;
crealActions[506].conditions[1].relationType = 3 ;
crealActions[506].conditions[1].value = 506.000000 ;
crealActions[506].conditions[1].conditionFunction = &conditionFunction_506_1;
crealNodes[703].actionsList[4] = &crealActions[510];
crealActions[510].alID = 510;
crealActions[510].numberOfActionItems = 1;
crealActions[510].actions[0].actionType = 2;
crealActions[510].actions[0].targetID = 921;
crealActions[510].actions[0].targetValue = 0.007000;
crealActions[510].actions[0].actionFunction = &actionFunction_510_0;
crealActions[510].numberOfConditions = 2;
crealActions[510].conditions[0].field = 898 ;
crealActions[510].conditions[0].relationType = 4 ;
crealActions[510].conditions[0].value = 510.000000 ;
crealActions[510].conditions[0].conditionFunction = &conditionFunction_510_0;
crealActions[510].conditions[1].field = 898 ;
crealActions[510].conditions[1].relationType = 3 ;
crealActions[510].conditions[1].value = 510.000000 ;
crealActions[510].conditions[1].conditionFunction = &conditionFunction_510_1;
crealNodes[703].actionsList[5] = &crealActions[507];
crealActions[507].alID = 507;
crealActions[507].numberOfActionItems = 1;
crealActions[507].actions[0].actionType = 2;
crealActions[507].actions[0].targetID = 921;
crealActions[507].actions[0].targetValue = 0.007500;
crealActions[507].actions[0].actionFunction = &actionFunction_507_0;
crealActions[507].numberOfConditions = 2;
crealActions[507].conditions[0].field = 898 ;
crealActions[507].conditions[0].relationType = 4 ;
crealActions[507].conditions[0].value = 507.000000 ;
crealActions[507].conditions[0].conditionFunction = &conditionFunction_507_0;
crealActions[507].conditions[1].field = 898 ;
crealActions[507].conditions[1].relationType = 3 ;
crealActions[507].conditions[1].value = 507.000000 ;
crealActions[507].conditions[1].conditionFunction = &conditionFunction_507_1;
crealNodes[703].actionsList[6] = &crealActions[508];
crealActions[508].alID = 508;
crealActions[508].numberOfActionItems = 1;
crealActions[508].actions[0].actionType = 1;
crealActions[508].actions[0].targetID = 921;
crealActions[508].actions[0].targetValue = 0.016700;
crealActions[508].actions[0].actionFunction = &actionFunction_508_0;
crealActions[508].numberOfConditions = 2;
crealActions[508].conditions[0].field = 898 ;
crealActions[508].conditions[0].relationType = 4 ;
crealActions[508].conditions[0].value = 508.000000 ;
crealActions[508].conditions[0].conditionFunction = &conditionFunction_508_0;
crealActions[508].conditions[1].field = 898 ;
crealActions[508].conditions[1].relationType = 3 ;
crealActions[508].conditions[1].value = 508.000000 ;
crealActions[508].conditions[1].conditionFunction = &conditionFunction_508_1;
crealNodes[703].actionsList[7] = &crealActions[509];
crealActions[509].alID = 509;
crealActions[509].numberOfActionItems = 1;
crealActions[509].actions[0].actionType = 1;
crealActions[509].actions[0].targetID = 921;
crealActions[509].actions[0].targetValue = 0.000000;
crealActions[509].actions[0].actionFunction = &actionFunction_509_0;
crealActions[509].numberOfConditions = 2;
crealActions[509].conditions[0].field = 898 ;
crealActions[509].conditions[0].relationType = 4 ;
crealActions[509].conditions[0].value = 509.000000 ;
crealActions[509].conditions[0].conditionFunction = &conditionFunction_509_0;
crealActions[509].conditions[1].field = 898 ;
crealActions[509].conditions[1].relationType = 3 ;
crealActions[509].conditions[1].value = 509.000000 ;
crealActions[509].conditions[1].conditionFunction = &conditionFunction_509_1;
crealNodes[705].numberOfProperties = 1;
crealNodes[705].properties[0] = &crealProperties[924];
crealProperties[924] = 102.000000;
crealNodes[705].numberOfActions = 5;
crealNodes[705].actionsList[0] = &crealActions[531];
crealActions[531].alID = 531;
crealActions[531].numberOfActionItems = 1;
crealActions[531].actions[0].actionType = 1;
crealActions[531].actions[0].targetID = 924;
crealActions[531].actions[0].targetValue = 0.000049;
crealActions[531].actions[0].actionFunction = &actionFunction_531_0;
crealActions[531].numberOfConditions = 2;
crealActions[531].conditions[0].field = 898 ;
crealActions[531].conditions[0].relationType = 4 ;
crealActions[531].conditions[0].value = 531.000000 ;
crealActions[531].conditions[0].conditionFunction = &conditionFunction_531_0;
crealActions[531].conditions[1].field = 898 ;
crealActions[531].conditions[1].relationType = 3 ;
crealActions[531].conditions[1].value = 531.000000 ;
crealActions[531].conditions[1].conditionFunction = &conditionFunction_531_1;
crealNodes[705].actionsList[1] = &crealActions[529];
crealActions[529].alID = 529;
crealActions[529].numberOfActionItems = 1;
crealActions[529].actions[0].actionType = 1;
crealActions[529].actions[0].targetID = 924;
crealActions[529].actions[0].targetValue = 0.000000;
crealActions[529].actions[0].actionFunction = &actionFunction_529_0;
crealActions[529].numberOfConditions = 1;
crealActions[529].conditions[0].field = 898 ;
crealActions[529].conditions[0].relationType = 3 ;
crealActions[529].conditions[0].value = 529.000000 ;
crealActions[529].conditions[0].conditionFunction = &conditionFunction_529_0;
crealNodes[705].actionsList[2] = &crealActions[530];
crealActions[530].alID = 530;
crealActions[530].numberOfActionItems = 1;
crealActions[530].actions[0].actionType = 1;
crealActions[530].actions[0].targetID = 924;
crealActions[530].actions[0].targetValue = 0.006918;
crealActions[530].actions[0].actionFunction = &actionFunction_530_0;
crealActions[530].numberOfConditions = 2;
crealActions[530].conditions[0].field = 898 ;
crealActions[530].conditions[0].relationType = 4 ;
crealActions[530].conditions[0].value = 530.000000 ;
crealActions[530].conditions[0].conditionFunction = &conditionFunction_530_0;
crealActions[530].conditions[1].field = 898 ;
crealActions[530].conditions[1].relationType = 3 ;
crealActions[530].conditions[1].value = 530.000000 ;
crealActions[530].conditions[1].conditionFunction = &conditionFunction_530_1;
crealNodes[705].actionsList[3] = &crealActions[532];
crealActions[532].alID = 532;
crealActions[532].numberOfActionItems = 1;
crealActions[532].actions[0].actionType = 1;
crealActions[532].actions[0].targetID = 924;
crealActions[532].actions[0].targetValue = 0.000023;
crealActions[532].actions[0].actionFunction = &actionFunction_532_0;
crealActions[532].numberOfConditions = 2;
crealActions[532].conditions[0].field = 898 ;
crealActions[532].conditions[0].relationType = 4 ;
crealActions[532].conditions[0].value = 532.000000 ;
crealActions[532].conditions[0].conditionFunction = &conditionFunction_532_0;
crealActions[532].conditions[1].field = 898 ;
crealActions[532].conditions[1].relationType = 3 ;
crealActions[532].conditions[1].value = 532.000000 ;
crealActions[532].conditions[1].conditionFunction = &conditionFunction_532_1;
crealNodes[705].actionsList[4] = &crealActions[533];
crealActions[533].alID = 533;
crealActions[533].numberOfActionItems = 1;
crealActions[533].actions[0].actionType = 2;
crealActions[533].actions[0].targetID = 924;
crealActions[533].actions[0].targetValue = 0.000900;
crealActions[533].actions[0].actionFunction = &actionFunction_533_0;
crealActions[533].numberOfConditions = 2;
crealActions[533].conditions[0].field = 898 ;
crealActions[533].conditions[0].relationType = 4 ;
crealActions[533].conditions[0].value = 533.000000 ;
crealActions[533].conditions[0].conditionFunction = &conditionFunction_533_0;
crealActions[533].conditions[1].field = 898 ;
crealActions[533].conditions[1].relationType = 3 ;
crealActions[533].conditions[1].value = 533.000000 ;
crealActions[533].conditions[1].conditionFunction = &conditionFunction_533_1;
crealNodes[706].numberOfActions = 1;
crealNodes[706].actionsList[0] = &crealActions[534];
crealActions[534].alID = 534;
crealActions[534].numberOfActionItems = 1;
crealActions[534].actions[0].actionType = 1;
crealActions[534].actions[0].targetID = 925;
crealActions[534].actions[0].targetValue = 1.000000;
crealActions[534].actions[0].actionFunction = &actionFunction_534_0;
crealActions[534].numberOfConditions = 0;
crealNodes[707].numberOfProperties = 1;
crealNodes[707].properties[0] = &crealProperties[925];
crealProperties[925] = 100.000000;
}
