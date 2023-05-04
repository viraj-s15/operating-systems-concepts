#!/bin/bash

if [ $# -ne 3 ] 
then 
  echo "The number iof argument provided is incorrect,please provide then in the format gievn below"
  echo "<number 1><number 2><sign>"
  echo "for the sign -> 1 = addition, 2 = substraction, 3 = multiplication, 4 = division"
fi

case $3 in 
  1) 
    result=$(($1 + $2))
    echo "The sum of the two numbers is $result"
    ;;
  2) 
    result=$(($1 - $2))
    echo "The difference of the two numbers is $result"
    ;;
  3) 
    result=$(($1 * $2))
    echo "The product of the two numbers is $result"
    ;;
  4) 
    result=$(($1 / $2))
    echo "The quotient when dividing the two numbers is $result"
    ;;
  *)
    echo "Valid arguments have not been provided"
    ;;
esac
