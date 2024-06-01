#include "screenIntro.h"
#include "fonts.h"
#include "tft.h"
#include "functions.h"

#define DELAY_TIMER_MILLIS 2000 

int screenIntro_show()
{
  int err = -1;
  fillScreen(WHITE);
  printnewtstr(100,RED, &mono12x7bold, 1 , "HELLO WORLD");
  return err;
}

int screenIntro_init( struct screenManager *sm )
{
  int err = -1;
  sm->s.tc.delay = DELAY_TIMER_MILLIS;
  err = screenIntro_show();
  return err;
}

