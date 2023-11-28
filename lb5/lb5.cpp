//mpic++ lb5.cpp -o lb5
//mpiexec -n 10 --oversubscribe  ./lb5
#include <iostream>
#include <stdio.h>
#include "mpi.h"
#include <fstream>
#include <string>


int main(int argc, char* argv[]) 
{
    int ProcNum, ProcRank;
    double starttime, endtime;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Barrier(MPI_COMM_WORLD);
    starttime = MPI_Wtime();
    double data = ProcRank * 2.0;

    int dims[1] = { ProcNum };
    int periods[1] = { 1 }; 

    MPI_Comm commCart;
    MPI_Cart_create(MPI_COMM_WORLD, 1, dims, periods, 1, &commCart);

    int lSibling, rSibling;
    MPI_Cart_shift(commCart, 0, 1, &lSibling, &rSibling);

    MPI_Send(&data, 1, MPI_DOUBLE, lSibling, 0, commCart);
    MPI_Recv(&data, 1, MPI_DOUBLE, rSibling, 0, commCart, MPI_STATUS_IGNORE);

    // std::cout << "Process : "<<ProcRank << "\t take \t" << data << "\t from \t" << rSibling << std::endl;

    MPI_Barrier(MPI_COMM_WORLD);
    endtime = MPI_Wtime();

    MPI_Finalize();

    if (ProcRank == 0) 
	{
        std::cout << "(main) \t  Time " << (endtime - starttime) * 1000000  <<" micro-seconds" << std::endl; 
        std::ofstream out_file;        
        std::string file_name = "result.txt";
        out_file.open(file_name, std::ios::app);
        out_file << ProcNum << "\t" << (endtime - starttime) * 1000000 << std::endl;
        out_file.close();
    }
    return 0;
}