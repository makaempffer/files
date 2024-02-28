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
  server->maxConnections = 3;
  server->currentConnections = 0;
  server->clientSockets = (int*)malloc(max_connections * sizeof(int));
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
  pushTextStack(server->stack, "[DEBUG] Receiving messages...");
  int clientSocket = accept(server->serverSocket, NULL, NULL);
  if (clientSocket == -1) {
    perror("[ERROR] Error accepting connection");
    return;
  }
  // Receive message from the client and assign into buffer
  ssize_t bytesReceived = recv(clientSocket, server->buffer, sizeof(server->buffer), 0);

  if (bytesReceived == -1) {
    perror("[ERROR] Error receiving message");
  } else if (bytesReceived > 0) {
    printf("[DEBUG] Received non-empty message\n");
    server->buffer[bytesReceived] = '\0';
    pushTextStack(server->stack, server->buffer);
    printf("[DEBUG] Message Received!: MSG: %s\n", server->buffer);
  } else if (bytesReceived == 0) {
    printf("[DEBUG] Client disconnected\n");
    pushTextStack(server->stack, "[DEBUG] Client disconnected.");
    close(clientSocket);
  }
}

void setTextStack(Server *server, TextStack *text_stack) {
  server->stack = text_stack;
  pushTextStack(server->stack, "Text server assigned.");
  printf("[DEBUG] Setting text Stack!\n");
}

void acceptConnections(Server *server) {
    while (1) {
        int clientSocket = accept(server->serverSocket, NULL, NULL);
        if (clientSocket == -1) {
            perror("[ERROR] Error accepting connection");
            continue;
        }

        if (server->currentConnections < server->maxConnections) {
            // Add the new client socket to the array of client sockets
            server->clientSockets[server->currentConnections++] = clientSocket;

            printf("[DEBUG] Accepted client connection successfully N° connections: %i\n", server->currentConnections);
      break;
        } else {
            printf("[DEBUG] Maximum number of connections reached, rejecting new connection\n");
            close(clientSocket);
        }
  }
}

void receiveMessages(Server *server) {
    for (int i = 0; i < server->currentConnections; ++i) {
        int clientSocket = server->clientSockets[i];

        // Receive message from the client and assign into buffer
        ssize_t bytesReceived = recv(clientSocket, server->buffer, sizeof(server->buffer), 0);

        if (bytesReceived == -1) {
            perror("[ERROR] Error receiving message");
        } else if (bytesReceived > 0) {
            server->buffer[bytesReceived] = '\0';
            pushTextStack(server->stack, server->buffer);
            printf("[DEBUG] Message Received from Client %d: MSG: %s\n", i, server->buffer);
        } else if (bytesReceived == 0) {
            printf("[DEBUG] Client %d disconnected\n", i);
            // Remove the disconnected client from the array
            server->currentConnections--;
            for (int j = i; j < server->currentConnections; ++j) {
                server->clientSockets[j] = server->clientSockets[j + 1];
            }
        }
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
