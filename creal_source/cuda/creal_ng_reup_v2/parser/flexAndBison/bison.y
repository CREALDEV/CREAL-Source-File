%{

#define YYSTYPE char * /* Use this for string data */

#define NAME "CREAL Language to C Parser DAEMON\n Created by Randy White for C.R.E.A.\n" /* Just putting a label on this thing */
#define USAGE "Usage : ctcpd [input file] [output file] \n \
This application takes one arguments, an input and output pipe (fifo) file for IPC communication\n \
It is preferable to use named pipes with this program, or files used in an location for shared memory (i.e. tmpfs)\n" /* Usage of this application */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "flex.h"


#define MAXSIZE 2048
#define MAX_PIPE_SIZE 2048
#define TEMP "crealProperties" //REPLACE EVENTUALLY
static char buffer0[MAXSIZE], buffer1[MAXSIZE], buffer2[MAXSIZE], buffer3[MAXSIZE], 
outputPipePath[256], inputPipePath[256], errorPipePath[256]; /* These are the buffers */

int loopConditionVar, errorBit;
uint parenCount, bracketCount, bufferCounter; /* Used to count parenthesis */
extern int yydebug;
extern void yyrestart( FILE *new_file );
FILE *inputPipeFile, *outputPipeFile, *errorPipeFile; /* Now we are getting things cooking */
extern FILE *yyin; //getting the input filehandle
extern FILE *yyout; //getting the output filehandle 
void abortParser(void);
pid_t pid, sid, cpid; // this is the pid for our daemon process
void startDaemonMode(void); //starts the daemon
int writeToPipe(const char *path, const char *string);
int readFromPipe(const char *path, char buffer[]);
char **stringCubby; //huge!

%}

%token NUMBER SPACE MOD SIN EOLN PID LBRACKET RBRACKET CREAL_END 
%token LPAREN RPAREN CREAL_BEGIN UNKNOWN CREAL_PRINT COPY POWERFUNC COMMA
%token COS TAN ASIN ACOS ATAN TANH SINH RANDFUNC EXP COSH POW
%left PLUS MINUS
%left MUL DIV

/*
%destructor { free ($$); } NUMBER SPACE MOD SIN EOLN PID LBRACKET RBRACKET CREAL_END 
%destructor { free ($$); } LPAREN RPAREN CREAL_BEGIN UNKNOWN CREAL_PRINT COPY POWERFUNC COMMA
%destructor { free ($$); } COS TAN ASIN ACOS ATAN TANH SINH RANDFUNC EXP COSH POW
%destructor { free ($$); } MUL DIV PLUS MINUS
*/

%%




cpy: 
expr COPY {
		
			if (parenCount % 2 != 0)
			{
				puts("Parenthesis are not equal!");
				/* Lets make sure there are the correct amount of parenthesis */
			}
	
	
			else if (bracketCount % 2 != 0)
			{
				puts("Brackets are not equal!");
				/* Lets make sure there are the correct amount of brackets */
			}
		else
		{
			strcpy(buffer0,$1);
			writeToPipe(outputPipePath,buffer0);
			YYACCEPT; /*This probably needs to be taken out of here */
			
		}
}

| error { 
	
	
	printf("%d\n",YYRECOVERING());
	errorBit = 1;
	yyrestart(yyin);
	YYABORT;

	
	}

	
| CREAL_END COPY { 
	
	loopConditionVar = 0;
	 }
;







expr : 
	power

	/* These are just general expressions */
	
| expr PLUS power {
	 memset(buffer1,0,sizeof(char) * MAXSIZE);
	 memset(buffer2,0,sizeof(char) * MAXSIZE);
	 strcpy(buffer1,$1);
	 strcpy(buffer2,$3);
	 puts(buffer1);
	 puts(buffer2);
	 sprintf($$,"%s + %s", buffer1, buffer2); 

	 }
 |expr MINUS power {
	 memset(buffer1,0,sizeof(char) * MAXSIZE);
	 memset(buffer2,0,sizeof(char) * MAXSIZE);
	 strcpy(buffer1,$1);
	 strcpy(buffer2,$3);
	 puts(buffer1);
	 puts(buffer2);
	 sprintf($$,"%s - %s", buffer1, buffer2);
	 
	  }
 |expr MUL power {
	 memset(buffer1,0,sizeof(char) * MAXSIZE);
	 memset(buffer2,0,sizeof(char) * MAXSIZE);
	 strcpy(buffer1,$1);
	 strcpy(buffer2,$3);
	 puts(buffer1);
	 puts(buffer2);
	 sprintf($$,"%s * %s", buffer1, buffer2);
	 
	  }
 |expr DIV power {
	 memset(buffer1,0,sizeof(char) * MAXSIZE);
	 memset(buffer2,0,sizeof(char) * MAXSIZE);
	 strcpy(buffer1,$1);
	 strcpy(buffer2,$3);
	 puts(buffer1);
	 puts(buffer2);
	 sprintf($$,"%s / %s", buffer1, buffer2);
	 
	  }
 |expr MOD power {
	 memset(buffer1,0,MAXSIZE);
	 memset(buffer2,0,MAXSIZE);
	 strcpy(buffer1,$1);
	 strcpy(buffer2,$3);
	 puts(buffer1);
	 puts(buffer2);
	 sprintf($$,"%s %c %s", buffer1,'%', buffer2);
	 
	  }	
;


power : 
		num

|power POW num {memset(buffer1,0,sizeof(char) * MAXSIZE);
					memset(buffer2,0,sizeof(char) * MAXSIZE);
					strcpy(buffer1,$1);
					strcpy(buffer2,$3);
	 sprintf($$,"pow(%s,%s)", buffer1, buffer2);
//also add the new modulous rules to this parser
	 }
;




num : 
NUMBER { 
	memset(buffer1,0,sizeof(char) * MAXSIZE);
	strcpy(buffer1,$1);
	puts(buffer1);
	sprintf($$,"%s", buffer1);
	 
	 }
	 
|LPAREN expr RPAREN {
	memset(buffer1,0,sizeof(char) * MAXSIZE);
	strcpy(buffer1,$2);
	puts(buffer1);
	sprintf($$,"(%s)", buffer1);
	 }
	 
|MINUS num {
	memset(buffer1,0,sizeof(char) * MAXSIZE);
	strcpy(buffer1,$2);
	puts(buffer1);
	sprintf($$,"-%s", buffer1);
	 }
	 
|PLUS num {
	memset(buffer1,0,sizeof(char) * MAXSIZE);
	strcpy(buffer1,$2);
	puts(buffer1);
	sprintf($$,"+%s", buffer1);
	 }
| crealproperty
| functions
;


crealproperty : 
LBRACKET NUMBER RBRACKET {
					memset(buffer1,0,sizeof(char) * MAXSIZE);
					memset(buffer2,0,sizeof(char) * MAXSIZE);
					strcpy(buffer1,$2);
					puts(buffer1);
	
					sprintf($$,"%s[%s]", TEMP,  buffer1);
	
}

|LBRACKET PID NUMBER RBRACKET {
					memset(buffer1,0,sizeof(char) * MAXSIZE);
					memset(buffer2,0,sizeof(char) * MAXSIZE);
					strcpy(buffer1,$3);
					puts(buffer1);
	
					sprintf($$,"%s[%s]", TEMP,  buffer1);
	
}
;


functions :
SIN LPAREN expr RPAREN {
					memset(buffer1,0,sizeof(char) * MAXSIZE);
	
					strcpy(buffer1,$3);
					puts(buffer1);
	
					sprintf($$,"sin(%s)", buffer1);


}

|SINH LPAREN expr RPAREN {
					memset(buffer1,0,sizeof(char) * MAXSIZE);
	
					strcpy(buffer1,$3);
					puts(buffer1);
	
					sprintf($$,"sinh(%s)", buffer1);


}

|COS LPAREN expr RPAREN {
					memset(buffer1,0,sizeof(char) * MAXSIZE);
	
					strcpy(buffer1,$3);
					puts(buffer1);
	
					sprintf($$,"cos(%s)", buffer1);


}

|COSH LPAREN expr RPAREN {
					memset(buffer1,0,sizeof(char) * MAXSIZE);
	
					strcpy(buffer1,$3);
					puts(buffer1);
	
					sprintf($$,"cosh(%s)", buffer1);


}

|TAN LPAREN expr RPAREN {
					memset(buffer1,0,sizeof(char) * MAXSIZE);
	
					strcpy(buffer1,$3);
					puts(buffer1);
	
					sprintf($$,"tan(%s)", buffer1);


}

|TANH LPAREN expr RPAREN {
					memset(buffer1,0,sizeof(char) * MAXSIZE);
	
					strcpy(buffer1,$3);
					puts(buffer1);
	
					sprintf($$,"tanh(%s)", buffer1);


}

|EXP LPAREN expr RPAREN {
					memset(buffer1,0,sizeof(char) * MAXSIZE);

					strcpy(buffer1,$3);
					puts(buffer1);

					sprintf($$,"exp(%s)", buffer1);


}

|RANDFUNC LPAREN expr RPAREN {
					memset(buffer1,0,sizeof(char) * MAXSIZE);



					puts(buffer1);
					sprintf($$,"rand()");


}

|EXP LPAREN expr COMMA expr RPAREN {
					memset(buffer1,0,sizeof(char) * MAXSIZE);
					memset(buffer2,0,sizeof(char) * MAXSIZE);
					strcpy(buffer1,$3);
					strcpy(buffer2,$5);
					puts(buffer1);
					puts(buffer2);
					sprintf($$,"exp((%s + %s))", buffer1, buffer2);


}

|RANDFUNC LPAREN expr COMMA expr RPAREN {
					memset(buffer1,0,sizeof(char) * MAXSIZE);
					memset(buffer2,0,sizeof(char) * MAXSIZE);

					
					puts(buffer1);
					sprintf($$,"rand()");


}

|POWERFUNC LPAREN expr COMMA expr RPAREN {
					memset(buffer1,0,sizeof(char) * MAXSIZE);
					memset(buffer2,0,sizeof(char) * MAXSIZE);
					strcpy(buffer1,$3);
					strcpy(buffer2,$5);
					puts(buffer1);
					puts(buffer2);
					
					sprintf($$,"pow(%s,%s)", buffer1, buffer2);


}
;

	

%%



int main(int argc, char *argv[]) {
		
		static  struct sockaddr_un mainSocketDataStructure; // this is used as the main data structure for the sockets 
			puts(NAME); /* Show the usage!! */
			
					if (argc <= 1 || argv[1] <= 0 || argv[2] <=0)
					{
						

						fprintf(stderr,"%s : \n\n %s",argv[0],USAGE);
						exit(EXIT_FAILURE);
						
						
					}
		/*  Assigning memory for the data structure */			
		/*  Do a memory pool for this application */			
		
		stringCubby = malloc(MAXSIZE * sizeof(char *));
		
		if ( stringCubby == NULL) {perror("We ran out of memory!"); exit(EXIT_FAILURE);}
		memset(stringCubby,0,sizeof(char*) * MAXSIZE); //set everything to zero!!
		int i = 0;
		
		for(i = 0; i < MAXSIZE; i++)
		{
			
			stringCubby[i] = (char *) malloc(MAXSIZE * sizeof(char));
			if ( stringCubby[i] == NULL) {perror("We ran out of memory!"); exit(EXIT_FAILURE);}
			memset(stringCubby[i],0,sizeof(char) * MAXSIZE); //set everything to zero!!
			
		}
		
		
				
		
		
		

		//~ startDaemonMode(); //starts the daemon
		daemon(1, 0); //this right here is used instead of my shitty function


		loopConditionVar = 1;		
		inputPipeFile = outputPipeFile = NULL; //set everything to NULL
		bufferCounter = bracketCount = parenCount = 0; //setting this shit to zero
		

		

		
		strcpy(outputPipePath,argv[2]);
				
		strcpy(inputPipePath,argv[1]);
		
		YY_BUFFER_STATE stringState, bState;
		

		/* All is good, start this program as a daemon */
			
		while(loopConditionVar == 1) //while this is true, always run the daemon
		{
		
		readFromPipe(inputPipePath,buffer3); 
		stringState = yy_scan_string(buffer3); //trying out parsing a string
		yy_switch_to_buffer(stringState);
		yyparse();
		yylex_destroy();
					
				if (errorBit >= 1)
				{

						writeToPipe(outputPipePath,buffer0);
						errorBit = 0;
				}
				

				bufferCounter = bracketCount = parenCount = 0; //setting this shit to zero
						
		}	
	
	
	
		/* Freeing the memory right here*/ 
		
		for(i = 0; i < MAXSIZE; i++)
		{
			free(stringCubby[i]);
			
		}
		
		free(stringCubby);

		exit(EXIT_SUCCESS);



}


/*
void startDaemonMode(void) //starts the daemon
{
					//* Daemon stuff below
					pid = fork(); //fork the proceess to a child process
					
					if(pid < 0)
					{
						printf("ERROR!\n");
						perror("Could not get a PID for child process"); //new way to handle errors
						exit(EXIT_FAILURE); // exit, things have failed
					}
					
					if(pid > 0)
					{
						//Things have succeeded
						exit(EXIT_SUCCESS); // exit, things have failed
					}
					
					umask(0); //change the file mask
					
					sid = setsid(); //get a set id for child process
						
						
					if(sid < 0)
					{
						puts("ERROR!\n");
						perror("Could not get a SID for child process"); //new way to handle errors
						exit(EXIT_FAILURE); // exit, things have failed
					}
					
					//* Change the current working directory 
					if ((chdir(".")) < 0) {
					//* Log any failure here 
					

				
					}
				
				
					//closes the standard display stuff
					//* Close out the standard file descriptors 
					close(STDIN_FILENO);
					close(STDOUT_FILENO); //standard output
					close(STDERR_FILENO);
				
				
				
}

*/


int yyerror(char *s)
    {
			/*  This right here is used to tell if there is an error with the parser */			
		          
          	printf("ERROR : %s", s); //prints out a syntax error to the filehandle
			
    }




int writeToPipe(const char *path, const char *string)
{
	/* this function writes to a pipe */
		FILE *fp = NULL;
		
	 fp = fopen(path,"w");
	 
	 if (fp == NULL) 
	 {
		 
			return -1;
			
	 }
	 
	 fputs(string,fp);
	 fclose(fp);
	 return 1;
}

int readFromPipe(const char *path, char buffer[])
{
	/*  this function reads from the pipe */			
		
		FILE *fp = NULL;
		
	 fp = fopen(path,"r");
	 
	 if (fp == NULL) 
	 {
		 
			return -1;
			
	 }
	 
	 while(fgets(buffer,MAX_PIPE_SIZE,fp) != NULL) {

		}
	 
	 fclose(fp);
	 return 1;
	 
}

