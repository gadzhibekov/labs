#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

int main() 
{
    const int N = 20;
    int A[N];
    
    srand(time(0));
    
    for (int i = 0; i < N; i++) 
    {
        A[i] = rand() % 100;
    }
    
    std::cout << "Array A: ";
    for (int i = 0; i < N; i++) 
    {
        std::cout << A[i] << " ";
    }
    std::cout << std::endl;
    
    #pragma omp parallel
    {
        int thread_id       = omp_get_thread_num();
        int num_threads     = omp_get_num_threads();
        int block_size      = N / num_threads;
        int start           = thread_id * block_size;
        int end             = (thread_id == num_threads - 1) ? N : start + block_size;
        int partial_sum     = 0;
        
        for (int i = start; i < end; i++) 
        {
            partial_sum += A[i];
        }
        
        #pragma omp critical
        {
            printf("Thread: %d\tpartial sum: %d\t(elements %d to %d)\n", thread_id, partial_sum, start, end - 1);
            
            static int total_sum_critical = 0;
            total_sum_critical += partial_sum;
            
            if (thread_id == 0) 
            {
                std::cout << "Total sum (critical): " << total_sum_critical << std::endl;
            }
        }
    }
    
    return 0;
}