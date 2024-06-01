#ifndef __SCREEN_H__
#define __SCREEN_H__

#include "moduleInit.h"

struct Screen
{
  uint8_t screenNumber;
  unsigned long tChangeStart;
  uint16_t delayScreenChange;
  bool allowTimerChange;
  bool timerChangeReached;
};

int screen_init( struct Screen *s );
int screen_updateScreen( struct Screen *s );

#endif