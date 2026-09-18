#include <stdio.h>
#include <time.h>

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
            return 0;  // escaped - outside the set
        }
    }
    return 1;  // did not escape - inside the set
}

int main() {
    int i, j;
    double area, eps, ztemp;
    struct d_complex c;
    int numoutside = 0;

    eps = 1.0e-5;

    clock_t start = clock();

    for (i = 0; i < NPOINTS; i++) {
        for (j = 0; j < NPOINTS; j++) {
            c.r = -2.0 + 2.5 * (double)(i) / (double)(NPOINTS) + eps;
            c.i = 1.125 * (double)(j) / (double)(NPOINTS) + eps;

            if (testpoint(c) == 0) {
                numoutside++;
            }
        }
    }

    area = 2.0 * 2.5 * 1.125 * (double)(NPOINTS * NPOINTS - numoutside) / (double)(NPOINTS * NPOINTS);

    clock_t end = clock();
    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("Area of Mandelbrot set = %12.8f\n", area);
    printf("Points outside set = %d\n", numoutside);
    printf("Time taken (serial): %f seconds\n", time_taken);

    return 0;
}
