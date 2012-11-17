all: Linux

# Linux Fag!
Linux:
	g++ -o Consultor -I/usr/include -I/usr/include/ -l mysqlcppconn smart_consul.cpp Text.cpp /usr/lib/libmysqlcppconn.so

debug:
	g++ -o Consultor -I/usr/include -I/usr/include/ -l mysqlcppconn smart_consul.cpp Text.cpp /usr/lib/libmysqlcppconn.so -g

gdb:
	gdb Consultor

GDBdebug: debug
	gdb Consultor

redebug: clean debug

clean:
	rm Consultor

redo: clean Linux
	
