#!/bin/bash

bash ./make_childrens.sh 
echo "childrens done"
gcc father_rr.c -o father_rr
./father_rr

