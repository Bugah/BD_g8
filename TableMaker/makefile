all: QuickStart
QuickStart: Insert Create
	./QuickStart.sh
Insert:
	g++ -o InsertMySQL -I/usr/local/include -I/usr/local/include/cppconn -l mysqlcppconn InsertMySQL.cpp mysql_header.h
Create:
	g++ -o CreateTablesMySQL -I/usr/local/include -I/usr/local/include/cppconn -l mysqlcppconn CreateTablesMySQL.cpp
clean:
	rm files/_InsertMySQL
	rm CreateTablesMySQL