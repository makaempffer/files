CC = gcc
CFLAGS = -Wall -Iraylib/src -Lraylib/src -lraylib -lm

SOURCES = src/main.c src/server.c src/button_data.c src/functions.c src/text_stack.c src/client.c
HEADERS = src/constants.h src/server.h src/button_data.h src/functions.h src/text_stack.h src/client.h
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
