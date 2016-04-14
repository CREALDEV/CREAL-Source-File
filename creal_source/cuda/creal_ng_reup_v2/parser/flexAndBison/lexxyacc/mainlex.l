%{
#define YYSTYPE double
#include <stdio.h>
#include <string.h>
#include "mainyacc.tab.h"
#include <math.h>
extern double yylval;
%}
D [0-9.]
%%
[ \t] { ; }
log return LOG;
pi return PIVAL;
sin return SIN;
cos return COS;
tan return TAN;
and return AND;
not return NOT;
xor return XOR;
or return OR;
reg return REGA;
ans return ANS;
fix return FIX;
sci return SCI;
eng return ENG;
const return CONST;
bintodec return BINTODEC;
dectobin return DECTOBIN;
{D}+ { sscanf( yytext, "%lf", &yylval ); return NUMBER ; }
[a-zA-Z_]+ return IDENT;
"[" return OPENREG;
"]" return CLOSEREG;
"<<" return LEFTSHIFT;
">>" return RIGHTSHIFT;
"++" return INC;
"--" return DEC;
"+" return PLUS;
"-" return MINUS;
"~" return UNARYMINUS;
"/" return DIV;
"*" return MUL;
"^" return POW;
"!" return FACT;
"(" return OPENBRACKET;
")" return CLOSEBRACKET;
"%" return MOD;
"^^" return XOR;
"!!" return NOT;
"=" return ASSIGN;
"&&" return LAND;
"||" return OR;
"|" return IOR;
"&" return AND;
"~~" return COMPLEMENT;
"\n" return EOLN;
