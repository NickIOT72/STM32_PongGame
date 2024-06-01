#include "ScreenManager.h"

int screenManager_init( struct screenManager *sm)
{
  int err = -1;
  sm->actualScreen = 1;
  return err;
}

int screenManager_updateScreen(struct screenManager *sm , struct Screen *s)
{
  sm->s.delayScreenChange = s->delayScreenChange;
  sm->s.screenNumber = s->screenNumber;
  
  screen_init(&(sm->s));
}
