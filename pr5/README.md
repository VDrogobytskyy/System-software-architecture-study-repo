Практична робота №5 з дисципліни АСПз Виконано Дрогобицьким Володимиром на мові С, в середовищі UTM Linux ubuntu server 
Тема практичної роботи: Помилки роботи з пам’яттю в Linux та засоби їх усунення.

Завдання за варіантом №6(Скриншот завдання):


Для виконання даного завдання було організовано два різні файли мовою С.
У першому який має назву pr5.c
Наведено приклад коли великий блок памʼяті все ж таки виділяється, але це фрагментація всерівно відбувається:

Вивід програми pr5.c:

```bash
Let`s check stats before program start!
Arena 0:
system bytes     =     135168
in use bytes     =       1696
Total (incl. mmap):
system bytes     =     135168
in use bytes     =       1696
max mmap regions =          0
max mmap bytes   =          0

stats after allocation: 10000blocks!
Arena 0:
system bytes     =    1486848
in use bytes     =    1441696
Total (incl. mmap):
system bytes     =    1486848
in use bytes     =    1441696
max mmap regions =          0
max mmap bytes   =          0

stats after freeing every second block:
Arena 0:
system bytes     =    1486848
in use bytes     =     722704
Total (incl. mmap):
system bytes     =    1486848
in use bytes     =     722704
max mmap regions =          0
max mmap bytes   =          0

big memory block allocation success!
stats after trying of allocation big block:
free memory in fragments (fordblks): 751328 bites:
memory get from system: 1486848 bites

```

Пояснення, ми виділяємо памʼять маленькими блоками, а після цього звільняємо кожен другий блок для отримання фрагментації,
но сучасні linux системи зокрема glibc є достатньо розумними, та при таких випадках просто просить додаткову памʼять у системи,
проте це не змінює того факту що фрагментація відбувається, адже тепер у нас є блоки памʼяті які вже не використаєш.

Для того аби повність задовільнити умову завдання, було також організовано другий файл під назвою pr5_failed.c
Пояснення:
У сучасних системах дуже складно справді "вбити" систему таким чином, тому що вони є неймовірно оптимізованими,
тому було прийнято рішення штучно обмежити ресурси для виконання, за допомогою наступних рядків:
```c
rl.rlim_cur = 4 * 1024 * 1024; 
rl.rlim_max = 4 * 1024 * 1024;
```
Після застосування даного обмеження, ми можемо наочно побачити, що через фрагментацію не виходить виділити памʼять, хотя її достатньо.
Демонстрація виводу:

```bash
Initial state
Arena 0:
system bytes     =     135168
in use bytes     =       1696
Total (incl. mmap):
system bytes     =     135168
in use bytes     =       1696
max mmap regions =          0
max mmap bytes   =          0

State after creating holes (FRAGMENTATION)
Total free memory (fordblks): 764144 bytes
Arena 0:
system bytes     =    1486848
in use bytes     =     722704
Total (incl. mmap):
system bytes     =    1486848
in use bytes     =     722704
max mmap regions =          0
max mmap bytes   =          0

Trying to allocate contiguous block: 3145728 bytes...
!!! RESULT: malloc returned NULL (Allocation Failed) !!!
Total free memory (764144) was enough for the request (3145728), but it is fragmented.
```
Отже таким чином, ми дослідили проблему з фрагментацією памʼяті, та глибше зрозуміли як працювати з нею у системах linux


