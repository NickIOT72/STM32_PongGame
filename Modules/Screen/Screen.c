#include "Screen.h"

int screen_init( struct Screen *s )
{
  s->tChangeStart = 0;
  s->allowTimerChange = false;
  s->timerChangeReached = false;
}