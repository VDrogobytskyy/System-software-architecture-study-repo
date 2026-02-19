#include <stdio.h>
#include <time.h>


int main(void){
	putchar('\n');

	printf("%s\n", "Lets print out max value for time_t in 64bits");
	time_t max_time_t_for_64_bits = (time_t)((1ULL << 63) - 1);
	printf("%lld\n", (long long)max_time_t_for_64_bits);

	printf("%s\n", "Lets print out max value for time_t in 32bits");
        time_t max_time_t_for_32_bits = (time_t)((1UL << 31) - 1);
        printf("%lld\n", (long long)max_time_t_for_32_bits);

	putchar('\n');
	return 0;
}
