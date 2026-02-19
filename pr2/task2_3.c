#include <stdio.h>
#include <stdlib.h>


int arr_bss[1000];
int arr_data[1000] = {32, 12 ,523 ,43};


void func(){
	int arr[1000];
	char chr_arr[1000] = {'e','w','t'};
}

int main(void){
	putchar('\n');
	static int static_int_data = 5;
	int local_str = 5;
	int *heap = malloc(100 * sizeof(int));
	func();
	printf("Address of text segment (main function): %p\n", main);
    	printf("Address of .bss: %p\n", arr_bss);
	printf("Address of .data: %p\n", arr_data);
        printf("Address of static_var: %p\n", &static_int_data);
        printf("Address of stack: %p\n", &local_str);
   	printf("Address of heap (malloc): %p\n", heap);

	free(heap);

	putchar('\n');
	return 0;
}
