#include <iostream>
#include <stdio.h>
#include "mpi.h"
#include <fstream>
#include <string>

int main(int argc, char* argv[]) 
{ 
	MPI_Status Status;
    MPI_Init(&argc, &argv);

    double starttime, endtime;
	MPI_Barrier(MPI_COMM_WORLD);
	starttime = MPI_Wtime();

    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);


    // std::cout <<  "rank# " << rank <<  " \t size# (k) " << size << " \t Init vales #(k+5) == " << size + 5 <<  ":\n";
	double* nums = new double[size + 5];	
    
    for (int i = 0; i < size + 5; ++i)
    {
		nums[i] = i + rank;
        // std::cout << rank << ":" << i << " : " << nums[i] << std::endl;
    }
	double* result = new double[size + 5];
	MPI_Allreduce(nums, result, size + 5, MPI_DOUBLE, MPI_PROD, MPI_COMM_WORLD);
    if (rank == 0) 
    {
        std::cout << "Result: ";   
        for (int i = 0; i < size + 5; ++i)
                std::cout << result[i] << " ";
        std::cout << std::endl;
    }

    
	endtime = MPI_Wtime();
    MPI_Finalize();

    if (rank == 0)    
    {
        std::cout << "(main) \t  Time " << (endtime - starttime) * 1000000  <<" micro-seconds" << std::endl; 
        std::ofstream out_file;        
        std::string file_name = "result.txt";
        out_file.open(file_name, std::ios::app);
        out_file << size << "\t" << (endtime - starttime) * 1000000 << std::endl;
        out_file.close();
    }
}