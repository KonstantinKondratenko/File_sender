#!/bin/bash

for (( i=1; i <= 18; i++ ))
do
gcc son$i.c -o son$i -lm
#echo "number is $i"
done
