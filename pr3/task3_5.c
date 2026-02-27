#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void read_and_write_func(FILE *f_to_read, FILE *f_to_write){
        char buffer[100];

        while(fgets(buffer, sizeof(buffer), f_to_read) != NULL){
                fputs(buffer, f_to_write);
        }
}

void file_size_handler(int signal){
        if(signal == SIGXFSZ){
                fprintf(stderr, "File max size reached!\n");
                exit(0);
        }
}

int main(int argc, char *argv[]){
        signal(SIGXFSZ, file_size_handler);
        putchar('\n');
        if(argc != 3){
                fprintf(stderr, "Program need two arguments\n");
                exit(1);
        }

        FILE *rF = fopen("doc_to_read.txt", "r");
        if(!rF){
                fprintf(stderr, "doc_to_read.txt cannot be opened\n");
                exit(1);
        }

        FILE *wF = fopen("doc_to_write.txt", "w");
        if(!wF){
                fprintf(stderr, "doc_to_write.txt cannot be opened\n");
                exit(1);
        }

        read_and_write_func(rF, wF);

        fclose(rF);
        fclose(wF);
        printf("%s\n", "Program finished!");

        putchar('\n');
        return 0;
}
