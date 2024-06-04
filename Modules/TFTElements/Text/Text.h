#ifndef __TEXT_H__
#define __TEXT_H__

#include "moduleInit.h"
#include "fonts.h"

struct text
{
  uint16_t xo;
  uint16_t yo;
  uint16_t color;
  uint8_t size;
  GFXfont f;
  unsigned char text[13];
};

int text_draw( struct text *t);

#endif