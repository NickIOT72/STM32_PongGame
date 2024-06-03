#include "Circle.h"
#include "fonts.h"
#include "tft.h"
#include "functions.h"

int circle_draw( struct circle *r)
{
  fillCircle( r->xo , r->yo , r->radius, r->backgroundColor );
  if ( r->borderSize > 0 )
  {
    for ( int i = 0; i <  r->borderSize; i-- )drawCircle(r->xo , r->yo , r->radius + i, r->borderColor );
  }
}