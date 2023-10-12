#!/bin/bash

for i in {1..32}
do
    mpiexec -n $i --oversubscribe ./lb0_time;
done                  
