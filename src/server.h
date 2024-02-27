#ifndef SERVER_H
#define SERVER_H
#include <netinet/in.h>

typedef struct {
  int serverSocket;
  struct sockaddr_in serverAddr;
  char buffer[1024];
} Server;

void initializeServer(Server *server, int max_connections);

#endif // !SERVER_H
