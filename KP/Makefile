CC = g++
FINALFLAGS =-lzmq -o

all: clean server game client

server:
	$(CC) ./src/server.cpp $(FINALFLAGS) server
game:
	$(CC) ./src/game.cpp $(FINALFLAGS) game
client:
	$(CC) ./src/client.cpp $(FINALFLAGS) client
clean:
	rm -r -f ./game ./server ./client