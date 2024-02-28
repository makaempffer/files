#include "raylib.h"
#include "constants.h"
#include "server.h"
#include "client.h"
#include "button_data.h"
#include <stdbool.h>
#include "text_stack.h"
#include <sys/socket.h>
#include <pthread.h>


void* listenForConnectionsThread(void* serverPtr) {
  Server* server = (Server*)serverPtr;
  listenForConnections(server);
  receiveMessage(server);
  return NULL;
}

int main(void)
{
  bool isClient;
  bool isInitialized = false;
  // Initialization
  TextStack textStack;
  initializeTextStack(&textStack);
  Server server;
  Client client;
  pthread_t connectionThread;

  InitWindow(WIDTH, HEIGHT, "server-client messaging :)");
  SetTargetFPS(FPS);
  Rectangle serverButtonRect = {20, 20, 120, 50};
  ButtonData serverButton = {"SERVER", false, serverButtonRect, RED, false};

  Rectangle clientButtonRect = {160, 20, 120, 50};
  ButtonData clientButton = {"CLIENT", false, clientButtonRect, BLUE, false};


  pushTextStack(&textStack, "Hola valebb eejej");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    // TEXT
    drawTextStack(&textStack);
    // SERVER BUTTON LOGIC
    //
    checkButtonState(&serverButton);
    if (getButtonPressed(&serverButton) && !isInitialized) {
      serverButton.color = GREEN;
      isClient = false;
      isInitialized = true;
      initializeServer(&server, 1);
      setTextStack(&server, &textStack);

      pthread_create(&connectionThread, NULL, listenForConnectionsThread, (void*)&server);

    }
    drawButton(serverButton);
    // CLIENT BUTTON LOGIC
    //
    checkButtonState(&clientButton);
    if (getButtonPressed(&clientButton) && !isInitialized) {
      clientButton.color = GREEN;
      isClient = true;
      isInitialized = true;
      initializeClient(&client);
    }

    drawButton(clientButton);

    EndDrawing();
  }

  if (isInitialized && !isClient) {
    pthread_join(connectionThread, NULL);
  }

  CloseWindow();
  return 0;
}
