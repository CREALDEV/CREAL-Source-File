#!/bin/bash

#compile script

echo "Compiling Bison and Flex"
#rm *.c *.h ctcpd
bison -d bison.y
flex --header=flex.h flex.l

gcc lex.yy.c bison.tab.c -o ctcpd -O2
