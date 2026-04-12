#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

void adjust_permissions(const char *path) {
    struct stat st;

    if (stat(path, &st) == -1) {
        perror("stat");
        return;
    }

    if (!S_ISREG(st.st_mode)) return;

    printf("File: %-15s | Link: %ld | Permissions: %o\n", 
            path, (long)st.st_nlink, st.st_mode & 0777);

    if (st.st_nlink > 1) {
        mode_t new_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
        
        if (chmod(path, new_mode) == 0) {
            printf("Active usage!!! only reading.\n");
        } else {
            perror("Error chmod");
        }
    }
}

int main(int argc, char *argv[]){
    putchar('\n');

    DIR *dir;
    struct dirent *entry;

    const char *dir_path = (argc > 1) ? argv[1] : ".";
    dir = opendir(dir_path);

    if (!dir) {
        perror("opendir");
        return EXIT_FAILURE;
    }

    printf("File analyse: %s\n", dir_path);

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        adjust_permissions(entry->d_name);
    }

    closedir(dir);

    putchar('\n');
    return 0;
}
