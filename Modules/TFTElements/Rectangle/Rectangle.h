#ifndef __RECTANGLE_H__
#define __RECTANGLE_H__

#include "moduleInit.h"

struct Rectangle
{
  uint16_t width;
  uint16_t heigth;
  uint16_t xo;
  uint16_t yo;
  uint16_t backgroundColor;
  uint16_t borderColor;
  uint8_t borderSize;
  uint8_t circleBorder;
};

int rectangle_draw( struct Rectangle *r);

#endif