#!/bin/bash

for i in {1..32}
do
    mpic++ lb3.cpp -o lb3  && mpiexec -n $i --oversubscribe ./lb3;
done     
