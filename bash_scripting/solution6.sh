#!/bin/bash

echo "There are two ways of doing this, either with a while loop or with a built in method"
echo "Enter a number"
read num
num1=$num
temp=0
rev=0

while [ $num -gt 0 ]
do
    temp=$(( $num % 10 ))
    rev=`expr $rev \* 10 + $temp` 
    num=$(( $num / 10 ))
done

echo "Reverse of the provided number usinga while loop $rev"

echo -n "The reverse of the number using the built in method is "
echo $num1 | rev
