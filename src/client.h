#ifndef CLIENT_H
#define CLIENT_H

#include <netinet/in.h>
typedef struct {
  int clientSocket;
  struct sockaddr_in serverAddr;
  char buffer[1024];
} Client;

void initializeClient(Client *client);
void runClient(Client *client);
void closeClient(Client *client);
void sendMessage(Client *client, const char *message);

#endif // !CLIENT_H

