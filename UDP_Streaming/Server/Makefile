CC=g++

CFLAGS=-c -Wall

all:./bin/UDPserver

./bin/UDPserver: ./obj/main.o ./obj/server.o
	$(CC) ./obj/main.o ./obj/server.o -o ./bin/UDPserver

./obj/main.o: ./src/main.cpp
	$(CC) $(CFLAGS) ./src/main.cpp -o ./obj/main.o

./obj/server.o: ./src/server.cpp
	$(CC) $(CFLAGS) ./src/server.cpp -o ./obj/server.o


../Common/obj/mySocket.o : ../Common/src/mySocket.cpp ../Common/inc/mySocket.h
	gcc -g -c ../Common/src/mySocket.cpp -o ../Common/obj/mySocket.o 
../Common/obj/myHostInfo.o : ../Common/src/myHostInfo.cpp ../Common/inc/myHostInfo.h
	gcc -g -c ../Common/src/myHostInfo.cpp -o ../Common/obj/myHostInfo.o

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./src/*.c~
	rm -f ./inc/*.h~
