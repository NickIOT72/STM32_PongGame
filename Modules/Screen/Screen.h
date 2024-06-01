#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "moduleInit.h"
#include "TimeCounter.h"

struct Screen
{
  uint8_t screenNumber;
  struct timeCounter tc;
};

int screen_init( struct Screen *s );
int screen_updateScreen( struct Screen *s );

#endif