# network_meter

Network meter is my old project that intented for overload network testing.
It consists of Gui, server and nodes.
Gui is jus a graphical interface to database where you can see testing results. It was created with Qt4 and requires Qtdeveloper
Server is a server that controls nodes and sends work plan to them. C++ ans STL is required to compile. was created as Kdevelop projects.
Node is a worker who makes ICMP requests according to timetable. The feature is sending requests bulky without waiting previous response. It helps us to create necessary load at the network and assume bottlenecks when we see statistics how delays are grows up.
