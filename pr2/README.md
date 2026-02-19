Практична робота №2 з дисципліни АСПз
Виконано Дрогобицьким Володимиром на мові С, в середовищі UTM Linux ubuntu server

Завдання №1 загальне для усіх(Скриншот завдання):
<img width="684" height="104" alt="Знімок екрана 2026-02-19 о 22 10 08" src="https://github.com/user-attachments/assets/af6e5a7e-96ac-428f-a8a8-2d07988f6fec" />

Виконано у файлі global_task_1.c
Результат виконання:

<img width="571" height="122" alt="Знімок екрана 2026-02-19 о 22 12 39" src="https://github.com/user-attachments/assets/532d9d8f-a35c-411e-bceb-3b200921ff43" />

Завдання №2_2(Скриншот завдання):

<img width="700" height="307" alt="Знімок екрана 2026-02-19 о 22 13 59" src="https://github.com/user-attachments/assets/d71a555a-1956-4999-9f00-8f105633f067" />
<img width="694" height="264" alt="Знімок екрана 2026-02-19 о 22 14 55" src="https://github.com/user-attachments/assets/2df8a441-b2fb-41bc-a93d-2eaf82f64dcb" />

Виконано у файлі task2_2.c:
Результат виконання:

Перше під-завдання:
<img width="1280" height="296" alt="image" src="https://github.com/user-attachments/assets/8650e713-334b-4c20-9338-e22c0a9e6f66" />

Друге під-завдання:

<img width="1280" height="314" alt="image" src="https://github.com/user-attachments/assets/3063da94-1b8f-40cc-b085-f60d08e1f2eb" />

Третє під-завдання:

<img width="1280" height="193" alt="image" src="https://github.com/user-attachments/assets/ae308e81-542e-4ecc-9ac9-bac4a995fb73" />

Четверте під-завдання без виклику функції:

<img width="1280" height="284" alt="image" src="https://github.com/user-attachments/assets/a898ced9-fb15-4ca4-93fd-da9a9621f38e" />

Четверте під-завдання з виклику функції:

<img width="1280" height="331" alt="image" src="https://github.com/user-attachments/assets/298dc8f9-0783-4bdd-91ac-e853f696328f" />

Пʼяте під-завдання:

<img width="1280" height="380" alt="image" src="https://github.com/user-attachments/assets/f677ad95-59b3-45a7-a6a4-7c914f2b1f46" />

Завдання №2_3(Скриншот завдання):

<img width="709" height="407" alt="Знімок екрана 2026-02-19 о 22 19 57" src="https://github.com/user-attachments/assets/cb475a78-d23e-406b-a19c-7b88ae39b699" />

Виконано у файлі task2_3.c:
Результат виконання:

Запуск коду наданого у завданні:

<img width="1280" height="295" alt="image" src="https://github.com/user-attachments/assets/9e8eca2b-a9ff-4106-a6da-40751dff0169" />

Знайдено розташування сегментів даних і тексту, а також купи всередині
сегмента даних, оголосили змінні, які будуть поміщені в ці сегменти, і
виведено їхні адреси:

<img width="1280" height="409" alt="image" src="https://github.com/user-attachments/assets/06e8f420-8d34-4cc5-91b6-5799188b7f4a" />

Збільшено розмір стека, викликавши функцію й оголосивши кілька
великих локальних масивів. Отримали нову вершину стека:

<img width="1280" height="424" alt="image" src="https://github.com/user-attachments/assets/10cdbbcf-e1c7-492e-8bff-b53ae1ea456c" />


Завдання №2_4(Скриншот завдання):

<img width="614" height="38" alt="Знімок екрана 2026-02-19 о 22 23 57" src="https://github.com/user-attachments/assets/b965c162-af14-4cd1-8636-bcb02a225def" />


Виконано у файлі task2_4.c:
Результат виконання:

gstack:

<img width="1280" height="813" alt="image" src="https://github.com/user-attachments/assets/61f08f7c-6c90-41e0-9580-243e4f0dd5c7" />


<img width="1280" height="601" alt="image" src="https://github.com/user-attachments/assets/282d81f6-1ed0-4930-a062-7cb6b8dab894" />

GDB:

<img width="1280" height="595" alt="image" src="https://github.com/user-attachments/assets/e358d850-eb2c-45b0-8ec4-10f9602fc2da" />


gstack: Миттєвий звіт. Програма майже не зупиняється, видає весь текст одразу, але змінні переглянути не можна.

GDB: Глибоке дослідженн. Програма стоїть на паузі, чекає команд, дозволяє вільно перевіряти будь-які дані.


Завдання №2_5(Скриншот завдання):

<img width="703" height="119" alt="Знімок екрана 2026-02-19 о 22 32 27" src="https://github.com/user-attachments/assets/b1cf099c-eeb5-4b2b-b07f-3ac8e7381521" />


Відповідь:
Відмова від IP на користь стека можлива, але вона перетворює процес виконання програми на нескінченний ланцюг переходів.
Перевага: Дуже компактна логіка для специфічних обчислювальних задач (наприклад, віртуальні машини).
Недолік: Величезні затримки через постійний доступ до пам'яті стека та неможливість ефективного передбачення розгалужень.
Сучасні процесори використовують стек як допоміжний інструмент саме тому, що IP дозволяє відокремити дані від потоку, забезпечуючи максимальну швидкість.


Завдання за варіантом №6(Скриншот завдання):


<img width="650" height="58" alt="Знімок екрана 2026-02-19 о 22 35 28" src="https://github.com/user-attachments/assets/209bef1d-5e2a-4d80-afc3-91b4bd6b626a" />


Виконано у файлі task_6_var.c:
Результат виконання:

<img width="682" height="230" alt="image" src="https://github.com/user-attachments/assets/0bb658e6-c061-41cb-8adf-8b9a792e7dc9" />

......


<img width="1280" height="133" alt="image" src="https://github.com/user-attachments/assets/ccfa54ba-9823-4139-b5a5-fb94531cca1b" />


Отримали звідси 260000 викликів.
Проведемо експеримент та виконаєм команду ulimit -s:


<img width="590" height="262" alt="image" src="https://github.com/user-attachments/assets/25beda1d-0761-42e5-821a-5d17589c09d5" />


отримали значення 8192, тобто 8 мб стеку,
у байтах це 8 * 1024 * 1024 = 8,388,608

<img width="434" height="154" alt="image" src="https://github.com/user-attachments/assets/15491760-d5c3-486e-9e17-bcb7b835488a" />

дальще виконаєм математичне обчислення щоб дізнатись скільки памʼяті необхідно для одного стекового кадру 8,388,608 / 260,000 = 32:

<img width="428" height="154" alt="image" src="https://github.com/user-attachments/assets/ee81f37b-8ac8-4dd9-981e-483a40873acc" />


Тобто розмір одного стекового кадру = 32 байти.

Таким чином ми отримуєм формулу Мінімальний необхідний стек = глибина рекурсії * розмір одного стекового кадру(в нашому випадку 32 байти)




