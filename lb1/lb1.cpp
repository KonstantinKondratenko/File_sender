#include<iostream>
#include <fstream>
#include "mpi.h"
#include <ctime>
#include<cmath>
#include <string> 
 
using namespace std;
//200000000
 
const int n = 100; // set all size
/*

run cpp in terminal
mpic++ lb1.cpp -o lb1

run object 

mpiexec -n <#process> ./lb1 

or

mpiexec -n <#process> --oversubscribe ./lb1 


*/
// run in terminal
// mpic++ lb1.cpp -o lb1


 

int main(int argc, char *argv[]) 
{
  	int ProcNum, ProcRank, RecvRank;
 
  	MPI_Status Status;
  	MPI_Init(&argc, &argv);
  	MPI_Comm_size(MPI_COMM_WORLD, &ProcNum);
  	MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);
  	double starttime, endtime;
  	MPI_Barrier(MPI_COMM_WORLD);

   
    int* array = new int[n];
 
  	if (ProcNum < 2) 
    {
         	cout << "ProcNum == " << ProcNum << " less then 2" << endl;
         	return -1;
  	}
    // расчет размера подмасиива
  	int size = ceil((double) n / (ProcNum - 1));
  	int* newArray = new int[size];

  	if (ProcRank == 0) 
    {
        // заполнение массива значениями 0-6
        for (int i = 0; i < n; i++)        
            array[i] = rand() % 7;
        
        
        
        for (int i = 1; i < ProcNum; i++) 
        {
            int index = (i - 1) * size;
            if (index < n) 
            {
                if ((index + size) > n)
                    MPI_Send(&array[index], n-index, MPI_INT, i, 0, MPI_COMM_WORLD);    
                else
                    MPI_Send(&array[index], size, MPI_INT, i, 0, MPI_COMM_WORLD);                
            }
            else 
            {
                    int ds = 1;
                    MPI_Send(&ds, 1, MPI_INT, i, 0, MPI_COMM_WORLD);
            }
        }

        int countNull = 0;
        starttime = MPI_Wtime();
        for (int j = 1; j < ProcNum; j++) 
        {
            MPI_Recv(&RecvRank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
            countNull += RecvRank;
        }
        cout << "(Parent) \t Count null :" << countNull << endl;
 
  	}
  	else 
    {
        MPI_Recv(newArray, size, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
        int sum = 0;
        for (int i = 0; i < size; i++) 
        {
            if (newArray[i] == 0) 
            {
                sum++;
            }
        }
        MPI_Send(&sum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
 
  	}
 
 
  	MPI_Barrier(MPI_COMM_WORLD);
  	endtime = MPI_Wtime();
  	
  	MPI_Finalize();
 
  	if (ProcRank == 0) 
    {
        cout << "(main) \t  Time " << (endtime - starttime) * 1000000  <<" micro-seconds" << endl;
        ofstream out_file;        
        string file_name = "result_"  + to_string(n) + ".txt";
        out_file.open(file_name, ios::app);
        out_file << n << "\t" <<  ProcNum << "\t" << (endtime - starttime) * 1000000 << endl;
        out_file.close();
    }
  	return 0;
 
}

