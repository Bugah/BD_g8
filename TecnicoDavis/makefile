all: Linux
Linux:
	g++ -o Coach -I/usr/include/ -l mysqlcppconn Coach.cpp Text.cpp Text.h mysql_header.h /usr/lib/libmysqlcppconn.so
clean:
	rm Coach
redo:	Linux clean

debug:
	g++ -o D_Coach -I/usr/include -l mysqlcppconn Coach.cpp Text.cpp Text.h mysql_header.h /usr/lib/libmysqlcppconn.so -g
