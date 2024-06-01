#include "screenIntro.h"
#include "fonts.h"
#include "tft.h"
#include "functions.h"

#define DELAY_TIMER_MILLIS 2000 

int screenBlank_show()
{
  int err = -1;
  fillScreen(BLACK);
  return err;
}

int screenBlank_init( struct screenManager *sm )
{
  int err = -1;
  sm->s.tc.delay = DELAY_TIMER_MILLIS;
  err = screenBlank_show();
  return err;
}

