#include "Screen.h"

int screen_init( struct Screen *s )
{
  timerCounter_init( &(s->tc) );
}