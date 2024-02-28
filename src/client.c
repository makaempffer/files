#include "client.h"
#include "constants.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>

void initializeClient(Client *client) {
  if ((client->clientSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("[ERROR] Error creating socket");
    exit(EXIT_FAILURE);
  } else {
    printf("[DEBUG] Client Socket initialized\n");
  }

  client->serverAddr.sin_family = AF_INET;
  client->serverAddr.sin_port = htons(PORT);
  inet_pton(AF_INET, "127.0.0.1", &client->serverAddr.sin_addr);

  printf("[DEBUG] Client initialized\n");
}

void runClient(Client *client) {
  if (connect(client->clientSocket, (struct sockaddr*)&client->serverAddr, sizeof(client->serverAddr)) == -1) {
    perror("[ERROR] Error connecting client to server");
  } else {
    printf("[DEBUG] Connected to server succesfully\n");
    sendMessage(client, "bibi byebye");
  }
}

void closeClient(Client *client) {
  printf("[DEBUG] Closing client socket.\n");
  close(client->clientSocket);
}

void sendMessage(Client *client, const char *message) {
  ssize_t bytesSent = send(client->clientSocket, message, strlen(message) + 1, 0);
  if (bytesSent == -1) {
    perror("[ERROR] Error sending message");
  } else {
    printf("[DEBUG] Sent message: %s-Bytes: %zd\n", message, bytesSent);
  }
}
/*
int main(void) {
  Client client;
  initializeClient(&client);
  runClient(&client);
  closeClient(&client);
  return 0;
}
*/
