#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void list_files(const char *base_path) {
    char path[1024];
    struct dirent *dp;
    struct stat statbuf;
    DIR *dir = opendir(base_path);

    if (!dir) {
        return;
    }

    while ((dp = readdir(dir)) != NULL) {

        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", base_path, dp->d_name);

        stat(path, &statbuf);

        if (S_ISDIR(statbuf.st_mode)){
            printf("Directory: %s\n", path);
            list_files(path);
        }else{
            printf("File: %s\n", path);
        }
    }

    closedir(dir);
}

int main(void){
    putchar('\n');

    printf("Listing all files starting from current directory:\n\n");

    list_files(".");
    putchar('\n');
    return 0;
}
