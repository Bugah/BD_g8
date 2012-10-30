all: BruteForceDist
Linux: 
	g++ -O3 -o BruteForceDist -I/usr/include -I/usr/include/  -l mysqlcppconn BruteForceDist.cpp KMaxHeap.cpp Vetorzao.cpp Relogio.cpp /usr/lib/libmysqlcppconn.so
BruteForceDist:
	g++ -O3 -o BruteForceDist -I/usr/local/include -I/usr/local/include/cppconn -l mysqlcppconn -lpthread BruteForceDist.cpp mysql_header.h KMaxHeap.cpp Vetorzao.cpp Relogio.cpp
clean:
	rm BruteForceDist
run:
	#./BruteForceDist norFiles/IMG000005.nor 1.nor
	# Exemplo e chamada.
remake:
	make clean
	make
replay:
	make clean
	make
	make run