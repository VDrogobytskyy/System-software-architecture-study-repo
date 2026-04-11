#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

int main(void){
    putchar('\n');
    
    struct dirent *dp;
    struct stat statbuf;
    DIR *dir = opendir("."); 
    char answer[10];

    if (!dir) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    while ((dp = readdir(dir)) != NULL) {

        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue;
        }

        if (stat(dp->d_name, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                continue; 
            }
        }

        printf("Delete file '%s'? (y/n): ", dp->d_name);
        
        if (fgets(answer, sizeof(answer), stdin) != NULL) {
            if (answer[0] == 'y' || answer[0] == 'Y') {
                if (unlink(dp->d_name) == 0) {
                    printf("File '%s' successfully deleted.\n", dp->d_name);
                } else {
                    perror("Deleting error");
                }
            } else {
                printf("Skipped.\n");
            }
        }
    }

    closedir(dir);

    putchar('\n');
    return 0;
}
