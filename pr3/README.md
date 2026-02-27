Практична робота №3 з дисципліни АСПз Виконано Дрогобицьким Володимиром на мові С, в середовищі UTM Linux ubuntu server
Тема практичної роботи: Дослідження обмежень ресурсів у середовищі Docker

Завдання №1 загальне для усіх(Скриншот завдання):
<img width="619" height="351" alt="Знімок екрана 2026-02-26 о 21 48 46" src="https://github.com/user-attachments/assets/e8377069-7844-4dd9-8390-646389c6a0dd" />

docker run -it --name lab3-container ubuntu:22.04 bash - Виконаєм дану команду, щоб створити контейнер Docker.
Та введемо всі необхідні команди:
<img width="1280" height="967" alt="image" src="https://github.com/user-attachments/assets/152d8281-4687-44f8-a7a4-af0397103894" />

як ми можемо спостерігати, в даному випадку при введені команди ulimit -n <число> ми змінюємо одразу і Soft i Hard обмеження,
що є типовим для даного середовища, проте пізніше зменшивши його ми не можем його збільшити бо діє правило Soft limit <= Hard limit

Проте, якщо ми увійдемо в новий контейнер з специфікатором "привілегійований", 
за допомогою команди: sudo docker run -it --privileged --name lab3-priv ubuntu:22.04 bash
ми отримаємо необхідні права доступу та зможемо виконати зміну даних лімітів, приклад на скріншоті:

<img width="1015" height="1280" alt="image" src="https://github.com/user-attachments/assets/96c36eb0-fc36-4a74-8fd2-3c7496b7d2fc" />

Завдання №2 загальне для усіх(Скриншот завдання):
<img width="616" height="56" alt="Знімок екрана 2026-02-26 о 22 24 38" src="https://github.com/user-attachments/assets/91c274cd-6fec-4e64-91e9-29ab918c355b" />

Для початку запустимо дану програму без специфікаторів:

<img width="1280" height="378" alt="image" src="https://github.com/user-attachments/assets/3b681d52-172e-41a2-a4d2-aed29f23d05f" />

Тепер поексперемнтуємо, і замість ./task3_2 виконаємо команду perf trace ./task3_2 отримуємо такий результат:
<img width="1280" height="1248" alt="image" src="https://github.com/user-attachments/assets/e054eb58-9b62-44aa-ac30-1b02596a5454" />
<img width="1280" height="159" alt="image" src="https://github.com/user-attachments/assets/b9eec26b-19c2-4b91-9196-1209387ba284" />

звідси видно, що файли починають заповнювати ліміт не з 1 а з показника 4, так як по замовчуванню відкриваються ще файли для роботи з вводом ти виводом,
можемо чітко побачити та зрозуміти на якому етапі програма падає, та що слугує цьому.
ВАЖЛИВО, perf... працюватиме лише при наявності специфікатора --privileged у контейнера!!!

Завдання №3 загальне для усіх(Скриншот завдання):
<img width="648" height="72" alt="Знімок екрана 2026-02-26 о 22 30 15" src="https://github.com/user-attachments/assets/7ac285be-b988-45f1-a0c3-dd946fe5043e" />

Код програми:
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

void dice_roll(FILE *f){

    srand(time(NULL));
    int count = 0;

    printf("%s\n", "Program starts, trying to do 100,000 rolls");

    while (1) {
        int random_roll = (rand() % 6) + 1;
        if (fprintf(f, "%d\n", random_roll) < 0) {
            fprintf(stderr, "\nfprintf ERROR: %s\n", strerror(errno));
            return;
        }

        if (fflush(f) != 0) {
            if (errno == EFBIG) { // EFBIG - File too large
                fprintf(stderr, "\nATTENTION Max file size reached!\n");
            } else {
                fprintf(stderr, "\nfprintf ERROR: %s\n", strerror(errno));
            }
            return;
        }

        count++;
        if (count >= 100000) {
            printf("\n100,000 rolls completed!\n");
            return;
        }

        if (count % 100 == 0) printf("\rWrote: %d", count);
    }    
}

int main(void){
        signal(SIGXFSZ, SIG_IGN);
        putchar('\n');
        FILE *f = fopen("dice_roll.txt", "w+");

        if (!f) {
                fprintf(stderr, "Error can`t open dice_roll.txt file: %s\n", strerror(errno));
                exit(1);
        }

        dice_roll(f);

        fclose(f);
        putchar('\n');
        printf("\nProgram finished.\n");
        return 0;
}

```
Результат виконання програми:
<img width="438" height="204" alt="Знімок екрана 2026-02-26 о 23 11 39" src="https://github.com/user-attachments/assets/af13477d-66a5-4395-9829-5af447466a6c" />

Дана програма коректно завершується завдяки умові: if (errno == EFBIG), тобто якщо ми ловимо помилку переповнення допустимого розміру файлу,
а також у файлі: task3_3.c перша строка в функції main: signal(SIGXFSZ, SIG_IGN); яка говорить програмі ігнорувати сигнал про переповнення 
допустимого розміру файлу, без неї отримуючи цей сигнал програма буде крашитись.

Завдання №4 загальне для усіх(Скриншот завдання):
<img width="632" height="91" alt="Знімок екрана 2026-02-26 о 23 16 37" src="https://github.com/user-attachments/assets/316567ac-7c6f-4ddd-a1e0-1bf8c4b384cc" />

Код програми:
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>

void gamble_func(int *ar, int amount, int max_value){
        int counter = 0;
        for(int i = 0; i < amount; i++){
                int rand_number = (rand() % max_value) + 1;
                ar[counter] = rand_number;
                counter++;
        }
}

void line_drower(int amount){
        for(int i = 0; i <= amount; i++){
                putchar('-');
        }
        putchar('\n');
}

void cpu_limit_handler(int signal){
        if(signal == SIGXCPU){
                fprintf(stderr, "CPU TIME LIMIT REACHED\n");
                exit(0);
        }
}

int main(void){
        signal(SIGXCPU, cpu_limit_handler);
        putchar('\n');
        srand(time(NULL));
        int array_sixth[6] = {0};
        int array_seventh[7] = {0};

        int counter = 0;
        while(1){
                gamble_func(array_sixth, 6, 36);
                gamble_func(array_seventh, 7, 49);

                line_drower(22);
                printf("%s\n", "6 numbers with high 36:");
                for(int i = 0; i < 6; i++){
                        printf("%d%c", array_sixth[i], ' ');
                }

                putchar('\n');
                line_drower(22);
                fflush(stdout);
                printf("%s\n", "7 numbers with high 49:");

                for(int i = 0; i < 7; i++){
                        printf("%d%c", array_seventh[i], ' ');
                }
                putchar('\n');
                fflush(stdout);
                counter++;
                if(counter == 10000000){
                        printf("%s\n", "Program created 10,000,000 combinations!");
                        break;
                }
        }

        putchar('\n');
        return 0;
}

```
Виконаємо дві команди для встановлення Soft та Hard лімітів по часу роботи процесора:

<img width="474" height="103" alt="Знімок екрана 2026-02-27 о 00 10 59" src="https://github.com/user-attachments/assets/308cb837-da9d-49e6-88dd-41f3412398fc" />

Ми отримуємо сигнал від програми а саме SIGXCPU, і правильно обробляєм його, результат виконання:
<img width="254" height="448" alt="Знімок екрана 2026-02-27 о 00 20 28" src="https://github.com/user-attachments/assets/96815bf1-e761-4d2f-a154-855a443f015d" />

Ми отримуємо вивід після виводу повідомлення: CPU TIME LIMIT REACHED тому що stderr виводиться миттєво при отриманні сигналу,
а після exit(0), буфер скидається тобто виводить все, що в ньому залишилось.

Завдання №5 загальне для усіх(Скриншот завдання):

<img width="624" height="51" alt="Знімок екрана 2026-02-27 о 00 25 18" src="https://github.com/user-attachments/assets/61ad0496-8aff-424b-9626-7f7fe51ce5b2" />
<img width="615" height="178" alt="Знімок екрана 2026-02-27 о 00 25 35" src="https://github.com/user-attachments/assets/6ede4d61-b182-41e9-a884-e7327be7b558" />

Код програми:
```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void read_and_write_func(FILE *f_to_read, FILE *f_to_write){
        char buffer[100];

        while(fgets(buffer, sizeof(buffer), f_to_read) != NULL){
                fputs(buffer, f_to_write);
        }
}

void file_size_handler(int signal){
        if(signal == SIGXFSZ){
                fprintf(stderr, "File max size reached!\n");
                exit(0);
        }
}

int main(int argc, char *argv[]){
        signal(SIGXFSZ, file_size_handler);
        putchar('\n');
        if(argc != 3){
                fprintf(stderr, "Program need two arguments\n");
                exit(1);
        }

        FILE *rF = fopen("doc_to_read.txt", "r");
        if(!rF){
                fprintf(stderr, "doc_to_read.txt cannot be opened\n");
                exit(1);
        }

        FILE *wF = fopen("doc_to_write.txt", "w");
        if(!wF){
                fprintf(stderr, "doc_to_write.txt cannot be opened\n");
                exit(1);
        }

        read_and_write_func(rF, wF);

        fclose(rF);
        fclose(wF);
        printf("%s\n", "Program finished!");

        putchar('\n');
        return 0;
}
```
Результат виконання з обмеженнням ulimit -f 8 а також обробкою сигналу який повертає програма при досягненні максимального розміру файлу:

<img width="641" height="169" alt="Знімок екрана 2026-02-27 о 01 24 10" src="https://github.com/user-attachments/assets/53c71489-123f-4602-897e-f6f34921d721" />

Завдання №6 загальне для усіх(Скриншот завдання):

<img width="694" height="50" alt="Знімок екрана 2026-02-27 о 01 25 20" src="https://github.com/user-attachments/assets/d1f43508-cf76-4cf8-8b35-a4ddca14c89d" />

Код програми:

```c
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
```
Результат виконання:

<img width="406" height="132" alt="Знімок екрана 2026-02-27 о 01 36 53" src="https://github.com/user-attachments/assets/4a5d6de4-b50b-4ed5-9c92-bc8fe51d7598" />

Встановлюємо обмеження на використання стеку за допомогою ulimit -Hs 8192, а потім створюєм величезний масив прямо у стеку.

Завдання за варіантом №6(Скриншот завдання):

<img width="561" height="29" alt="Знімок екрана 2026-02-27 о 01 38 45" src="https://github.com/user-attachments/assets/6766f091-4656-484a-a51e-4fe9d18e4da1" />

Код програми:

```c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>

int main(void){
        putchar('\n');

        size_t large_storage = 5 * 1024 * 1024; // 5 Mb
        void *ptr = malloc(large_storage);

        if(!ptr){
                fprintf(stderr, "Oops memory allocation error!\n");
                exit(0);
        }

        printf("%s\n", "We succesfully allocated 5 Mb of memory!");

        if(mlock(ptr, large_storage) == 0){
                printf("%s\n", "Everything worked, we locked memory in RAM, and it will never be placed in SWAP(HD)");
        }else{
                fprintf(stderr, "\nSomething went wrong :\\ Error: %s\n", strerror(errno));
        }

        free(ptr);

        putchar('\n');
        return 0;
}
```
Тепер проведемо тест:
<img width="1280" height="591" alt="image" src="https://github.com/user-attachments/assets/db613d45-2f7d-476c-b6bd-2afc3a5a1c81" />

як ми можемо бачити хоть ми і "прикріплюємо" виділену памʼять за допомогою mlock(), але маючи root права, система ігнорує обмеження ulimit -l
Тож створимо нового користувача та дамо йому дуже нильке обмеження по памʼятті за допомогою команд:

```bash
useradd -m not_root
su not_root
ulimit -l 1
```

Результат виконання:

<img width="508" height="156" alt="Знімок екрана 2026-02-27 о 02 19 25" src="https://github.com/user-attachments/assets/524218e6-114a-4b80-b46f-748dc9932518" />

Отримали повідомлення про помилку "прикріплення" памʼятті.
Таким чином ми проаналізували та продемонстрували роботу ulimit -l в середовищі Docker.
