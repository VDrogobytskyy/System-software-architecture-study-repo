#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void dice_roll(FILE *f) {
    srand(time(NULL));
    int count = 0;

    printf("%s\n", "Program starts, trying to do 100,000 rolls");

    while (1) {
        int random_roll = (rand() % 6) + 1;
        if (fprintf(f, "%d\n", random_roll) < 0) {
            fprintf(stderr, "\nfprintf ERROR: %s\n", strerror(errno));
            return;
        }

        if (fflush(f) != 0) {
            if (errno == EFBIG) { // EFBIG - File too large
                fprintf(stderr, "\nATTENTION Max file size reached!\n");
            } else {
                fprintf(stderr, "\nfprintf ERROR: %s\n", strerror(errno));
            }
            return;
        }

        count++;
        if (count >= 100000) {
            printf("\n100,000 rolls completed!\n");
            return;
        }

        if (count % 100 == 0) printf("\rWrote: %d", count);
    }
}

int main(void){
	signal(SIGXFSZ, SIG_IGN);
	putchar('\n');
    	FILE *f = fopen("dice_roll.txt", "w+");

    	if (!f) {
        	fprintf(stderr, "Error can`t open dice_roll.txt file: %s\n", strerror(errno));
        	exit(1);
    	}

    	dice_roll(f);

    	fclose(f);
	putchar('\n');
	printf("\nProgram finished.\n");
    	return 0;
}
