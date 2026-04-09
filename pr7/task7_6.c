#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

int compare_names(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void list_dirs(const char *base_path) {
    char path[1024];
    struct dirent *dp;
    struct stat statbuf;
    DIR *dir = opendir(base_path);

    if (!dir) return;

    char *found_dirs[256];
    int count = 0;

    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") == 0 || strcmp(dp->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", base_path, dp->d_name);

        if (stat(path, &statbuf) == 0) {
            if (S_ISDIR(statbuf.st_mode)) {
                found_dirs[count] = strdup(dp->d_name);
                count++;
            }
        }
    }

    qsort(found_dirs, count, sizeof(char *), compare_names);

    for (int i = 0; i < count; i++) {
        printf("Directory: %s\n", found_dirs[i]);
        free(found_dirs[i]); 
    }

    closedir(dir);
}

int main(void){
    putchar('\n');

    list_dirs(".");

    putchar('\n');
    return 0;
}
