#include "text_stack.h"
#include <stdio.h>
#include <string.h>
#include "raylib.h"
#include "constants.h"

void initializeTextStack(TextStack *text_stack) {
  text_stack->currentIndex = 0;
}

void pushTextStack(TextStack *text_stack, const char *text) {
  if (text_stack->currentIndex >= MAX_ENTRIES) {
    text_stack->currentIndex = 0;
  }
  strcpy(text_stack->entries[text_stack->currentIndex].text, text);
  text_stack->currentIndex++;
  printf("[DEBUG] Appended to stack successfully\n");
}

void popTextStack(TextStack *text_stack) {
  return;
}

void drawTextStack(TextStack *text_stack) {
  for (int i = 0; i < text_stack->currentIndex; i++) {
    DrawText(text_stack->entries[i].text, 100, (FONT_SIZE * i) + 100, FONT_SIZE, WHITE);
  }
}
