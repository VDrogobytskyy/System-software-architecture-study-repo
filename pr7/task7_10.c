#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double rand_zero_to_one() {
    return (double)rand() / (double)RAND_MAX;
}

double rand_zero_to_n(double n) {
    return ((double)rand() / (double)RAND_MAX) * n;
}

int main(void){
    putchar('\n');
    srand((unsigned int)time(NULL));

    double n = 59.1;
    int count = 7;

    printf("(a) Range [0.0, 1.0]:\n");
    for (int i = 0; i < count; i++) {
        printf("  %f\n", rand_zero_to_one());
    }

    printf("\n(b) Range [0.0, %.2f]:\n", n);
    for (int i = 0; i < count; i++) {
        printf("  %f\n", rand_zero_to_n(n));
    }

    putchar('\n');
    return 0;
}
