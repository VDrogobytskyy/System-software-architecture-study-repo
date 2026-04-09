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

Завдання №5 загальне для усіх(Скриншот завдання):
<img width="682" height="46" alt="Знімок екрана 2026-04-09 о 20 21 01" src="https://github.com/user-attachments/assets/f14e00b7-ec19-475a-85a9-84afafb3024a" />

Завдання №6 загальне для усіх(Скриншот завдання):
<img width="601" height="35" alt="Знімок екрана 2026-04-09 о 20 21 14" src="https://github.com/user-attachments/assets/d14e7628-81f8-4ab4-805a-38175fa91c1f" />

Завдання №7 загальне для усіх(Скриншот завдання):
<img width="698" height="70" alt="Знімок екрана 2026-04-09 о 20 21 23" src="https://github.com/user-attachments/assets/399a4756-4e84-4d9d-99de-76927e98aea5" />

Завдання №8 загальне для усіх(Скриншот завдання):
<img width="692" height="73" alt="Знімок екрана 2026-04-09 о 20 21 36" src="https://github.com/user-attachments/assets/c74638bb-5fc2-4f99-ae48-ef1764ebaef1" />

Завдання №9 загальне для усіх(Скриншот завдання):
<img width="659" height="45" alt="Знімок екрана 2026-04-09 о 20 21 49" src="https://github.com/user-attachments/assets/f6781385-415d-4cf5-9d11-e45f67e7cdc4" />

Завдання №10 загальне для усіх(Скриншот завдання):
<img width="696" height="187" alt="Знімок екрана 2026-04-09 о 20 22 03" src="https://github.com/user-attachments/assets/aa732e48-4012-495f-b41d-8a702ec0bffc" />

Завдання за варіантом №6(Скриншот завдання):
<img width="676" height="63" alt="Знімок екрана 2026-04-09 о 20 22 15" src="https://github.com/user-attachments/assets/19246cd4-8608-4091-a61e-a3366d9a47de" />

