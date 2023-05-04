#!/bin/bash

echo "Enter the directory path:"
read directory
count=$(find "$directory" -mindepth 1 -type d | wc -l)
echo "The number of subdirectories in $directory is: $count"
