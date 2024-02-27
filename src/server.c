#include "server.h"
#include "constants.h"
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>

void initializeServer(Server *server, int max_connections) {
  printf("[DEBUG] Initializing server...\n");
  server->serverSocket = socket(AF_INET, SOCK_STREAM, 0);
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
    close(clientSocket);
  }
  /*if (close(server.serverSocket) == -1) {
    perror("[ERROR] Error closing socket");
  } else {
    printf("[DEBUG] Socket was closed successfully\n");
  }
  */
  return 0;
}
