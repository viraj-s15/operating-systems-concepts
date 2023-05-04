#!/bin/bash

if [ $# -ne 1 ]
then
    echo "The number of arguments is incorrect, please only enter the name of the file"
    exit
fi

if [ -f "$1" ] 
then 
    echo "The file does exist"
else
    echo "The file does not exist"
fi
