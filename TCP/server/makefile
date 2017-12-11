main :main.o IKTCP_SERVER.o
	g++ -o server -pthread main.o IKTCP_SERVER.o
main.o:main.cpp ../src/IKTCP_SERVER.h
	g++ -g -c main.cpp
IKTCP_SERVER.o:
	g++ -g -c ../src/IKTCP_SERVER.cpp
clean:
	rm *.o
	rm server
