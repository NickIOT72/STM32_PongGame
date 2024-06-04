#ifndef __BAR_H__
#define __BAR_H__

#include "moduleInit.h"
#include "Rectangle.h"
#include "TimeCounter.h"

struct bar
{
  struct Rectangle r;
  struct timeCounter tm;
};

int bar_init( struct bar *b);

#endif