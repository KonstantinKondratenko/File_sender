#!/bin/bash

for i in {2..32}
do
    mpiexec -n $i --oversubscribe  ./lb5;
done    