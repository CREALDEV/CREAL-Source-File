#!/bin/bash

echo "Compile bison parser!"


bison mainyacc.y

cc mainyacc.tab.c -lm -o rpcalc

