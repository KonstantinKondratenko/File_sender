#!/bin/bash

bash ./make_childrens.sh 
echo "childrens done"
gcc father_fifo.c -o father_fifo
./father_fifo

