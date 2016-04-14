#!/bin/bash

gcc mainProgramForShu.c -o creal_ng -lm -g 
gcc mainProgramForShu.c -o creal_mp -lm -g -fopenmp 
