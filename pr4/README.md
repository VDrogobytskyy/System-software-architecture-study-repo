Практична робота №4 з дисципліни АСПз Виконано Дрогобицьким Володимиром на мові С, в середовищі UTM Linux ubuntu server
Тема практичної роботи: дослідження роботи malloc

Завдання №1 загальне для усіх(Скриншот завдання):

<img width="880" height="228" alt="Знімок екрана 2026-03-08 о 00 18 13" src="https://github.com/user-attachments/assets/35381322-7ede-41b8-b906-5e2fbe6b636a" />


Відповідь:
Функція malloc приймає аргумент типу size_t, який є беззнаковим 64-бітним цілим числом.
Відповідно, найбільше число, яке можна передати в malloc, становить 2^64 − 1 (мінус один через те, що нуль також враховується). 
Це значення є теоретичним максимумом для параметра, а не реальною кількістю виділюваної пам’яті.

Фактичним обмеженням виступає віртуальний адресний простір процесу. 
На стандартних x86_64 системах використовують 48-бітні адреси, що дає загалом 256 ТБ простору.
Ця область ділиться приблизно навпіл між користувачем і ядром (по 128 ТБ), причому процес може використовувати тільки свою частину.
До цього ще додаються обмеження через стек, пам’ять, виділену через mmap, підключені бібліотеки та інші ресурси. 
Саме таке розділення дозволяє захищати систему від некоректного доступу. 
У нових режимах (LA57) доступно більше бітів адреси, але принцип залишився тим самим.

Крім того, malloc не створює пам’ять “з нічого”.
Він запитує її у ядра за допомогою brk або mmap, і повернуті адреси мають бути канонічними — старші біти повторюють знак молодших бітів, щоб забезпечити коректність адреси.
Таким чином, значення 2^64 − 1 — це лише максимальний можливий аргумент для malloc, а реальна межа виділення визначається доступним віртуальним простором процесу та обмеженнями ядра.

Завдання №2 загальне для усіх(Скриншот завдання):

<img width="877" height="158" alt="Знімок екрана 2026-03-08 о 00 18 44" src="https://github.com/user-attachments/assets/88194438-c9a5-4f83-8fe2-302657093ca1" />

Код представлений у файлі: task4_2.c

Результат виконання:

```bash
./task4

num after xa * xb(9999999 * 1000000000000) = -1253904384
let`s convert this variable into size_t format!
num in size_t: 18446744072455647232
memory allocated fail
```
Завдання №3 загальне для усіх(Скриншот завдання):

<img width="889" height="104" alt="Знімок екрана 2026-03-08 о 00 22 41" src="https://github.com/user-attachments/assets/85ecc8d8-b94d-4ba9-8e55-e145a3c541d0" />

Код представлений у файлі: task4_3.c

Результат виконання:

```bash

 22:29:29  ltrace ./task
__libc_start_main(0xb03cc6830858, 1, 0xfffffb006628, 0 <unfinished ...>
putchar(10, 0xfffffb006628, 0xfffffb006638, 0xb03cc6830858
)          = 10
malloc(0)                                                            = 0xb03cf96bd6b0
puts("malloc(0) returned NOT NULL valu"...malloc(0) returned NOT NULL value!
)                          = 35
free(0xb03cf96bd6b0)                                                 = <void>
putchar(10, 1, 0xb03cf96bd, 0xb03cf96bd010
)                          = 10
__cxa_finalize(0xb03cc6850008, 0xb03cc6830800, 1, 568)               = 1
+++ exited (status 0) +++

```
звідси ми бачимо, що malloc(0) повернув саме адресу памʼятті, а не NULL.


Завдання №4 загальне для усіх(Скриншот завдання):

<img width="843" height="315" alt="Знімок екрана 2026-03-08 о 00 58 10" src="https://github.com/user-attachments/assets/97ba53a3-f177-4aa4-a7e6-086ca99e5432" />

Якщо виконати цей код, отримаєм ось такий вивід:
```bash
./task

On interation: 1 we managed to malloc: 4
free(): double free detected in tcache 2
Aborted (core dumped)

 ltrace ./task
__libc_start_main(0xb7762d120858, 1, 0xffffcbdb00e8, 0 <unfinished ...>
putchar(10, 0xffffcbdb00e8, 0xffffcbdb00f8, 0xb7762d120858
)          = 10
malloc(4)                                                            = 0xb776404dd6b0
printf("%s%d%s%zu\n", "On interation: ", 1, " we managed to malloc: ", 4On interation: 1 we managed to malloc: 4
) = 41
free(0xb776404dd6b0)                                                 = <void>
free(0xb776404dd6b0free(): double free detected in tcache 2
 <no return ...>
--- SIGABRT (Aborted) ---
+++ killed by SIGABRT +++
```

Ми наочно бачимо, що програма намагається звільнити вже раніше виділену пам`ять,
це стається тому що, ми не зануляємо вказівник після виклику для нього free()
Виправимо це і переглянем результат!

Код представлений у файлі task4_4.c

Результат виконання виправленої програми:
 
```bash
./task4

On interation: 1 we managed to malloc: 4
On interation: 2 we managed to malloc: 4
On interation: 3 we managed to malloc: 4

ltrace ./task4
__libc_start_main(0xb28d8d920858, 1, 0xffffd27afec8, 0 <unfinished ...>
putchar(10, 0xffffd27afec8, 0xffffd27afed8, 0xb28d8d920858
) = 10
malloc(4)                                           = 0xb28da1f1c6b0
printf("%s%d%s%zu\n", "On interation: ", 1, " we managed to malloc: ", 4On interation: 1 we managed to malloc: 4
) = 41
free(0)                                             = <void>
malloc(4)                                           = 0xb28da1f1c6d0
printf("%s%d%s%zu\n", "On interation: ", 2, " we managed to malloc: ", 4On interation: 2 we managed to malloc: 4
) = 41
free(0)                                             = <void>
malloc(4)                                           = 0xb28da1f1c6f0
printf("%s%d%s%zu\n", "On interation: ", 3, " we managed to malloc: ", 4On interation: 3 we managed to malloc: 4
) = 41
free(0)                                             = <void>
putchar(10, 0xec3df9d8db50, 0, 0
)                   = 10
__cxa_finalize(0xb28d8d940008, 0xb28d8d920800, 1, 568) = 1
+++ exited (status 0) +++
```
Отже тепер після виправлення цієї проблеми, програма стає робочою, та ми правильно працюєм із памʼяттю!

Завдання №5 загальне для усіх(Скриншот завдання):

<img width="842" height="66" alt="Знімок екрана 2026-03-08 о 00 58 31" src="https://github.com/user-attachments/assets/20e7ed81-0637-4399-a7ff-31e0f4bd4fdb" />

Код представлений у файлі: task4_5.c

Результат виконання:
```bash

memory for void pointer succesfully allocated! ptr adress = 0xb31e8be426b0
realloc fail!
we still can use ptr!
program didn`t finished!

```

Отже якщо realloc() не зможе виділити памʼять воно просто поверне NULL, та програма не впаде,
а до старого вказівника ми досі маємо доступ, та він не "загубився"

Завдання №6 загальне для усіх(Скриншот завдання):

<img width="840" height="63" alt="Знімок екрана 2026-03-08 о 01 42 51" src="https://github.com/user-attachments/assets/a5ce62df-23c6-4fc9-8b74-86dd1a9896f6" />

Код представлений у файлі: task4_6.c

Результат виконання:
```bash

ltrace ./task
__libc_start_main(0xc15fd3d90958, 1, 0xfffffaf596c8, 0 <unfinished ...>
putchar(10, 0xfffffaf596c8, 0xfffffaf596d8, 0xc15fd3d90958
)                      = 10
malloc(8)                                                                        = 0xc15ffc91c6b0
printf("%s%p\n", "memory for void pointer succesfu"..., 0xc15ffc91c6b0memory for void pointer succesfully allocated! ptr adress = 0xc15ffc91c6b0
)          = 75
malloc(16)                                                                       = 0xc15ffc91c6d0
printf("%s%p\n", "confirmed allocation by realloc("..., 0xc15ffc91c6d0confirmed allocation by realloc(NUll) real_mal_ptr = 0xc15ffc91c6d0
)          = 68
realloc(0xc15ffc91c6b0, 0)                                                       = 0
printf("%s%p\n", "after realloc(..., 0) we have pt"..., 0xc15ffc91c6b0after realloc(..., 0) we have ptr = 0xc15ffc91c6b0
)          = 51
puts("but this memory is already free,"...but this memory is already free, so we cannot use it
)                                      = 53
puts("program didn`t finished!"program didn`t finished!
)                                                 = 25
free(0)                                                                          = <void>
putchar(10, 1, 0xfbad2a84, 1
)                                                    = 10
__cxa_finalize(0xc15fd3db0008, 0xc15fd3d90900, 1, 568)                           = 1
+++ exited (status 0) +++
```

Звідси робимо висновок, що realloc(NULL, n) працює як malloc(),
а realloc(..., 0) працює як free()


Завдання №7 загальне для усіх(Скриншот завдання):

<img width="562" height="205" alt="Знімок екрана 2026-03-08 о 01 43 07" src="https://github.com/user-attachments/assets/eac37ee9-6542-4028-8795-f16c682b4f99" />

Код наданий у завданні:
```c

#include <stdio.h>
#include <stdlib.h>

struct sbar {
        float x, y;
};

int main(void){
        putchar('\n');
        struct sbar *ptr, *newptr;

        ptr = calloc(1000, sizeof(struct sbar));

        newptr = realloc(ptr, 500 * sizeof(struct sbar));
        if (newptr == NULL){
                free(ptr);
                return 1;
        }
        ptr = newptr;

        putchar('\n');
        return 0;
}
```
Результат його виконання:
```bash
ltrace ./task
__libc_start_main(0xc18e4f2e0858, 1, 0xffffc0350a68, 0 <unfinished ...>
putchar(10, 0xffffc0350a68, 0xffffc0350a78, 0xc18e4f2e0858
)                      = 10
calloc(1000, 8)                                                                  = 0xc18e5c0a76b0
realloc(0xc18e5c0a76b0, 4000)                                                    = 0xc18e5c0a76b0
putchar(10, 0xc18e5c0a76a0, 0, 0xe2f490490110
)                                   = 10
__cxa_finalize(0xc18e4f300008, 0xc18e4f2e0800, 1, 568)                           = 1
+++ exited (status 0) +++
```

Переписаний варіант представлено у файлі: task4_7.c

Результат його виконання:
```bash
ltrace ./task
__libc_start_main(0xacfe4c6c0858, 1, 0xffffca102818, 0 <unfinished ...>
putchar(10, 0xffffca102818, 0xffffca102828, 0xacfe4c6c0858
)                      = 10
calloc(1000, 8)                                                                  = 0xacfe5a76a6b0
reallocarray(0xacfe5a76a6b0, 500, 8, 0xacfe5a76c580)                             = 0xacfe5a76a6b0
putchar(10, 0xacfe5a76a6a0, 0, 0xe552cc040110
)                                   = 10
__cxa_finalize(0xacfe4c6e0008, 0xacfe4c6c0800, 1, 568)                           = 1
+++ exited (status 0) +++
```

В обох випадках програма спочатку виділяє пам’ять через calloc(1000, 8), а потім зменшує її до 4000 байт:
у першому випадку через realloc, у другому через reallocarray.
Функціонально обидва варіанти виконують однакову операцію, відмінність лише в тому, що reallocarray безпечніший і перевіряє переповнення при множенні розмірів, тоді як realloc такої перевірки не має. 
Програма завершується успішно, викликаючи __cxa_finalize.

Завдання за варіантом №6(Скриншот завдання):

<img width="600" height="49" alt="Знімок екрана 2026-03-08 о 02 05 05" src="https://github.com/user-attachments/assets/4cadbf97-08cc-4d78-ad41-3100cd9ef1e8" />

Код програми представлено у файлі: task_by_var_6.c

Після кожної ітерації програма виводить сповіщення та впадає в "сон", що дає змогу в іншмоу терміналі зручно переглянути всю необхіднк інформацію

Вивід програми:

```bash
./task

Program started. PID: 10917

--- Before allocation ---
grep -E 'VmSize|VmRSS' /proc/10917/status
press ENTER, to continue...

```
```bash
grep -E 'VmSize|VmRSS' /proc/10917/status
VmSize:	    2252 kB
VmRSS:	    1400 kB
```
```bash
--- After malloc (Lazy Allocation) ---
grep -E 'VmSize|VmRSS' /proc/10917/status
press ENTER, to continue...
```
```bash
grep -E 'VmSize|VmRSS' /proc/10917/status
VmSize:	  264400 kB
VmRSS:	    1404 kB
```
```bash
touching pages...

--- After allocation (Physical Allocation) ---
grep -E 'VmSize|VmRSS' /proc/10917/status
press ENTER, to continue...
```
```bash
grep -E 'VmSize|VmRSS' /proc/10917/status
VmSize:	  264400 kB
VmRSS:	  263544 kB
```

У цьому експерименті ми виділили великий обсяг пам’яті (256 МБ) і виміряли параметри VmSize та VmRSS до та після виділення і запису в пам’ять. До виділення пам’яті фізична (VmRSS) і віртуальна (VmSize) пам’ять були мінімальні. Після виклику malloc VmSize збільшилась до розміру виділеної пам’яті, але VmRSS майже не змінилась, що демонструє принцип лінивої алокації (lazy allocation): віртуальна пам’ять резервується, а фізичні сторінки виділяються лише при фактичному записі. Після того, як ми звернулись до кожної сторінки, VmRSS зросла майже до повного розміру виділеної пам’яті, підтверджуючи, що фізичне виділення сталося тільки під час фактичного використання. Таким чином, VmSize відображає всю зарезервовану пам’ять, а VmRSS — реально зайняту фізичну пам’ять, і експеримент наочно ілюструє роботу механізму lazy allocation.
