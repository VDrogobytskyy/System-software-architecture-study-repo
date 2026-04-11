#include <stdio.h>
#include <time.h>
#include <stdlib.h>

void making_one_hundred_thousand_iterations();

int main(void){
	putchar('\n');
	srand(time(NULL));
	clock_t program_started, program_finished;

	program_started = clock();
	making_one_hundred_thousand_iterations();
	program_finished = clock();

	double result_in_miliseconds = ((double) program_finished - program_started) / CLOCKS_PER_SEC * 1000;

	printf("%s%.4f%s\n", "Our func worked for: ", result_in_miliseconds, " miliseconds.");
	putchar('\n');
	return 0;
}

void making_one_hundred_thousand_iterations(){
	int random_numbers[100000];
	int size = sizeof(random_numbers) / sizeof(random_numbers[0]);

	for(int i = 0; i < size; i++){
		random_numbers[i] = rand();
	}
}
