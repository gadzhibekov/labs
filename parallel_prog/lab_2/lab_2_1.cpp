#include <iostream>
#include <cmath>
#include <omp.h>

double f(double x)                          {return  sin(x); }
double exact_integral(double a, double b)   {return -cos(b) + cos(a); }

int main() 
{
    const double a  = 0.0;
    const double b  = M_PI;
    const int n     = 10000000;
    
    double h        = (b - a) / n;
    double sum      = 0.0;
    double start_time, end_time;
    
    start_time      = omp_get_wtime();
    
    #pragma omp parallel
    {
        double local_sum = 0.0;
        
        #pragma omp for
        for (int i = 0; i < n; i++) 
        {
            double x_mid = a + (i + 0.5) * h;
            local_sum += f(x_mid);
        }
        
        #pragma omp critical
        {
            sum += local_sum;
        }
    }
    
    double integral     = sum * h;
    
    end_time            = omp_get_wtime();
    
    double exact        = exact_integral(a, b);
    double error        = fabs(integral - exact);
    
    std::cout.precision(12);
    std::cout << "Результаты вычисления интеграла\t\t"  << std::endl;
    std::cout << "Функция\t\t\t\tsin(x)"                << std::endl;
    std::cout << "Пределы интегрирования\t\t["          << a                        << ", "         << b << "]" << std::endl;
    std::cout << "Количество разбиений\t\t"             << n                        << std::endl;
    std::cout << "Приближенное значение\t\t"            << integral                 << std::endl;
    std::cout << "Точное значение\t\t\t"                << exact                    << std::endl;
    std::cout << "Абсолютная погрешность\t\t"           << error                    << std::endl;
    std::cout << "Время вычисления\t\t"                 << end_time - start_time    << " секунд"    << std::endl;
    std::cout << "Количество потоков\t\t"               << omp_get_max_threads()    << std::endl;
    
    return 0;
}