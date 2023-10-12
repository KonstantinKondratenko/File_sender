#include <iostream>
#include <mpi.h>
#include <fstream>
#include <chrono>


int main(int argc, char* argv[])
{
    std::ofstream out;
    out.open("result.txt", std::ios::app);    

    // инициализация
    int process_num, process_rank, recevied_rank;
    auto start_time = std::chrono::steady_clock::now();
    MPI_Status status;

    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &process_num); // определение количества параллельных процессов
    MPI_Comm_rank(MPI_COMM_WORLD, &process_rank); // каждый процесс определяет свой ранг
    if (process_rank == 0) // выполняет процесс только с рангом 0
    {
        //std::cout << "Hello from process " << process_rank << std::endl; // 
        
        // последовательно принимает сообщения от процессов c их рангами
        for(int i = 1; i < process_num; i++)
        {
            MPI_Recv(&recevied_rank, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &status);
            //MPI_Recv(&recevied_rank, 1, MPI_INT, i, MPI_ANY_TAG, MPI_COMM_WORLD, &status); 
            //std::cout << " Hello from process " << recevied_rank << std::endl;
        }

        auto end_time = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time);
        out << process_num << " " << elapsed_ms.count() << std::endl;
    }
    else // все остальные процессы передают значение своего ранга нулевому
    {
        MPI_Send(&process_rank, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();
    out.close();

    return 0;
}
