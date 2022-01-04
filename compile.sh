#!/usr/bin/env sh 
FILE="simttylogin"

CPPFLAGS=""

#POSITIONAL_ARGS=()

while [ $# -gt 0 ]; do
  case $1 in
    -c|--enable-color)
      CPPFLAGS=$CPPFLAGS-DCOLOR
      shift 
      ;;
    -*|--*)
      printf "%s:Unknown argument:\"%s\"\n" $0 $1 || echo -e "$0: Uknown argument:\"$1\""
      exit 1
      ;;
    #*)
      #POSITIONAL_ARGS+=("$1") 
      #shift 
     # ;; I won't plan to  use this (because this requires bash)
  esac
done
cc  `pkg-config --cflags --libs pam` -O2 -std=c99 -lpam_misc $CPPFLAGS -o $FILE $FILE.c
