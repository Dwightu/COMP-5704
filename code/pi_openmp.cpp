#include <iostream>
#include <omp.h>
#include<time.h>

static constexpr long MAX_N = 1000000000;

double calc_pi(const long N);

int main()
{
    std::cout.precision(20);
    std::cout << "Hello_OpenMP_PI_Program" << '\n';
    int numProcs = omp_get_max_threads();
    std::cout << "max_threads" << numProcs<<'\n';
    std::cout << calc_pi1(MAX_N) << '\n';
    std::cout << calc_pi2(MAX_N) << '\n';
    std::cout << calc_pi4(MAX_N) << '\n';
    std::cout << calc_pi8(MAX_N) << '\n';
    std::cout << calc_pi16(MAX_N) << '\n';
    return 0;
}

double calc_pi1(const long N)
{
    float startTime1 = omp_get_wtime();
    const double N1 = 1.0 / N;
    double res = 0.0;

#pragma omp parallel num_threads(1)
{   
    double tmp = 0.0;

#pragma omp for
for (long i = 0; i < N; i++)
    {
        const double x = (i + 0.5) * N1;
        tmp += 4.0 / (x * x + 1);
    }
        res += tmp;
    }
    float endTime1 = omp_get_wtime();
    printf("For one thread time: %f\n", endTime1 - startTime1);
    return res / N;
}

double calc_pi2(const long N)
{
    float startTime2 = omp_get_wtime();
    const double N1 = 1.0 / N;
    double res = 0.0;

#pragma omp parallel num_threads(2)
{   
    double tmp = 0.0;

#pragma omp for
for (long i = 0; i < N; i++)
    {
        const double x = (i + 0.5) * N1;
        tmp += 4.0 / (x * x + 1);
    }
        res += tmp;
    }
    printf("For two thread time: %f\n", endTime2 - startTime2);
    return res / N;
}

double calc_pi4(const long 4)
{
    float startTime3 = omp_get_wtime();
    const double N1 = 1.0 / N;
    double res = 0.0;

#pragma omp parallel num_threads(2)
{   
    double tmp = 0.0;

#pragma omp for
for (long i = 0; i < N; i++)
    {
        const double x = (i + 0.5) * N1;
        tmp += 4.0 / (x * x + 1);
    }
        res += tmp;
    }
    printf("For four thread time: %f\n", endTime3 - startTime3);
    return res / N;
}

double calc_pi8(const long 8)
{
    const double N1 = 1.0 / N;
    double res = 0.0;

#pragma omp parallel num_threads(2)
{   
    double tmp = 0.0;

#pragma omp for
for (long i = 0; i < N; i++)
    {
        const double x = (i + 0.5) * N1;
        tmp += 4.0 / (x * x + 1);
    }
        res += tmp;
    }
    printf("For eight thread time: %f\n", endTime - startTime);
    return res / N;
}

double calc_pi816(const long 16)
{
    const double N1 = 1.0 / N;
    double res = 0.0;

#pragma omp parallel num_threads(2)
{   
    double tmp = 0.0;

#pragma omp for
for (long i = 0; i < N; i++)
    {
        const double x = (i + 0.5) * N1;
        tmp += 4.0 / (x * x + 1);
    }
        res += tmp;
    }
    printf("For sixteen thread time: %f\n", endTime - startTime);
    return res / N;
}