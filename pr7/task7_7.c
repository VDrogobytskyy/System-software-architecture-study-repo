#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>

int main(void){
    struct dirent *dp;
    struct stat statbuf;
    DIR *dir = opendir(".");
    char answer[10];

    if (!dir) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    while ((dp = readdir(dir)) != NULL) {
        char *dot = strrchr(dp->d_name, '.');
        if (dot && strcmp(dot, ".c") == 0) {
            
            if (stat(dp->d_name, &statbuf) == -1) {
                perror("stat");
                continue;
            }

            printf("File founded: %s\n", dp->d_name);
            printf("Give other users read permission? (y/n): ");
            
            if (fgets(answer, sizeof(answer), stdin) != NULL) {
                if (answer[0] == 'y' || answer[0] == 'Y') {

                    mode_t new_mode = statbuf.st_mode | S_IROTH;
                    
                    if (chmod(dp->d_name, new_mode) == 0) {
                        printf("Successful: Permission granted.\n\n");
                    } else {
                        perror("Error chmod");
                    }
                } else {
                    printf("Canceled.\n\n");
                }
            }
        }
    }

    closedir(dir);

    putchar('\n');
    return 0;
}
