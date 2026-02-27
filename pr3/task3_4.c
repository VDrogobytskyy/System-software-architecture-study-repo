#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

void gamble_func(int *ar, int amount, int max_value){
        int counter = 0;
        for(int i = 0; i < amount; i++){
                int rand_number = (rand() % max_value) + 1;
                ar[counter] = rand_number;
                counter++;
        }
}

void line_drower(int amount){
        for(int i = 0; i <= amount; i++){
                putchar('-');
        }
        putchar('\n');
}

void cpu_limit_handler(int signal){
        if(signal == SIGXCPU){
                fprintf(stderr, "CPU TIME LIMIT REACHED\n");
                exit(0);
        }
}

int main(void){
        signal(SIGXCPU, cpu_limit_handler);
        putchar('\n');
        srand(time(NULL));
        int array_sixth[6] = {0};
        int array_seventh[7] = {0};

        int counter = 0;
        while(1){
                gamble_func(array_sixth, 6, 36);
                gamble_func(array_seventh, 7, 49);

                line_drower(22);
                printf("%s\n", "6 numbers with high 36:");
                for(int i = 0; i < 6; i++){
                        printf("%d%c", array_sixth[i], ' ');
                }

                putchar('\n');
                line_drower(22);
                fflush(stdout);
                printf("%s\n", "7 numbers with high 49:");

                for(int i = 0; i < 7; i++){
                        printf("%d%c", array_seventh[i], ' ');
                }
                putchar('\n');
                fflush(stdout);
                counter++;
                if(counter == 10000000){
                        printf("%s\n", "Program created 10,000,000 combinations!");
                        break;
                }
        }

        putchar('\n');
        return 0;
}
