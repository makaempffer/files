#include "raylib.h"
#include "constants.h"
#include "server.h"
#include "client.h"
#include "button_data.h"
#include <stdbool.h>
#include "text_stack.h"
#include <sys/socket.h>
#include <pthread.h>
#include <unistd.h>



void* listenForConnectionsThread(void* serverPtr) {
  Server* server = (Server*)serverPtr;
  while (1) {
    if (server->currentConnections >= 1) {
      receiveMessages(server); 
    } else {
      acceptConnections(server);
    }
    usleep(100*1000);
  }
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
  ButtonData clientButton = {"CLIENT", false, clientButtonRect, RED, false};

  Rectangle sendButtonRect = {300, 20, 120, 50};
  ButtonData sendButton = {"SEND", false, sendButtonRect, GREEN, false};

  pushTextStack(&textStack, "-TEXT-");

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    // TEXT
    drawTextStack(&textStack);
    // SERVER BUTTON LOGIC
    //
    checkButtonState(&serverButton);

    if (getButtonPressed(&serverButton) && !isInitialized) {
      serverButton.color = BLUE;
      isClient = false;
      isInitialized = true;
      initializeServer(&server, 3);
      setTextStack(&server, &textStack);
      if (!isClient && isInitialized) pthread_create(&connectionThread, NULL, listenForConnectionsThread, (void*)&server);
    }

    // CLIENT BUTTON LOGIC
    //
    checkButtonState(&clientButton);
    if (getButtonPressed(&clientButton) && !isInitialized) {
      clientButton.color = BLUE;
      isClient = true;
      isInitialized = true;
      initializeClient(&client);
      runClient(&client);
    }

    checkButtonState(&sendButton);
    if (getButtonPressed(&sendButton) && isInitialized && isClient) {
      sendMessage(&client, "Hello world!");
    }


    // Button draw
    drawButton(sendButton);
    drawButton(clientButton);
    drawButton(serverButton);

    EndDrawing();
  }

  if (isInitialized && !isClient) {
    pthread_join(connectionThread, NULL);
  }
  closeClient(&client);

  CloseWindow();
  return 0;
}
