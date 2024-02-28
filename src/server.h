#ifndef SERVER_H
#define SERVER_H
#include <netinet/in.h>
#include "text_stack.h"

typedef struct {
  int serverSocket;
  struct sockaddr_in serverAddr;
  char buffer[1024];
  TextStack *stack;
  int totalConnections;
} Server;

void initializeServer(Server *server, int max_connections);
void receiveMessage(Server *server);
void setTextStack(Server *server, TextStack *text_stack);
void listenForConnections(Server *server);

#endif // !SERVER_H
