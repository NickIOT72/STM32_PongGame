#ifndef __BALL_H__
#define __BALL_H__

#include "moduleInit.h"
#include "Circle.h"
#include "TimeCounter.h"

#define BALL_DIR_LEFT false
#define BALL_DIR_RIGHT true
#define BALL_DIR_UP true
#define BALL_DIR_DOWN false

struct ballLimits
{
  uint16_t Y_UpLimit;
  uint16_t Y_DownLimit;
  uint16_t X_LeftLimit;
  uint16_t X_RigthLimit;
};

struct ball
{
  struct circle c;
  struct timeCounter tc;
  bool ydir;
  bool xdir;
  uint8_t step;
  struct ballLimits bll;
  uint16_t xInit ;
  uint16_t yInit ;
  bool ballReset;
};

int ball_init( struct ball *bl);
int ball_animation( struct ball *bl );
int ball_direction( struct ball *bl );
int ball_move(struct ball *bl);

#endif