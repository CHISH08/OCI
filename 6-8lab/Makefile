CC = g++
FINALFLAGS =-lzmq -o

all: clean client server

client:
	$(CC) ./src/client.cpp $(FINALFLAGS) client
server:
	$(CC) ./src/server.cpp $(FINALFLAGS) server
clean:
	rm -r -f ./client ./server