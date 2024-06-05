#include "Rectangle.h"
#include "fonts.h"
#include "tft.h"
#include "functions.h"

int rectangle_draw( struct Rectangle *r)
{
  fillRoundRect(r->xo, r->yo, r->width, r->heigth, r->circleBorder, r->backgroundColor);
  if ( r->borderSize > 0 )
  {
    for ( int i = 0; i < r->borderSize; i++ )drawRoundRect(r->xo+i, r->yo+i, r->width -2*i, r->heigth-2*i, r->borderSize , r->borderColor);
  }
}