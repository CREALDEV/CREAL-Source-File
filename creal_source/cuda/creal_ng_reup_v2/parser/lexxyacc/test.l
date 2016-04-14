%{
#define YYSTYPE char *
#include <stdio.h>
#include <string.h>

%}
%%



[0-9]		{printf("%s",yytext);	return INTEGER;} 
[0-9].[0-9] {printf("%s",yytext);	return DOUBLE;} 
"^"			{return POW;}
"pid:"				{return PID;}
","         		{ return COMMA;      }
"("                  { return LPAREN;     }
")"                  { return RPAREN;     }
"["					{ return LBRACKET;     }
"]"					{ return RBRACKET;     }
[ \t\n\r]
%%
