#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

#define N 1000000
#define STRIP_SIZE 8   // aligns with common SIMD vector width (e.g. AVX = 8 floats)

int main() {
    double *A = (double *)malloc(N * sizeof(double));
    double *B = (double *)malloc(N * sizeof(double));
    double *C = (double *)malloc(N * sizeof(double));

    for (int i = 0; i < N; i++) {
        A[i] = i * 0.5;
        B[i] = i * 2.0;
    }

    double start = omp_get_wtime();

    #pragma omp parallel for schedule(static)
    for (int strip_start = 0; strip_start < N; strip_start += STRIP_SIZE) {
        int strip_end = strip_start + STRIP_SIZE;
        if (strip_end > N) strip_end = N;

        #pragma omp simd
        for (int i = strip_start; i < strip_end; i++) {
            C[i] = A[i] * B[i];
        }
    }

    double end = omp_get_wtime();

    printf("Sample check: C[100] = %f (expected %f)\n", C[100], A[100] * B[100]);
    printf("Sample check: C[999999] = %f (expected %f)\n", C[999999], A[999999] * B[999999]);
    printf("Time taken (strip mining): %f seconds\n", end - start);

    free(A);
    free(B);
    free(C);

    return 0;
}
