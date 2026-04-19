#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

long long count = 0;

int compare_ints(const void *a, const void *b) {
    count++;

    int arg1 = *(const int*)a;
    int arg2 = *(const int*)b;

    if (arg1 < arg2){
        return -1;
    }

    if (arg1 > arg2){ 
        return 1;
    }

    return 0;
}

int is_sorted(int *array, int n) {
    for (int i = 0; i < n - 1; i++){
        if (array[i] > array[i + 1]) return 0;
    }
    return 1;
}

void run_experiment(const char *test_name, int *array, int n) {
    count = 0;
    
    clock_t start = clock();
    qsort(array, n, sizeof(int), compare_ints);
    clock_t end = clock();
    
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("%s Comparisons: %lld time: %f seconds %s\n", test_name, count, time_taken, is_sorted(array, n) ? "Correct" : "FAIL");
}

int main(void){
    putchar('\n');
    
    const int N = 1000000000;
    int *arr = malloc(N * sizeof(int));
    srand(time(NULL));

    for (int i = 0; i < N; i++){
        arr[i] = rand() % 100000;
    }
    run_experiment("Random numbers", arr, N);

    for (int i = 0; i < N; i++){
        arr[i] = i;
    }
    run_experiment("Sorted array", arr, N);

    for (int i = 0; i < N; i++){
        arr[i] = N - i;
    }
    run_experiment("Inverse", arr, N);

    for (int i = 0; i < N; i++){
        arr[i] = 7;
    }
    run_experiment("Same numbers", arr, N);

    for (int i = 0; i < N / 2; i++) arr[i] = i;
    for (int i = N / 2; i < N; i++) arr[i] = N - i;
    run_experiment("Pipe Organ Pattern", arr, N);
    
    free(arr);

    putchar('\n');
    return 0;
}
