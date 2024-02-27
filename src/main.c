#include "raylib.h"
#include "constants.h"
#include <arpa/inet.h>
#include <unistd.h>

int main(void)
{
  InitWindow(WIDTH, HEIGHT, "raylib [core] example - basic window");
  SetTargetFPS(FPS);

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(BLACK);
    EndDrawing();
  }

  CloseWindow();
  return 0;
}
