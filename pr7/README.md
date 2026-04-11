Практична робота №7 з дисципліни АСПз Виконано Дрогобицьким Володимиром на мові С, в середовищі UTM Linux ubuntu server
Тема практичної роботи: Дослідження, моделювання та нестандартні підходи до аналізу процесів, файлових систем, безпеки та ресурсів в Linux.

Завдання №1 загальне для усіх(Скриншот завдання):
<img width="689" height="47" alt="Знімок екрана 2026-04-09 о 20 19 00" src="https://github.com/user-attachments/assets/10341468-100c-4012-b93e-72640aa87154" />

Відопвідь:
В цьому завданні було реалізовано систему через popen(), для передання в потік виводу команди sudo rwho more,
тобто аби отримати вивід в консоль всіх авторизованих користувачів, а more працює як пейджер, тобто не перекидує зразу в кінець,
а виводить максимальну кількість інформації, що влізає в розмір вікна, і пропонує перейти далі, так як у моєму випадку команда rwho видасть лише два рядки, цю команду було викликано та записано результат у змінну storage, а для виводу її було передано 50 разів, місце в коді:
```c
for(int i = 0; i < 50; i++){
  fputs(storage, pipe_out);
}
```
Вивід програми у консоль:

```bash
drogobyt drogserv:tty1  Apr  9 17:00 :25
drogobyt drogserv:pts/0 Apr  9 17:01 :10
drogobyt drogserv:tty1  Apr  9 17:00 :25

.....


drogobyt drogserv:tty1  Apr  9 17:00 :25
drogobyt drogserv:pts/0 Apr  9 17:01 :10
drogobyt drogserv:tty1  Apr  9 17:00 :25
drogobyt drogserv:pts/0 Apr  9 17:01 :10
--More--
```

Завдання №2 загальне для усіх(Скриншот завдання):
<img width="692" height="78" alt="Знімок екрана 2026-04-09 о 20 20 21" src="https://github.com/user-attachments/assets/c9ead34a-4cd1-489b-881e-86b573d1cadc" />

Відопвідь:
Програма імітує команду ls -l, поетапно збираючи дані про кожен об'єкт у папці: спочатку функція opendir відкриває доступ до поточної директорії, після чого цикл readdir по черзі витягує імена всіх наявних файлів, ігноруючи приховані (ті, що починаються з крапки). Для кожного знайденого імені викликається системна функція stat, яка звертається до індексних дескрипторів файлової системи, щоб отримати повне «досьє» файлу (структуру file_stat), що містить його розмір, ідентифікатори власника та бітову маску прав доступу. Далі програма розшифровує ці технічні дані: функція print_permissions за допомогою бітових операцій перетворює маску в рядок rwxrwxrwx, функції getpwuid та getgrgid знаходять у системних базах даних текстові імена користувача і групи замість їхніх цифрових номерів, а strftime перетворює системні секунди останньої зміни файлу на зрозумілу дату. У результаті всі ці підготовлені фрагменти (права, посилання, власник, розмір, дата та ім'я) склеюються в один рядок і виводяться на екран, відтворюючи стандартний вигляд детального списку файлів UNIX.

Вивід в консоль:
Вивід команди ls -l :
```bash
ls -l
total 36
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy     0 Apr  9 17:30 file_created_for_task2_1
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy     0 Apr  9 17:30 file_created_for_task2_2
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy     0 Apr  9 17:30 file_created_for_task2_3
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy     0 Apr  9 17:30 file_created_for_task2_4
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy     0 Apr  9 17:30 file_created_for_task2_5
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy  4715 Apr  9 17:28 README.md
-rwxrwxr-x 1 drogobytskyyy drogobytskyyy 70984 Apr  9 18:00 task2
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy   615 Apr  9 17:26 task7_1.c
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy  1600 Apr  9 18:00 task7_2.c
```
Вивід реалізованої програми:
```bash
./task2

-rwxrwxr-x  1 drogobytskyyy drogobytskyyy    70984 Apr 09 18:00 task2
-rw-rw-r--  1 drogobytskyyy drogobytskyyy        0 Apr 09 17:30 file_created_for_task2_5
-rw-rw-r--  1 drogobytskyyy drogobytskyyy        0 Apr 09 17:30 file_created_for_task2_1
-rw-rw-r--  1 drogobytskyyy drogobytskyyy        0 Apr 09 17:30 file_created_for_task2_2
-rw-rw-r--  1 drogobytskyyy drogobytskyyy      615 Apr 09 17:26 task7_1.c
-rw-rw-r--  1 drogobytskyyy drogobytskyyy     1600 Apr 09 18:00 task7_2.c
-rw-rw-r--  1 drogobytskyyy drogobytskyyy        0 Apr 09 17:30 file_created_for_task2_3
-rw-rw-r--  1 drogobytskyyy drogobytskyyy        0 Apr 09 17:30 file_created_for_task2_4
-rw-rw-r--  1 drogobytskyyy drogobytskyyy     4715 Apr 09 17:28 README.md
```

Завдання №3 загальне для усіх(Скриншот завдання):
<img width="691" height="46" alt="Знімок екрана 2026-04-09 о 20 20 32" src="https://github.com/user-attachments/assets/ee4270d6-69f2-4048-89bb-e9002006c4cd" />

Відповідь:
У даному завданні було створено власну реалізацію команди grep, код програми працює ідентично, відкривається файл для читання, а також приймається на вхід слово яке ми шукаєм результати виконання продемонстровані нижче.

Вивід в консоль:
Оригінальний grep:
```bash
grep apple txt_file_for_task3.txt
There are many apples on the tree, but grep usually looks for exact matches.
pineapple is a different fruit, but it contains the word apple inside.
An apple a day keeps the doctor away.
Last line: just one more apple.
```

Власна реалізація:
```bash
./task3 apple txt_file_for_task3.txt

There are many apples on the tree, but grep usually looks for exact matches.
pineapple is a different fruit, but it contains the word apple inside.
An apple a day keeps the doctor away.
Last line: just one more apple.
```

Завдання №4 загальне для усіх(Скриншот завдання):
<img width="685" height="75" alt="Знімок екрана 2026-04-09 о 20 20 49" src="https://github.com/user-attachments/assets/902cf33b-816d-48e5-8d2b-84f9d8338fd6" />

Відповідь:
У даному завданні було реалізовано власну технологію more, тобто ми читаєм циклом три різні файли, а наша програма встановлює обмеження на вивід в 20 рядків(згідно умові завдання), після чого запитує любий ввід та продовжує роботу.

Вивід в консоль(на виводі --More-- відбувався ввід(Enter)):
```bash
./task4 first_file_for_task4.txt second_file_for_task4.txt third_file_for_task4.txt

01. Kyiv - The capital of Ukraine.
02. Lviv - The cultural heart of the country.
03. Odesa - The pearl by the Black Sea.
04. Dnipro - A powerful industrial center.
05. Kharkiv - A city of students and science.
06. Vinnytsia - Famous for its floating fountains.
07. Chernihiv - One of the oldest cities in Europe.
08. Poltava - Known for its history and dumplings.
09. Ivano-Frankivsk - The gateway to the Carpathians.
10. Ternopil - A peaceful city with a beautiful lake.
11. Lutsk - Home to the Lubart's Castle.
12. Rivne - Famous for the Tunnel of Love nearby.
13. Zhytomyr - The birthplace of space exploration legends.
14. Sumy - A green city in the northeast.
15. Cherkasy - Located on the banks of the Dnipro.
16. Mykolaiv - The city of shipbuilders.
17. Kherson - Known for its steppes and watermelons.
18. Zaporizhzhia - The land of the Cossacks.
19. Uzhhorod - Famous for cherry blossoms in spring.
20. Chernivtsi - The "Little Vienna" of Ukraine.
--More--
21. This is the line after the first pause!
22. You should have pressed Enter to see this.
Row 01: Kernel - The core of the operating system.
Row 02: Shell - The interface between user and kernel.
Row 03: Process - A program in execution.
Row 04: Thread - The smallest unit of processing.
Row 05: Memory - Where data is stored temporarily.
Row 06: Pointer - A variable that stores an address.
Row 07: Buffer - Temporary storage for data transfer.
Row 08: Compiler - Translates code to machine language.
Row 09: Linker - Combines object files into one.
Row 10: Library - A collection of precompiled code.
Row 11: Header - File containing declarations.
Row 12: Struct - A custom data type in C.
Row 13: Array - A collection of similar elements.
Row 14: Loop - Repeated execution of code blocks.
Row 15: Function - A reusable block of code.
Row 16: Variable - A named storage location.
Row 17: Constant - A value that never changes.
Row 18: Syntax - The rules of the language.
--More--
Row 19: Debugger - A tool to find and fix errors.
Row 20: Git - A version control system.
Row 21: New File Start: You reached the end of the second file's first page!
1. "First, solve the problem. Then, write the code."
2. "Experience is the name everyone gives to their mistakes."
3. "In order to be irreplaceable, one must always be different."
4. "Java is to JavaScript what car is to Carpet."
5. "Knowledge is power."
6. "Code is like humor. When you have to explain it, it’s bad."
7. "Fix the cause, not the symptom."
8. "Optimism is a occupational hazard of programming."
9. "Simplicity is the soul of efficiency."
10. "Before software can be reusable it first has to be usable."
11. "Make it work, make it right, make it fast."
12. "Deleted code is debugged code."
13. "Don't repeat yourself (DRY principle)."
14. "Keep it simple, stupid (KISS principle)."
15. "It's not a bug – it's an undocumented feature."
16. "Software is a gas; it expands to fill its container."
17. "The best way to predict the future is to invent it."
--More--
18. "Programs must be written for people to read."
19. "Quality is not an act, it is a habit."
20. "Talk is cheap. Show me the code."
21. "Final line of the test: Everything worked perfectly!"
```

Завдання №5 загальне для усіх(Скриншот завдання):
<img width="682" height="46" alt="Знімок екрана 2026-04-09 о 20 21 01" src="https://github.com/user-attachments/assets/f14e00b7-ec19-475a-85a9-84afafb3024a" />

Відповідь:
У даному завданні ми реалізували програму яка знаходить файл починаючи з поточної директорії формує його повний шлях, та виводить це на екран, якщо в даній директорії знаходяться підкаталоги(папки) функція заходить туди та рекурсивно викликає себе ж, тим самим виводить всі файли з цих підкаталогів. Роботу продемонстровано нижче у вигляді виводу в консоль:

Вивід в консоль:
```bash
./task5

Listing all files starting from current directory:

File: ./second_file_for_task4.txt
File: ./task5
File: ./task7_5.c
File: ./task7_4.c
File: ./task7_1.c
Directory: ./empty_dir
File: ./empty_dir/empty3.txt
File: ./empty_dir/empty1.txt
File: ./empty_dir/empty2.txt
File: ./task7_2.c
File: ./third_file_for_task4.txt
File: ./txt_file_for_task3.txt
Directory: ./empty_dir2
File: ./empty_dir2/empty3.txt
File: ./empty_dir2/empty1.txt
File: ./empty_dir2/empty2.txt
File: ./first_file_for_task4.txt
File: ./task7_3.c
File: ./README.md

```

Завдання №6 загальне для усіх(Скриншот завдання):
<img width="601" height="35" alt="Знімок екрана 2026-04-09 о 20 21 14" src="https://github.com/user-attachments/assets/d14e7628-81f8-4ab4-805a-38175fa91c1f" />

Відповідь:
У даному завданні ми спростили код попереднього завдання, забравши вивід файлів, но добавивши зберігання та сортування назв підкаталогів.

Вивід в консоль:
```bash
./task6

Directory: a
Directory: empty_dir
Directory: empty_dir2
Directory: x
```

Завдання №7 загальне для усіх(Скриншот завдання):
<img width="698" height="70" alt="Знімок екрана 2026-04-09 о 20 21 23" src="https://github.com/user-attachments/assets/399a4756-4e84-4d9d-99de-76927e98aea5" />

Відповідь:
Перш за все нам необхідно виконати команду ls -l *c, щоб отримати поточний стан дозволів для вихідних файлів:

```bash
ls -l *c
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy  615 Apr  9 17:26 task7_1.c
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy 1600 Apr  9 18:03 task7_2.c
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy  596 Apr  9 18:34 task7_3.c
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy  578 Apr  9 20:01 task7_4.c
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy  913 Apr  9 20:11 task7_5.c
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy 1148 Apr  9 20:29 task7_6.c
```

Так як ми бачимо вкінці r-- це означає, що права начитання і так за замовчуванням, надані іншим користувачам, для наглядності виконання даного завдання, заберемо ці права командою chmod o-r task7_*.c, та продемонструєм зміни у правах доступу тою ж командою ls -l *c:
```bash
ls -l *c
-rw-rw---- 1 drogobytskyyy drogobytskyyy  615 Apr  9 17:26 task7_1.c
-rw-rw---- 1 drogobytskyyy drogobytskyyy 1600 Apr  9 18:03 task7_2.c
-rw-rw---- 1 drogobytskyyy drogobytskyyy  596 Apr  9 18:34 task7_3.c
-rw-rw---- 1 drogobytskyyy drogobytskyyy  578 Apr  9 20:01 task7_4.c
-rw-rw---- 1 drogobytskyyy drogobytskyyy  913 Apr  9 20:11 task7_5.c
-rw-rw---- 1 drogobytskyyy drogobytskyyy 1148 Apr  9 20:29 task7_6.c
```
Запустимо нашу програму та в хаотичному порядку будем надавати права на читання для кожного файлу:
```bash
./task7
File founded: task7_6.c
Give other users read permission? (y/n): y
Successful: Permission granted.

File founded: task7_5.c
Give other users read permission? (y/n): y
Successful: Permission granted.

File founded: task7_4.c
Give other users read permission? (y/n): y
Successful: Permission granted.

File founded: task7_1.c
Give other users read permission? (y/n): n
Canceled.

File founded: task7_2.c
Give other users read permission? (y/n): n
Canceled.

File founded: task7_7.c
Give other users read permission? (y/n): y
Successful: Permission granted.

File founded: task7_3.c
Give other users read permission? (y/n): n
Canceled.
```
Як результат виконання виконаєм команду ls -l *c, та переконаємось що відповідним файлам, надані відповідні првав:

```bash
ls -l *c
-rw-rw---- 1 drogobytskyyy drogobytskyyy  615 Apr  9 17:26 task7_1.c
-rw-rw---- 1 drogobytskyyy drogobytskyyy 1600 Apr  9 18:03 task7_2.c
-rw-rw---- 1 drogobytskyyy drogobytskyyy  596 Apr  9 18:34 task7_3.c
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy  578 Apr  9 20:01 task7_4.c
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy  913 Apr  9 20:11 task7_5.c
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy 1148 Apr  9 20:29 task7_6.c
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy 1333 Apr  9 22:28 task7_7.c
```

Завдання №8 загальне для усіх(Скриншот завдання):
<img width="692" height="73" alt="Знімок екрана 2026-04-09 о 20 21 36" src="https://github.com/user-attachments/assets/c74638bb-5fc2-4f99-ae48-ef1764ebaef1" />

Відповідь:
У даному завданні наша програма уникає каталогів та працює лише для файлів у директорії, проходячись по кожному та запитуючи, чи варто його видалити, для наглядності роботи програми спочатку виконаєм команду ls та побачим, наявність файлу file_to_delete.txt:
```bash
ls
a                          task7_1.c  task7_8.c
empty_dir                  task7_2.c  task8
empty_dir2                 task7_3.c  third_file_for_task4.txt
file_to_delete.txt         task7_4.c  txt_file_for_task3.txt
first_file_for_task4.txt   task7_5.c  x
README.md                  task7_6.c
second_file_for_task4.txt  task7_7.c
```
Тепер виконаєм програму:
```bash
./task8

Delete file 'task7_6.c'? (y/n): n
Skipped.
Delete file 'second_file_for_task4.txt'? (y/n): n
Skipped.
Delete file 'task7_8.c'? (y/n): n
Skipped.
Delete file 'task7_5.c'? (y/n): n
Skipped.
Delete file 'task7_4.c'? (y/n): n
Skipped.
Delete file 'file_to_delete.txt'? (y/n): y
File 'file_to_delete.txt' successfully deleted.

....

Delete file '.gitignore'? (y/n): n
Skipped.
Delete file 'README.md'? (y/n): n
Skipped.
```

Видаляємо тільки наперед підготовлений для цього файл, інші не рухаєм, продемонструєм результат виконання командою ls:
```bash
ls
a                          task7_1.c  task7_7.c
empty_dir                  task7_2.c  task7_8.c
empty_dir2                 task7_3.c  task8
first_file_for_task4.txt   task7_4.c  third_file_for_task4.txt
README.md                  task7_5.c  txt_file_for_task3.txt
second_file_for_task4.txt  task7_6.c  x
```

Завдання №9 загальне для усіх(Скриншот завдання):
<img width="659" height="45" alt="Знімок екрана 2026-04-09 о 20 21 49" src="https://github.com/user-attachments/assets/f6781385-415d-4cf5-9d11-e45f67e7cdc4" />

Завдання №10 загальне для усіх(Скриншот завдання):
<img width="696" height="187" alt="Знімок екрана 2026-04-09 о 20 22 03" src="https://github.com/user-attachments/assets/aa732e48-4012-495f-b41d-8a702ec0bffc" />

Завдання за варіантом №6(Скриншот завдання):
<img width="676" height="63" alt="Знімок екрана 2026-04-09 о 20 22 15" src="https://github.com/user-attachments/assets/19246cd4-8608-4091-a61e-a3366d9a47de" />

