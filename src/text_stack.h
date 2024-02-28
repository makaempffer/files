#ifndef TEXT_STACK_H
#define TEXT_STACK_H
#define MAX_ENTRIES 16

typedef struct {
  char text[256];
} Entry;

typedef struct {
  Entry entries[MAX_ENTRIES];
  int currentIndex;
} TextStack;


void initializeTextStack(TextStack *text_stack);
void pushTextStack(TextStack *text_stack, const char *text);
void popTextStack(TextStack *text_stack);
void drawTextStack(TextStack *text_stack);

#endif
