#ifndef __SCREENGAME_H__
#define __SCREENGAME_H__

#include "ScreenManager.h"
#include "TimeCounter.h"

struct game {
  uint8_t pl1Score;
  uint8_t pl2Score;
  uint8_t timeMinutes;
  uint8_t timeSeconds;
  struct timeCounter tm;
};

int screenGame_init( struct screenManager *sm  );
int screenGame_eval(struct screenManager *sm);

#endif