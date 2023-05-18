#!/bin/bash

if [ $# -ne 1 ]
then 
  echo "The number of arguments provided is incorrect"
  exit
fi

if [ -d "$1" ]; then
  find "$1" -mindepth 1 -type d -empty -print > empty_subfolders.txt -delete
  echo "The empty subfolders in $1 have been noted and saved to empty_subfolders.txt"
  echo "The empty directories have all been removed all well"
else
  echo "Error: $1 is not a valid directory"
fi
