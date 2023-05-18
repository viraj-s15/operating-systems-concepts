#!/bin/bash

if [ $# -ne 3 ]; then
  echo "Sufficient arguments have not been provided, required arguments = 3"
  exit 1
fi

largest=$1
if [ $2 -gt $largest ]; then
  largest=$2
fi
if [ $3 -gt $largest ]; then
  largest=$3
fi

echo "$largest is the largest number."

exit 0
