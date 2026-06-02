#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define REPEAT 100

/* Acceso secuencial (Paso 2) */
double bench_seq(size_t n_bytes) {
    volatile char *arr = (volatile char *)malloc(n_bytes);
    if (!arr) return -1.0;
    memset((void*)arr, 1, n_bytes);
    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    for (int r = 0; r < REPEAT; r++) {
        for (size_t i = 0; i < n_bytes; i++) {
            (void) arr[i];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);
    free((void*)arr);
    double ns = (t1.tv_sec - t0.tv_sec) * 1e9 + (t1.tv_nsec - t0.tv_nsec);
    return ns / (REPEAT * (double)n_bytes);
}

/* Acceso aleatorio (Paso 3) [cite: 83-105] */
double bench_rand(size_t n_bytes) {
    size_t n = n_bytes / sizeof(int);
    if (n == 0) n = 1;
    int *arr = (int*)malloc(n * sizeof(int));
    size_t *idx = (size_t *)malloc(n * sizeof(size_t));
    if (!arr || !idx) return -1.0;

    for (size_t i = 0; i < n; i++) { arr[i] = 1; idx[i] = i; }
    
    /* Mezcla Fisher-Yates para romper localidad espacial [cite: 92-97] */
    for (size_t i = n - 1; i > 0; i--) {
        size_t j = rand() % (i + 1);
        size_t tmp = idx[i]; idx[i] = idx[j]; idx[j] = tmp;
    }

    struct timespec t0, t1;
    clock_gettime(CLOCK_MONOTONIC, &t0);
    volatile long sum = 0;
    for (int r = 0; r < REPEAT; r++) {
        for (size_t i = 0; i < n; i++) {
            sum += arr[idx[i]];
        }
    }
    clock_gettime(CLOCK_MONOTONIC, &t1);

    free(arr); free(idx);
    double ns = (t1.tv_sec - t0.tv_sec) * 1e9 + (t1.tv_nsec - t0.tv_nsec);
    return ns / (REPEAT * (double)n);
}

int main(void) {
    size_t sizes[] = {
        32*1024,      /* L1 */
        512*1024,     /* L2 */
        4096*1024,    /* L3 */
        16*1024*1024  /* RAM */
    };

    int n_sizes = sizeof(sizes)/sizeof(sizes[0]);
    printf("%-12s %15s %15s\n", "Size(KB)", "Seq(ns/access)", "Rand(ns/access)");

    for (int i = 0; i < n_sizes; i++) {
        double l_seq = bench_seq(sizes[i]);
        double l_rand = bench_rand(sizes[i]);
        printf("%-12zu %15.3f %15.3f\n", sizes[i]/1024, l_seq, l_rand);
    }
    return 0;
}