#!/bin/bash

echo "Enter a number"
read num
num1=$num
temp=0
sum=0
while [ $num -gt 0 ]
do
    temp=$(( $num % 10 ))
    sum=$(( $sum + $temp ))
    num=$(( $num / 10 ))
done

echo "The sum of the digits of the numbers is $sum"
