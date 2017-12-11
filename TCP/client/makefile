

main :main.o IKTCP_CLIENT.o
	g++ -o client main.o IKTCP_CLIENT.o
main.o:main.cpp ../src/IKTCP_CLIENT.h
	g++ -g -c main.cpp
IKTCP_CLIENT.o:
	g++ -g -c ../src/IKTCP_CLIENT.cpp
clean:
	rm *.o
	rm client