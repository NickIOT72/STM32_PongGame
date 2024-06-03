#include "Bar.h"

int bar_init( struct bar *b)
{
  rectangle_draw(&(b->r));
  timeCounter_init(&(b->tm));
}