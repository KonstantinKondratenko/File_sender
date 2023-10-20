#include<iostream>
#include<fstream>
#include <stdio.h>
#include "mpi.h"
#include <map>
#include<string>
#include <ctime>
#include <stdlib.h>
#include <time.h>

using namespace std;

void print(int* array, int size) 
{
    for (int i = 0; i < size; i++) 
    {
        if (i == size -1) 
            cout << array[i] << endl;
        else
            cout << array[i] << "-";
    }
}

bool search(int* array, int size, int num) 
{
    for (int i = 0; i < size; i++) 
    {
        if (array[i] == num) 
            return false;    
    }
    return true;
}

int main(int argc, char *argv[]) 
{
    int ProcNum, ProcRank;

    MPI_Status Status;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
    double starttime, endtime;
    MPI_Barrier(MPI_COMM_WORLD);
    

    if (ProcRank == 0) 
    {
        int* array = new int[ProcNum];
        // init array as -1
        for (int i = 0; i < ProcNum; i++) 
            array[i] = -1;

        // random seed
        srand((unsigned)time(NULL) );
        int process_to_send = rand() % ProcNum;
        //cout << i << "\n";
        if(ProcNum == 1) 
        {
            cout << "Process 0 has no one to send the message to" << "\n";
            return -1;
        }

        //bag generation fix
        if (process_to_send == ProcRank) 
            process_to_send = 1;
        starttime = MPI_Wtime();
        MPI_Send(array, ProcNum, MPI_INT, process_to_send, 0, MPI_COMM_WORLD);
        MPI_Recv(array, ProcNum, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
        array[ProcNum - 1] = ProcRank;
        cout << "Хронология передачи сигналов: " << endl;
        print(array, ProcNum);
    }
    else 
    {
        int *array = new int[ProcNum];
        MPI_Recv(array, ProcNum, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
        srand((unsigned)time(NULL) + ProcRank * ProcNum);
        int i = rand() % ProcNum;
        for (int j = 0; j < ProcNum; j++) 
        {
            if (array[j] == -1) 
            {
                array[j] = ProcRank;
                break;
            }
        }

        if (i == 0 && array[ProcNum - 2] == -1) 
            i = 1;

        while (search(array, ProcNum, i) != true) 
        {
            i = (i + 1) % ProcNum;
            if (i == 0 && array[ProcNum - 2] == -1) 
                i = 1;
            
        }
        MPI_Send(array, ProcNum, MPI_INT, i, 0, MPI_COMM_WORLD);
    }

    MPI_Barrier(MPI_COMM_WORLD);
    endtime = MPI_Wtime();

    MPI_Finalize();

    if (ProcRank == 0) 
    {
        cout << "(main) \t  Time " << (endtime - starttime) * 1000000  <<" micro-seconds" << endl;
        ofstream out_file;        
        string file_name = "result.txt";
        out_file.open(file_name, ios::app);
        out_file << ProcNum << "\t" << (endtime - starttime) * 1000000 << endl;
        out_file.close();
    }

    return 0;

}