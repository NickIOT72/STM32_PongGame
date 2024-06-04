#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "moduleInit.h"

struct triangle
{
  uint16_t x0;
  uint16_t y0;
  uint16_t x1;
  uint16_t y1;
  uint16_t x2;
  uint16_t y2;
  uint16_t backgroundColor;
  uint16_t borderColor;
  uint8_t borderSize;
};

int triangle_draw( struct triangle *tr);

#endif