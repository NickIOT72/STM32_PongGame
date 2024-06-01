#ifndef __TIMECOUNTER_H__
#define __TIMECOUNTER_H__

#include "moduleInit.h"

struct timeCounter
{
  unsigned long tStart;
  uint16_t delay;
  bool allowTimer;
  bool timerReached;
};

int timeCounter_init( struct timeCounter *tc );
int timeCounter_initTimer( struct timeCounter *tc );
int timeCounter_verifyTimer( struct timeCounter *tc  );
int timeCounter_resetTimer( struct timeCounter *tc );
int timeCounter_endTimer( struct timeCounter *tc  );

#endif