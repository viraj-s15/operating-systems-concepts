#!/bin/bash

if [ $# -ne 1 ]
then 
  echo "The number of arguments provided is incorrect"
  exit
fi

input_file=$1
output_file="${input_file}.txt"

sort -u "$input_file" > "$output_file"
mv "$output_file" "$input_file"
# In case the extension of the file wants to be changed this line is necessary
echo "The duplicate lines have been removed"
