#include "server.h"
#include "constants.h"
#include "text_stack.h"
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>


void initializeServer(Server *server, int max_connections) {
  printf("[DEBUG] Initializing server...\n");
  server->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
  server->totalConnections = 0;
  if (server->serverSocket == -1) {
    perror("[ERROR] Error creating socket");
    exit(EXIT_FAILURE);
  } else {
    printf("[DEBUG] Socket initialized\n");
  }
  server->serverAddr.sin_family = AF_INET;
  server->serverAddr.sin_addr.s_addr = INADDR_ANY;
  server->serverAddr.sin_port = htons(PORT);
  if (bind(server->serverSocket, (struct sockaddr*)&(server->serverAddr), sizeof(server->serverAddr)) == -1) {
    perror("[ERROR] Error binding socket, closing socket...");
    close(server->serverSocket);
    exit(EXIT_FAILURE);
  } 

  if (listen(server->serverSocket, max_connections) == -1) {
    perror("[ERROR] Error listening");
  } else {
    printf("[DEBUG] Server listening for connections\n");
  }
  printf("[DEBUG] Server initialized correctly!\n");
}

void receiveMessage(Server *server) {
  printf("[DEBUG] Receiving message\n");
  int clientSocket = accept(server->serverSocket, NULL, NULL);
  if (clientSocket == -1) {
    perror("[ERROR] Error accepting connection");
    return;
  }
  // Receive message from the client and assign into buffer
  ssize_t bytesReceived = recv(clientSocket, server->buffer, sizeof(server->buffer), 0);

  if (bytesReceived == -1) {
    perror("[ERROR] Error receiving message");
  } else {
    server->buffer[bytesReceived] = '\0';
    pushTextStack(server->stack, server->buffer);
    printf("[DEBUG] Message Received!: MSG: %s\n", server->buffer);
  }
}

void setTextStack(Server *server, TextStack *text_stack) {
  server->stack = text_stack;
  pushTextStack(server->stack, "Text server assigned.");
  printf("[DEBUG] Setting text Stack!\n");
}

void listenForConnections(Server *server) {
  if (server->totalConnections >= 1) {
    return;
  }
  int clientSocket = accept(server->serverSocket, NULL, NULL);
  if (clientSocket != -1) {
    printf("[DEBUG] Accepted client connection successfully\n");
    receiveMessage(server);
    close(clientSocket);
    server->totalConnections++;
  }
}
/*
int main(void) {
  Server server;
  initializeServer(&server, 3);
  int isRunning = 1;
  while (isRunning) {
    int clientSocket = accept(server.serverSocket, NULL, NULL);
    if (clientSocket == -1) {
      perror("[ERROR] Error accepting connection");
      continue;
    }

    printf("[DEBUG] Accepted client connection successfully\n");
    receiveMessage(&server);
    close(clientSocket);
  }
  
  return 0;
}
*/
