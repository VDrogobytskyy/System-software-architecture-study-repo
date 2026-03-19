Практична робота №6 з дисципліни АСПз Виконано Дрогобицьким Володимиром на мові С, в середовищі UTM Linux ubuntu server 
Тема практичної роботи: Інструменти налагодження для проблем з памʼяттю.

Завдання за варіантом №6:

***Створити бібліотеку з LD_PRELOAD, яка перехоплює виклик open() і логгує його параметри, та порівняти підхід із використанням strace.***


Для виконання даної Лабораторної роботи було створено власну бібліотеку, представлену у файлі own_open_lib.c
Суть коду цього файлу полягає в наступному:
Ми перехоплюєм виклик функції open, за рахунок того що, перевизначаємо її у своїй бібліотеці.
Даний файл компілюється спеціальною командою, а саме: 
```bash
gcc -shared -fPIC own_open_lib.c -o my_lib.so -ldl
```
Після цього отримавши файл my_lib.so
Ми можемо перевірити як це працює, для цього спочатку просто скомпілюєм та виконаєм файл pr6.c:

```bash
gcc -Wall pr6.c -o pr6

./pr6


```
Даний файл за замовчуванням нічого не виводить так як виконує базову функцію open в якій не передбачено логування.

Тепер продемонструємо роботу нашого коду, запустимо цей же файл, но за допомогою LD_PRELOAD, заставимо використати нашу динамічну бібліотеку,
та перехопити виклик open();
Вивід:

```bash
LD_PRELOAD=./my_lib.so ./pr6

Open func was hooked. We will have logging from own LIB.
On time: Thu Mar 19 20:11:49 2026
file was opened by path: test1.txt
Open func was hooked. We will have logging from own LIB.
On time: Thu Mar 19 20:11:49 2026
file was opened by path: test2.txt
We used this flag: 644

```

Як ми можемо бачити, все працює відмінно, виклик open(), успішно перехоплюється та логується(у даному випадку просто в консоль).
Таким чином було організовано свою динамічну бібліотеку та продемонстровано варіант перехоплення вже визначених функцій, та виконання логування.


***Тепер порівняємо цей підхід з використанням strace***

Продемонструємо вивід strace ./pr6:
```bash
strace ./pr6
execve("./pr6", ["./pr6"], 0xffffd9030c30 /* 34 vars */) = 0
brk(NULL)                               = 0xca4298aa2000
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0xf6eaac129000
faccessat(AT_FDCWD, "/etc/ld.so.preload", R_OK) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
fstat(3, {st_mode=S_IFREG|0644, st_size=31527, ...}) = 0
mmap(NULL, 31527, PROT_READ, MAP_PRIVATE, 3, 0) = 0xf6eaac121000
close(3)                                = 0
openat(AT_FDCWD, "/lib/aarch64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0\267\0\1\0\0\0\360\206\2\0\0\0\0\0"..., 832) = 832
fstat(3, {st_mode=S_IFREG|0755, st_size=1722920, ...}) = 0
mmap(NULL, 1892240, PROT_NONE, MAP_PRIVATE|MAP_ANONYMOUS|MAP_DENYWRITE, -1, 0) = 0xf6eaabf22000
mmap(0xf6eaabf30000, 1826704, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0) = 0xf6eaabf30000
munmap(0xf6eaabf22000, 57344)           = 0
munmap(0xf6eaac0ee000, 8080)            = 0
mprotect(0xf6eaac0ca000, 77824, PROT_NONE) = 0
mmap(0xf6eaac0dd000, 20480, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x19d000) = 0xf6eaac0dd000
mmap(0xf6eaac0e2000, 49040, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0xf6eaac0e2000
close(3)                                = 0
set_tid_address(0xf6eaac129f90)         = 2423
set_robust_list(0xf6eaac129fa0, 24)     = 0
rseq(0xf6eaac12a5e0, 0x20, 0, 0xd428bc00) = 0
mprotect(0xf6eaac0dd000, 12288, PROT_READ) = 0
mprotect(0xca429825f000, 4096, PROT_READ) = 0
mprotect(0xf6eaac12e000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0xf6eaac121000, 31527)           = 0
fstat(1, {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}) = 0
getrandom("\xf0\xf8\x0f\xe1\x52\x91\x73\x7f", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0xca4298aa2000
brk(0xca4298ac3000)                     = 0xca4298ac3000
write(1, "\n", 1
)                       = 1
openat(AT_FDCWD, "test1.txt", O_RDONLY) = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "test2.txt", O_WRONLY|O_CREAT, 0644) = 3
close(3)                                = 0
write(1, "\n", 1
)                       = 1
exit_group(0)                           = ?
+++ exited with 0 +++
```
У цьому виводі видно, що програма спочатку намагається відкрити файл test1.txt, але він відсутній (ENOENT), а потім створює файл test2.txt з правами доступу 0644 і отримує файловий дескриптор 3. Інші записи (mmap, brk, fstat, read, close) показують стандартну роботу бібліотек та завантаження ресурсів у пам’ять.

Порівняно з підходом LD_PRELOAD, який дозволяє перехоплювати виклики функцій у бібліотеках і логувати параметри, strace лише спостерігає системні виклики на рівні ядра і не змінює поведінку програми. Використання LD_PRELOAD дозволяє бачити додаткові параметри, такі як час виклику і права доступу при створенні файлу, а також при необхідності модифікувати виклик. Strace дає більш детальну інформацію про всі системні виклики, але не дозволяє змінювати їхню поведінку. Обидва підходи разом дають повне уявлення про роботу програми і допомагають порівняти user-space логування та kernel-space моніторинг.


