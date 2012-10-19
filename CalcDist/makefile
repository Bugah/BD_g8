all: Distance
Linux: DistanceLinux
Distance:
	g++ -o CalcDist -I/usr/local/include -I/usr/local/include/cppconn -l mysqlcppconn CalcDist.cpp
DistanceLinux:
	g++ -o CalcDist -I/usr/include -I/usr/include/cppconn -l mysqlcppconn CalcDist.cpp /usr/lib/libmysqlcppconn.so
clean:
	rm CalcDist