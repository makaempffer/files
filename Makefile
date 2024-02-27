CC = gcc
CFLAGS = -Wall -Iraylib/src -Lraylib/src -lraylib -lm

SOURCES = src/main.c src/server.c
HEADERS = src/constants.h src/server.h
EXECUTABLE = game

all: $(EXECUTABLE)

run: $(EXECUTABLE)
	./$(EXECUTABLE)

server: src/server.c src/server.h
	$(CC) src/server.c $(CFLAGS) -o $@

runserver: 
	./server

client: src/client.c src/client.h
	$(CC) src/client.c $(CFLAGS) -o $@

runclient:
	./client

$(EXECUTABLE): $(SOURCES) $(HEADERS)
	$(CC) $(SOURCES) $(CFLAGS) -o $@

clean:
	rm -f $(EXECUTABLE)
