#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "moduleInit.h"

struct circle
{
  uint16_t radius;
  uint16_t xo;
  uint16_t yo;
  uint16_t backgroundColor;
  uint16_t borderColor;
  uint8_t borderSize;
};

int circle_draw( struct circle *r);

#endif