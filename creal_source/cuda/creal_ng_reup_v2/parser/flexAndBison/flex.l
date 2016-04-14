%{
#define YYSTYPE char * /* Use this for string data */
#include <stdio.h>
#include <string.h>
#include "bison.tab.h"

#define MAXSIZE 2048
extern YYSTYPE yylval;
extern int loopConditionVar;

extern uint parenCount, bracketCount, bufferCounter; 
//~ static char stringCubby[1024][2048]; //huge!
extern char **stringCubby; //huge!

%}


%%


[0-9]+	{	
	strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
	//~ yylval = strdup(yytext); 
		//~ addElementToList(trashList,yylval);
		
		
		return NUMBER;
		/* Regular integers */
	} 
	
\.[0-9]+	{	
	//~ yylval = strdup(yytext); 
	strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
		

		return NUMBER;
		/*  Decimals  */
	} 

[0-9]+\.[0-9]+ {	
	//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		//~ strcat(buffer0,yytext);
		
		
		return NUMBER;
		/* Decimals numbers  */
	} 

"pid:"	{
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return PID;
	/* the PID */
	}
	
	
	
"pow"	{
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return POWERFUNC;
	/* pow function in C */
	}
	
"sin"	{
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return SIN;
	/* sin function in c */
	}
	
"cos"	{
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return COS;
	/* cos function in c  */
	}
	
"tan"	{
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
	return TAN;
	/* tan function in c */
	}
	
"tanh"	{
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return TANH;
	/* tanh function in c */
	}
	
	
"sinh"	{
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
	return SINH;
	/* sinh function in c */
	}

"cosh"	{
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return COSH;
	/* cosh function in c */
	}
	
	
	
"rand"	{
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return RANDFUNC;
	/* random function in c  */
	}
	
	
"exp"	{
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return EXP;
	/* exp function in c */
	}
	




	
"["		{
	
	bracketCount++;
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return LBRACKET;
	/*  left bracket */
	}
	
"]"		{
	
	bracketCount++;
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return RBRACKET;
	/* right bracket */
	}
	
"("		{
	
	parenCount++;
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return LPAREN;
	/* left parenthesis */
	}
	
")"		{
	
	parenCount++;
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return RPAREN;
	/* right parenthesis */
	}

"+" {
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return PLUS;
	/* plus */
	}
	
"-" {
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return MINUS;
	/* minus */
	}
	
"/" {
			//~ yylval = strdup(yytext); 
			strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
			
	return DIV;
	/* divide */
	}
	
"*" {
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return MUL;
	/* multiply */
	}
	
"^" {
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return POW;
	/* Power */
	}
	
	
"%" {
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return MOD;
	/* modulous */
	}
	
"," {
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return COMMA;
	/*  */
	}






	
	
"E" {
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
	return CREAL_END;
	/* deprecated */
	}
	
	
"B" {
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
	return CREAL_BEGIN;
	/* deprecated */
	}
	
	
"P" {
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
	
	/* this prints stuff in the buffers */
	}
	
"CLS" {
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
	
	/* clears the buffer  */
	}
	
"Q" {
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
		
	return CREAL_END;
	/* quits */
	}
	
"C" {
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
	return COPY;
	/* copy/end statement */
	}
	
";" {
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
		
	return COPY;
	/* copy/end statement */
	}

"CH" {
	
		//~ yylval = strdup(yytext); 
		strcpy(stringCubby[bufferCounter],yytext);
	yylval = stringCubby[bufferCounter];
		bufferCounter++;
	if (parenCount % 2 != 0)
	{
		puts("Parenthesis are not equal!");
		/*  */
	}
	
	
	if (bracketCount % 2 != 0)
	{
		puts("Brackets are not equal!");
		/*  */
	}
	
	/* deprecated */
	
}
	

[\t\n\r ]+ {
  
				/* do nothing 
				 * These are white space characters
				 * 
				 * */
  /*  */
  
}




.   { 		
	
	printf("Unknown character :: %c\n",yytext[0]);
		/* every other character */
    
    }
%%

int yywrap(void) {
	
	/* Just return a 1 for this function */
	return 1;
	/* this is just the wrap function */
}



