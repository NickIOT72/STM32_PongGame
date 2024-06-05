#ifndef __SCREENSETTINGS_H__
#define __SCREENSETTINGS_H__

#include "ScreenManager.h"

#define MODE_TIMER 0
#define MODE_SCORE 1

#define MAX_MINUTES 5
#define TIMER_STEP 5
#define MIN_SECONDS 30
#define MIN_TO_SECONDS 60 

#define MAX_SCORE 10

struct gameSetting
{
  uint8_t mode;
  uint8_t time_minutes;
  uint8_t time_seconds;
  uint8_t score;
};

int screenSettings_init( struct screenManager *sm  );

#endif