Практична робота №9 з дисципліни АСПз Виконано Дрогобицьким Володимиром, в середовищі UTM Linux ubuntu server 
Тема практичної роботи: bash - скрипти

***Загальна інформація***

Всі скрипти пишуть у файлах формату .sh, після чого виконується команда shc -f, завдяки чому створюються два нових файли,
з розширеннями .x та .x.c, надалі файли розширення .x.c будуть видалятись, під час лабороторної використовуватимо 3 додадктових тестових користувача. Запуск програми відбувається за допомогою команди:
```bash
./my_script.sh.x
```

Завдання №1 загальне для усіх(Скриншот завдання):
<img width="593" height="81" alt="Знімок екрана 2026-04-22 о 00 44 58" src="https://github.com/user-attachments/assets/4cb4a4bc-d3c7-43a1-91c9-0c13e5c2f566" />

Відповідь:
На моєму дестрибутиві сторонні користувачі мають UID > 1000, що і видно з виводу.

Вивід в консоль:
```bash
./task9_1.sh.x

looking for different users except drogobytskyyy

User found: test_user1 (UID: 1001)
User found: test_user2 (UID: 1002)
User found: test_user3 (UID: 1003)

```

Завдання №2 загальне для усіх(Скриншот завдання):
<img width="592" height="83" alt="Знімок екрана 2026-04-22 о 00 45 12" src="https://github.com/user-attachments/assets/bbc84914-ff10-424e-8af0-efb76f9673e5" />

Відповідь:
Ми використовуємо sudo cat, щоб виконати це з правами адміністратора, після чого вводимо пароль(перший раз), та бачиво необхідний вивід.

Вивід в консоль:
```bash
./task9_2.sh.x

Try to read /etc/shadow like admin.

[sudo] password for drogobytskyyy:
root:*:20306:0:99999:7:::
daemon:*:20306:0:99999:7:::
bin:*:20306:0:99999:7:::
sys:*:20306:0:99999:7:::
sync:*:20306:0:99999:7:::
games:*:20306:0:99999:7:::
man:*:20306:0:99999:7:::
lp:*:20306:0:99999:7:::
mail:*:20306:0:99999:7:::
news:*:20306:0:99999:7:::
uucp:*:20306:0:99999:7:::
proxy:*:20306:0:99999:7:::
www-data:*:20306:0:99999:7:::
backup:*:20306:0:99999:7:::
list:*:20306:0:99999:7:::
irc:*:20306:0:99999:7:::
_apt:*:20306:0:99999:7:::
nobody:*:20306:0:99999:7:::
systemd-network:!*:20306::::::
systemd-timesync:!*:20306::::::
dhcpcd:!:20306::::::
messagebus:!:20306::::::
systemd-resolve:!*:20306::::::
pollinate:!:20306::::::
polkitd:!*:20306::::::
syslog:!:20306::::::
uuidd:!:20306::::::
tcpdump:!:20306::::::
landscape:!:20306::::::
fwupd-refresh:!*:20306::::::
drogobytskyyy:$6$HrgO29DLZ4/.6Adm$9i5RbfVTj1SftbOai4qfL5gG1YghF4N7f6NVxKEg1Npe520OySPn.YVGnEbHaaapklaHJRdxVZeeN.w3pHO4a0:20493:0:99999:7:::
sshd:!:20493::::::
dnsmasq:!:20509::::::
rwhod:!:20552::::::
test_user1:$y$j9T$qAERoX06DZ0XdQwLXbnw0.$Yg4V3ZzV7sDRuSZfsMAk3TV8lp5UA8HWALZBWwx6B2.:20564:0:99999:7:::
test_user2:$y$j9T$HFCZ984JLYCJudDpL7BkE.$2G7qsJkDd6gfkHVbjctFibtNFTxgMuaV9Iur0sTP3AB:20564:0:99999:7:::
test_user3:$y$j9T$JyAqXNW27iETLrTkm3xs4/$riwS7RdLlT4JTljDegrQfB9DeHD5nKw1owkzyLaUj/4:20564:0:99999:7:::
Success: File /etc/shadow accessed successfully.
```

Завдання №3 загальне для усіх(Скриншот завдання):
<img width="601" height="139" alt="Знімок екрана 2026-04-22 о 00 45 26" src="https://github.com/user-attachments/assets/18bed6ca-c11f-443c-ac4e-2d99aef172b5" />

Відповідь:
Відповідь на дане завдання цілком і повністю демонструє вивід.

***ЗАУВАЖЕННЯ***

для коректної роботи програми, та отримування очікуваного результату в коді ми використовуєм команду: sudo -u "$USER", адже на сучасному дестрибутиві Linux, права root після надання їх через sudo + password, застосовуються для всієї цепочки виконання.

Вивід в консоль:
```bash
./task9_3.sh.x
Creating a file as drogobytskyyy...
-rw-rw-r-- 1 drogobytskyyy drogobytskyyy 18 Apr 21 22:16 ordinary_file.txt

Copying to home folder as ROOT...
[sudo] password for drogobytskyyy:
-rw-r--r-- 1 root root 18 Apr 21 22:16 /home/drogobytskyyy/root_owned.txt

Trying to modify the file...
Result: Access denied. I cannot edit root's file.

Trying to delete the file...

Result: Success! The file was deleted.
Explanation: I can delete it because I own the directory.
```

Завдання №4 загальне для усіх(Скриншот завдання):
<img width="589" height="29" alt="Знімок екрана 2026-04-22 о 00 45 37" src="https://github.com/user-attachments/assets/c3627548-1804-4e42-8b9e-c2b4ff974fa4" />
<img width="584" height="66" alt="Знімок екрана 2026-04-22 о 00 45 48" src="https://github.com/user-attachments/assets/724b49d0-1791-4e9c-85f9-5ed796a5031f" />

Відповідь:
Даний скрипт почергово виконує команди whoami та id, для отримання очікуваного завданням виводу, також після цього виконується команда
id -Gn, аби прибрати всі технічні цифри та отримати читабельний вивід принадлежності користувача до різних груп.

Вивід в консоль:
```bash
./task9_4.sh.x
Current user identity:
drogobytskyyy

Full account details (UID, GID, and Groups):
uid=1000(drogobytskyyy) gid=1000(drogobytskyyy) groups=1000(drogobytskyyy),4(adm),24(cdrom),27(sudo),30(dip),46(plugdev),101(lxd)

List of all groups you belong to:
drogobytskyyy adm cdrom sudo dip plugdev lxd

Summary:
User drogobytskyyy is currently active and belongs to 7 groups.
```

Завдання №5 загальне для усіх(Скриншот завдання):
<img width="607" height="100" alt="Знімок екрана 2026-04-22 о 00 46 04" src="https://github.com/user-attachments/assets/b5470c7a-2c0e-4b34-8269-5a5fb4eacba0" />


Завдання №6 загальне для усіх(Скриншот завдання):
<img width="603" height="103" alt="Знімок екрана 2026-04-22 о 00 46 16" src="https://github.com/user-attachments/assets/ef4366fc-90f0-4e58-a128-f342d1e7f47b" />



Завдання за варіантом №6(Скриншот завдання):
<img width="521" height="46" alt="Знімок екрана 2026-04-22 о 00 46 54" src="https://github.com/user-attachments/assets/040f7633-ae35-490a-89fc-7d7b3e35ad20" />


