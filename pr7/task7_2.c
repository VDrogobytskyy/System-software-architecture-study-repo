#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void print_permissions(mode_t mode);

int main(void){
	putchar('\n');
	DIR *directory;

	struct dirent *files;
	struct stat file_stat;
	struct passwd *pw;
	struct group *gr;

	char time_str[80];

	if((directory = opendir(".")) == NULL){
		fprintf(stderr, "Fail to open dir\n");
		return EXIT_FAILURE;
	}

	while((files = readdir(directory)) != NULL){
		if(files->d_name[0] == '.'){
			continue;
		}
		if (stat(files->d_name, &file_stat) == -1) {
            		perror("stat");
            		continue;
        	}

		print_permissions(file_stat.st_mode);

		printf(" %2ld", (long)file_stat.st_nlink);

		pw = getpwuid(file_stat.st_uid);
		gr = getgrgid(file_stat.st_gid);
		printf(" %s %s", pw->pw_name, gr->gr_name);

		printf(" %8lld", (long long)file_stat.st_size);

		strftime(time_str, sizeof(time_str), "%b %d %H:%M", localtime(&file_stat.st_mtime));
		printf(" %s", time_str);

		printf(" %s\n", files->d_name);
	}

	closedir(directory);

	putchar('\n');
	return 0;
}

void print_permissions(mode_t mode) {
    putchar((S_ISDIR(mode)) ? 'd' : (S_ISLNK(mode)) ? 'l' : '-');
    putchar((mode & S_IRUSR) ? 'r' : '-');
    putchar((mode & S_IWUSR) ? 'w' : '-');
    putchar((mode & S_IXUSR) ? 'x' : '-');
    putchar((mode & S_IRGRP) ? 'r' : '-');
    putchar((mode & S_IWGRP) ? 'w' : '-');
    putchar((mode & S_IXGRP) ? 'x' : '-');
    putchar((mode & S_IROTH) ? 'r' : '-');
    putchar((mode & S_IWOTH) ? 'w' : '-');
    putchar((mode & S_IXOTH) ? 'x' : '-');
}
