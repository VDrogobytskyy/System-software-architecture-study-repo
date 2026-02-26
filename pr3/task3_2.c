#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void file_opener(int files_amount){
        int file_desckriptor;

        for(int i = 0; i <= files_amount; i++){
                file_desckriptor = open("file_to_check_ulimit.txt", O_CREAT | O_RDWR);
                if(file_desckriptor == -1){
                        fprintf(stderr, "Opened to many files");
                        putchar('\n');
                        exit(1);
                }
        }

        printf("%s%d%s\n", "We succesfully opened ", files_amount, "files!");

}

int main(void){
        putchar('\n');
        printf("%s\n", "Let`s test our program with ulimit -n 50");

        int test_value = 50;
        file_opener(test_value);
        sleep(10);

        putchar('\n');
        return 0;
}
