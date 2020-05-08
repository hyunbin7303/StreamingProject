
#./bin/ispeed : ./obj/Main.o ./obj/iSpeedClient.o ./obj/iSpeedServer.o ./obj/commandLine.o
#	cc ./obj/Main.o ./obj/iSpeedClient.o ./obj/iSpeedServer.o ./obj/commandLine.o -o ./bin/ispeed


# ./obj/Main.o : ./src/Main.c ./src/iSpeedClient.c ./src/iSpeedServer.c ./src/commandLine.c ./inc/Common.h ./inc/iSpeedClient.h ./inc/iSpeedServer.h
#	cc -c ./src/Main.c -o ./obj/Main.o

#./obj/iSpeedClient.o : ./src/iSpeedClient.c ./inc/iSpeedClient.h
#	cc -c ./src/iSpeedClient.c -o ./obj/iSpeedClient.o

#./obj/iSpeedServer.o : ./src/iSpeedServer.c ./inc/iSpeedServer.h
#	cc -c ./src/iSpeedServer.c -o ./obj/iSpeedServer.o

#./obj/commandLine.o : ./src/commandLine.c ./inc/Common.h
#	cc -c ./src/commandLine.c -o ./obj/commandLine.o

#
# Other Targets
#


CC=g++


CFLAGS=-c -Wall


all:./bin/UDPserver

 		./bin/UDPserver: main.o server.o
		$(CC) main.o server.o -o ./bin/UDPserver


main.o: ./src/main.cpp
	$(CC) $(CFLAGS) ./src/main.cpp

server.o: ./src/server.cpp
	$(CC) $(CFLAGS) ./src/server.cpp



clean:
	rm -f ./bin/*
	rm -f ./obj/*.o
	rm -f .o
	rm -f ./*.o
	rm -f ./src/*.c~
	rm -f ./inc/*.h~
