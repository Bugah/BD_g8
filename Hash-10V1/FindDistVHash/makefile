all: BruteForceDist
Linux: 
	g++ -O3 -o BruteForceDist -I/usr/include -I/usr/include/  -l mysqlcppconn BruteForceDist.cpp mysql_header.h KMaxHash.cpp Vetorzao.cpp /usr/lib/libmysqlcppconn.so
BruteForceDist:
	g++ -O3 -o BruteForceDist -I/usr/local/include -I/usr/local/include/cppconn -l mysqlcppconn BruteForceDist.cpp mysql_header.h KMaxHash.cpp Vetorzao.cpp
	#./BruteForceDist file.nor
clean:
	rm BruteForceDist
