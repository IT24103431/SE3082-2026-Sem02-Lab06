#include <stdio.h>
#include <time.h>

int fib(int n) {
    int i, j;
    if (n < 2)
        return n;
    else {
        i = fib(n - 1);
        j = fib(n - 2);
        return i + j;
    }
}

int main() {
    int n = 30;

    clock_t start = clock();
    int result = fib(n);
    clock_t end = clock();

    double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("fib(%d) = %d\n", n, result);
    printf("Time taken (serial): %f seconds\n", time_taken);

    return 0;
}
