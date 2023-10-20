#!/bin/bash

for i in {2..32}
do
    mpic++ lb1_50.cpp -o lb1_50  && mpiexec -n $i --oversubscribe ./lb1_50;
done     

for i in {2..32}
do
    mpic++ lb1_100.cpp -o lb1_100  && mpiexec -n $i --oversubscribe ./lb1_100;
done     

for i in {2..32}
do
    mpic++ lb1_1000.cpp -o lb1_1000  && mpiexec -n $i --oversubscribe ./lb1_1000;
done     


for i in {2..32}
do
    mpic++ lb1_10000.cpp -o lb1_10000  && mpiexec -n $i --oversubscribe ./lb1_10000;
done     

for i in {2..32}
do
    mpic++ lb1_100000.cpp -o lb1_100000  && mpiexec -n $i --oversubscribe ./lb1_100000;
done     

for i in {2..32}
do
    mpic++ lb1_1000000.cpp -o lb1_1000000  && mpiexec -n $i --oversubscribe ./lb1_1000000;
done     