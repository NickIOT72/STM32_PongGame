#include "TimeCounter.h"

int timeCounter_init( struct timeCounter *tc )
{
  int err = -1;
  tc->allowTimer = false;
  tc->timerReached = false;
  return err;
}

int timeCounter_initTimer( struct timeCounter *tc )
{
  int err = -1;
  tc->allowTimer = true;
  tc->tStart = HAL_GetTick();
  return err;
}

int timeCounter_verifyTimer( struct timeCounter *tc  )
{
  int err = -1;
  if ( (HAL_GetTick() > tc->tStart + tc->delay) && !tc->timerReached )
  {
    tc->timerReached = true;
  }
  return err;
}
int timeCounter_resetTimer( struct timeCounter *tc )
{
  int err = -1;
  tc->tStart = HAL_GetTick();
  tc->timerReached = false;
  return err;
}

int timeCounter_endTimer( struct timeCounter *tc  )
{
  int err = -1;
  tc->tStart = 0;
  tc->allowTimer = false;
  tc->timerReached = false;
  return err;
}