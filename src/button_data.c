#include "button_data.h"
#include "constants.h"
#include "functions.h"
#include <raylib.h>

void drawButton(ButtonData data) {
  DrawRectangle(data.rect.x, data.rect.y, data.rect.width, data.rect.height, data.color);
  DrawText(data.text, data.rect.x + (data.rect.width / 2) - FONT_SIZE * 1.8, data.rect.y + (data.rect.height / 2.0) - FONT_SIZE / 2.0, FONT_SIZE, WHITE);
}

void checkButtonState(ButtonData *button) { 
  Vector2 mousePos = GetMousePosition();
  bool isButtonHovered = checkCollisionPointRec(mousePos, button->rect);
  button->isHovered = isButtonHovered;
  if (button->isHovered && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
    button->isPressed = true;
  } else {
    button->isPressed = false;
  }
}

bool getButtonPressed(ButtonData *button) {
  return button->isPressed;
}


