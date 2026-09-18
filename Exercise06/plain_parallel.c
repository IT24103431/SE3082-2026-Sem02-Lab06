#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000

int main() {
    double *A = (double *)malloc(N * sizeof(double));
    double *B = (double *)malloc(N * sizeof(double));
    double *C = (double *)malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        A[i] = i * 0.5;
        B[i] = i * 2.0;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for
    for (int i = 0; i < N; i++) {
        C[i] = A[i] * B[i];
    }

    double end = omp_get_wtime();

    printf("Sample check: C[100] = %f (expected %f)\n", C[100], A[100] * B[100]);
    printf("Time taken (plain parallel): %f seconds\n", end - start);

    free(A);
    free(B);
    free(C);

    return 0;
}
