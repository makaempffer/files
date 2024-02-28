#ifndef BUTTON_DATA_H
#define BUTTON_DATA_H
#include "raylib.h"

typedef struct {
  char text[8];
  bool isPressed;
  Rectangle rect;
  Color color;
  bool isHovered;
} ButtonData;

void drawButton(ButtonData data);
void checkButtonState(ButtonData *button);
bool getButtonPressed(ButtonData *button);

#endif // !BUTTON_DATA_H
