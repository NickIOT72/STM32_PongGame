#include "Triangle.h"
#include "listColors.h"
#include "fonts.h"
#include "tft.h"
#include "functions.h"

int triangle_draw( struct triangle *tr)
{
  fillTriangle( tr->x0, tr->y0, tr->x1, tr->y1, tr->x2, tr->y2, tr->backgroundColor );
  if ( tr->borderSize > 0 )
  {
    for ( int i = 0; i < tr->borderSize; i++ )drawTriangle(tr->x0 , tr->y0 + i, tr->x1, tr->y1, tr->x2, tr->y2, tr->backgroundColor);
  }
}