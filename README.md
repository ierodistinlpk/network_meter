# network_meter

Network meter is my old project that intented for overload network testing.
It consists of Gui, server and nodes.
Gui is jus a graphical interface to database where you can see testing results. It was created with Qt4 and requires Qtdeveloper
Server is a server that controls nodes and sends work plan to them. C++ ans STL is required to compile. was created as Kdevelop projects.
Node is a worker who makes ICMP requests according to timetable. The feature is sending requests bulky without waiting previous response. It helps us to create necessary load at the network and assume bottlenecks when we see statistics how delays are grows up.

Now this project is abandoned but it can be used under LGPL License

Directyry sctucture described as is:

/source - исходные коды

-/analyser - система анализа и расчета данных. проект для qmake/Qtcreator

-/Database - сценарии создания БД на языке sql.

-/agent - агент для UNIX-систем на c++. включает файл проека для kdevelop.

-/server - сервер для UNIX-систем на c++. включает файл проека для kdevelop.

/distrib - утановочные пакеты

-/analyser - исполняемый фал системы анализа и расчета.

-/halfserv-0.1.tar.gz - дистрибутив сервера

-/agent_nix-0.1.tar.gz - дистрибутив агента

-/db - дампы восстановления БД.

-/-/pg_template.pd_dump - структура БД

-/-/errors_type.pd_dump - список типов ошибок

-/-/homelan.pg_dump - слепок результатов тестирования домашней сети

-/-/domolink.pg_dump - слепок результатов тестирования сети "Домолинк"

-/-/corbina.pg_dump - слепок результатов тестирования сети "Корбина"
