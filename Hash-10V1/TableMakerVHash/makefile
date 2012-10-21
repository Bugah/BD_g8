all: QuickStart
QuickStart: Insert Create
	#./QuickStart.sh
Linux: InsertLinux CreateLinux
	#./QuickStart.sh
Insert:
	g++ -o InsertMySQL -I/usr/local/include -I/usr/local/include/cppconn -l mysqlcppconn InsertMySQL.cpp mysql_header.h Vetorzao.cpp
Create:
	g++ -o CreateTablesMySQL -I/usr/local/include -I/usr/local/include/cppconn -l mysqlcppconn CreateTablesMySQL.cpp
InsertLinux:
	g++ -o InsertMySQL -I/usr/include -I/usr/include/  -l mysqlcppconn InsertMySQL.cpp mysql_header.h /usr/lib/libmysqlcppconn.so
CreateLinux:
	g++ -o CreateTablesMySQL -I/usr/include -I/usr/include/cppconn -l mysqlcppconn CreateTablesMySQL.cpp /usr/lib/libmysqlcppconn.so
clean:
	rm InsertMySQL
	rm CreateTablesMySQL