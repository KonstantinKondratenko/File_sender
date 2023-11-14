#include <iostream>
#include <stdio.h>
#include "mpi.h"
#include <fstream>
#include <string>



// void print(double* array_to_print, int n)
// {
//     for (int i = 0; i < n; i++)
//         std::cout << array_to_print[i] << " ";
//     std::cout << std::endl;

// }


bool search(int* array, int size, int num) 
{
    for (int i = 0; i < size; i++) 
    {
        if (array[i] == num) 
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]) 
{
    int ProcNum, ProcRank;

    MPI_Status Status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    MPI_Group WorldGroup, WorkerGroup;
    MPI_Comm Workers;
    double starttime, endtime;
    MPI_Barrier(MPI_COMM_WORLD);
    starttime = MPI_Wtime();

    if (ProcNum < 2) 
    {
        std::cout << "No processes with odd numbers \n";
        return 0;
    }

    int size_del_ranks = (ProcNum / 2) + (ProcNum % 2);
    int* ranks = new int[size_del_ranks];
    int t = 0;

    for (int i = 0; i < size_del_ranks; i++) 
    {
        ranks[i] = t;
        t += 2;
    }

    double* array = new double[2];
    int size_res = (ProcNum - size_del_ranks)*2;
    double* res = new double[size_res];
    srand((unsigned)time(NULL) + ProcRank * ProcNum);

    if (ProcRank % 2 == 1) 
    {
        array[0] = (double)rand() / 10;
        array[1] = (double)rand() / 30;
    }
    MPI_Comm_group(MPI_COMM_WORLD, &WorldGroup);
    MPI_Group_excl(WorldGroup, size_del_ranks, ranks,&WorkerGroup);
    MPI_Comm_create(MPI_COMM_WORLD, WorkerGroup, &Workers);
    if (Workers != MPI_COMM_NULL) 
    {
        MPI_Allgather(array, 2, MPI_DOUBLE, res, 2, MPI_DOUBLE, Workers);
        // std::cout << "Process: " << ProcRank << " ->\n";
        // std::cout << "a and b:\n";
        // print(array, 2);
        // std::cout << "Array result: \n";
        // print(res, size_res);
        MPI_Comm_free(&Workers);
    }

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