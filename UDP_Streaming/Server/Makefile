CC=g++

CFLAGS=-c -Wall

all:./bin/UDPserver

./bin/UDPserver: ./obj/main.o ./obj/server.o ../Common/obj/mySocket.o ../Common/obj/myHostInfo.o ../Common/obj/common.o
	$(CC) ./obj/main.o ./obj/server.o ../Common/obj/mySocket.o ../Common/obj/myHostInfo.o ../Common/obj/common.o -o ./bin/UDPserver 

./obj/main.o: ./src/main.cpp 
	$(CC) $(CFLAGS) ./src/main.cpp -o ./obj/main.o

./obj/server.o: ./src/server.cpp ./inc/server.h
	$(CC) $(CFLAGS) ./src/server.cpp -o ./obj/server.o

../Common/obj/mySocket.o : ../Common/src/mySocket.cpp ../Common/inc/mySocket.h
	$(CC) $(CFLAGS) ../Common/src/mySocket.cpp -o ../Common/obj/mySocket.o 

../Common/obj/myHostInfo.o : ../Common/src/myHostInfo.cpp ../Common/inc/myHostInfo.h
	$(CC) $(CFLAGS)  ../Common/src/myHostInfo.cpp -o ../Common/obj/myHostInfo.o

../Common/obj/common.o : ../Common/src/common.cpp ../Common/inc/common.h
	$(CC) $(CFLAGS)  ../Common/src/common.cpp -o ../Common/obj/common.o

clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f ./src/*.c~
	rm -f ./inc/*.h~
	rm -f ../Common/bin/*
	rm -f ../Common/obj/*.o
	rm -f ../Common/src/*.c~
	rm -f ../Common/inc/*.h~