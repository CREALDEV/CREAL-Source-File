/* A Bison parser, made by GNU Bison 2.4.3.  */

/* Skeleton interface for Bison's Yacc-like parsers in C
   
      Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004, 2005, 2006,
   2009, 2010 Free Software Foundation, Inc.
   
   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   
   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.
   
   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     NUMBER = 258,
     SPACE = 259,
     MOD = 260,
     RIGHTSHIFT = 261,
     LEFTSHIFT = 262,
     SEMICOLON = 263,
     SIN = 264,
     EOLN = 265,
     PIVAL = 266,
     BINTODEC = 267,
     DECTOBIN = 268,
     IDENT = 269,
     PLUS = 270,
     MINUS = 271,
     DIV = 272,
     MUL = 273,
     POW = 274,
     OPENBRACKET = 275,
     CLOSEBRACKET = 276,
     UNARYMINUS = 277,
     COS = 278,
     TAN = 279,
     ASIN = 280,
     ACOS = 281,
     ATAN = 282,
     FACT = 283,
     INC = 284,
     DEC = 285,
     LAND = 286,
     OR = 287,
     COMPLEMENT = 288,
     NOT = 289,
     XOR = 290,
     ASSIGN = 291,
     IOR = 292,
     AND = 293,
     OPENREG = 294,
     CLOSEREG = 295,
     REGA = 296,
     ANS = 297,
     FIX = 298,
     SCI = 299,
     ENG = 300,
     CONST = 301,
     LOG = 302
   };
#endif



#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
typedef int YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
#endif

extern YYSTYPE yylval;


