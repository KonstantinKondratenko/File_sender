for i in {2..32}
do
    mpic++ lb2.cpp -o lb2  && mpiexec -n $i --oversubscribe ./lb2;
done   