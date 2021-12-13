#!/usr/bin/env sh 
FILE="simttylogin"

cc  `pkg-config --cflags --libs pam` -O2 -std=c99 -lpam_misc -o $FILE $FILE.c
