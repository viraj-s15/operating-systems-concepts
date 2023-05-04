#!/bin/bash

if [ $# -lt 1 ]
then 
  echo "No arguments were provided hence no operation can be carried out"
  exit 1
else
  echo "The two numbers given are $1 and $2"
  sum=$(($1 + $2))
  echo "The sum of the given two numbers is $sum"
fi
