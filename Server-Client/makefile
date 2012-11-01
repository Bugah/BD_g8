all: both
both:
	make server
	make client
server:
	g++ -O3 -o server -I/usr/local/include -I/usr/local/include/cppconn -l mysqlcppconn server.cpp helper.c mysql_header.h KMaxHeap.cpp Vetorzao.cpp
client:
	gcc -O3 -o client client_b.c helper.c 
clean:
	rm server
	rm client
redo:
	make clean
	make
Linux:
	make client
	make serverLinux
serverLinux:
	g++ -O3 -o server -I/usr/include -I/usr/include/ mysqlcppconn server.cpp helper.c mysql_header.h KMaxHeap.cpp Vetorzao.cpp /usr/lib/libmysqlcppconn.so