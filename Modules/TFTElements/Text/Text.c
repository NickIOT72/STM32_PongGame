#include "Text.h"
#include "listColors.h"
#include "fonts.h"
#include "tft.h"
#include "functions.h"

int text_draw( struct text *t)
{
  setCursor(t->xo, t->yo);
  setTextColor(t->color);
  setFont(&t->f);
  setTextSize(t->size);
  printstr(t->text);
}