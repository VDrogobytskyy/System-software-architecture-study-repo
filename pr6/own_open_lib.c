#include <stdio.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <time.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>

int open(const char *path, int oflag, ... ){

	static int (*native_open)(const char *path, int oflag, ...) = NULL;
	if(!native_open){
		native_open = dlsym(RTLD_NEXT, "open");
	}
	time_t raw_time;

	time(&raw_time);

	printf("%s\n", "Open func was hooked. We will have logging from own LIB.");
	printf("%s%s%s%s\n", "On time: ", ctime(&raw_time), "file was opened by path: ", path);

	if(oflag & O_CREAT){
		va_list arguments;
		va_start (arguments, oflag);
		mode_t mode = va_arg(arguments, mode_t);
		va_end(arguments);

		printf("%s%o\n", "We used this flag: ", mode);
		return native_open(path, oflag, mode);
	}

	return native_open(path, oflag);
}

