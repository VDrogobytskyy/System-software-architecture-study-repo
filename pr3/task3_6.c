#include <stdio.h>
#include <stdlib.h>


void crashing_by_arr_size(){
        int arr[2 * 8192 * 8192];
        arr[10] = 5;
        printf("%s\n", "You will never see this message!");
}


int main(void){
        putchar('\n');

        crashing_by_arr_size();

        putchar('\n');
        return 0;
}
