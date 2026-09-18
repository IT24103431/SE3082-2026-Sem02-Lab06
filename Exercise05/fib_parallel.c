#include <stdio.h>
#include <omp.h>

int fib(int n) {
    int i, j;
    if (n < 2)
        return n;

    #pragma omp task shared(i)
    i = fib(n - 1);

    #pragma omp task shared(j)
    j = fib(n - 2);

    #pragma omp taskwait
    return i + j;
}

int main() {
    int n = 30;
    int result;

    double start = omp_get_wtime();

    #pragma omp parallel
    {
        #pragma omp single
        {
            result = fib(n);
        }
    }

    double end = omp_get_wtime();

    printf("fib(%d) = %d\n", n, result);
    printf("Time taken (parallel): %f seconds\n", end - start);

    return 0;
}
