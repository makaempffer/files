#include "raylib.h"
bool checkCollisionPointRec(Vector2 point, Rectangle rect) {
  return (point.x >= rect.x && point.x <= (rect.x + rect.width) &&
          point.y >= rect.y && point.y <= (rect.y + rect.height));
}


