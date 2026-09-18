#include <stdio.h>
#include <omp.h>

#define NPOINTS 1000
#define MAXITER 2000

struct d_complex {
    double r;
    double i;
};

int testpoint(struct d_complex c) {
    struct d_complex z;
    int iter;
    double temp;

    z = c;
    for (iter = 0; iter < MAXITER; iter++) {
        temp = (z.r * z.r) - (z.i * z.i) + c.r;
        z.i = 2.0 * z.r * z.i + c.i;
        z.r = temp;
        if ((z.r * z.r + z.i * z.i) > 4.0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    int i, j;
    double area, eps;
    int numoutside = 0;

    eps = 1.0e-5;

    double start = omp_get_wtime();

    #pragma omp parallel for private(j) reduction(+:numoutside)
    for (i = 0; i < NPOINTS; i++) {
        struct d_complex c;
        for (j = 0; j < NPOINTS; j++) {
            c.r = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS) + eps;
            c.i = 1.125 * (double)(j) / (double)(NPOINTS) + eps;

            if (testpoint(c) == 0) {
                numoutside++;
            }
        }
    }

    area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) / (double)(NPOINTS * NPOINTS);

    double end = omp_get_wtime();

    printf("Area of Mandelbrot set = %12.8f\n", area);
    printf("Points outside set = %d\n", numoutside);
    printf("Threads used: %d\n", omp_get_max_threads());
    printf("Time taken (parallel): %f seconds\n", end - start);

    return 0;
}
