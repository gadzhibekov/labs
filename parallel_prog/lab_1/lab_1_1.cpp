#include <iostream>
#include <omp.h>

int main() 
{
    #pragma omp parallel num_threads(4)
    {
        u_int thread_id = omp_get_thread_num();
        
        if (thread_id % 2 == 0) 
        {
            #pragma omp critical
            {
                std::cout << "Even-numbered thread: " << thread_id << std::endl;
            }
        } 
        else 
        {
            #pragma omp critical
            {
                std::cout << "Odd-numbered  thread: " << thread_id << std::endl;
            }
        }
    }
    
    return 0;
}