#include <stdio.h>
#include <stdlib.h>

/*

  Task complited by Drogobytskyy Volodymyr
  From group TB-41
  On date 02-02-2026

  made in UTM - with ubuntu

*/

int main(void){
  
  putchar('\n');
  int input_seconds;

  char user_choice = '\0';

  printf("%s\n", "This programe take your seconds input, and tell you when event will happend or when it took place already!");
  do{
    printf("%s\n", "C to continue/Q to quit");

    scanf(" %c", &user_choice);

    
    if(user_choice == 'C' || user_choice == 'c'){
      printf("%s\n", "Enter amount of seconds to convert!");

      while((user_choice = getchar()) != '\n');
      if(scanf(" %d", &input_seconds) != 1){
        printf("%s", "You have to enter INTEGER, try again");
        return 1;
      }

      int positive_second = abs(input_seconds);

      int temp_hours = positive_second / 3600;
      int temp_minutes = (positive_second % 3600) / 60;
      int temp_seconds = positive_second % 60;

      if(input_seconds > 0){
        printf("%s\n%s%d\n%s%d\n%s%d\n", "The event WILL TAKE place through:", "In hours: ", temp_hours, "In minutes:", temp_minutes, "In seconds: ", temp_seconds);

      }else{
        printf("%s\n%s%d\n%s%d\n%s%d\n", "The event TOOK place that long ago:", "In hours: ", temp_hours, "In minutes:", temp_minutes, "In seconds: ", temp_seconds);

      }

    }

  }while(user_choice != 'q' && user_choice != 'Q');

  
  putchar('\n');
  
  return 0;
}

