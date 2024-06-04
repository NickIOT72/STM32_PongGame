#include "Ball.h"
#include "listColors.h"
#include "fonts.h"
#include "tft.h"
#include "functions.h"

int ball_init( struct ball *bl)
{
  bl->c.xo = bl->xInit;
  bl->c.yo = bl->yInit;
  circle_draw(&bl->c);
  timeCounter_init(&bl->tc);
  return -1;
}

int ball_set(struct ball *bl)
{
  uint16_t colorperv = bl->c.backgroundColor;
  bl->c.backgroundColor = WHITE;
  circle_draw( &bl->c );
  bl->c.backgroundColor = colorperv;
  circle_draw( &bl->c );
  return -1;
}

int ball_move(struct ball *bl)
{
  uint16_t colorperv = bl->c.backgroundColor;
  bl->c.backgroundColor = WHITE;
  circle_draw( &bl->c );
  bl->c.xo = bl->xdir == BALL_DIR_LEFT? bl->c.xo -bl->step : bl->c.xo +bl->step;
  bl->c.yo = bl->ydir == BALL_DIR_UP? bl->c.yo -bl->step : bl->c.yo + bl->step;
  bl->c.backgroundColor = colorperv;
  circle_draw( &bl->c );
  return -1;
}

int ball_direction( struct ball *bl )
{
  if ( bl->c.xo <= bl->bll.X_LeftLimit )
  {
    uint16_t colorperv = bl->c.backgroundColor;
    bl->c.backgroundColor = WHITE;
    circle_draw( &bl->c );
    bl->xdir = BALL_DIR_RIGHT;
    bl->c.xo = bl->xInit;
    bl->c.yo = bl->yInit;
    bl->c.backgroundColor = colorperv;
    circle_draw( &bl->c );
    bl->ballReset = true;
  }
  else if ( bl->c.xo >= bl->bll.X_RigthLimit )
  {
    uint16_t colorperv = bl->c.backgroundColor;
    bl->c.backgroundColor = WHITE;
    circle_draw( &bl->c );
    bl->xdir = BALL_DIR_LEFT;
    bl->c.xo = bl->xInit;
    bl->c.yo = bl->yInit;
    bl->c.backgroundColor = colorperv;
    circle_draw( &bl->c );
    bl->ballReset = true;
  }
  if ( bl->c.yo - bl->c.radius <= bl->bll.Y_UpLimit )bl->ydir = BALL_DIR_DOWN;
  else if ( bl->c.yo + bl->c.radius >= bl->bll.Y_DownLimit  ) bl->ydir = BALL_DIR_UP;
  return -1;
}

int ball_animation( struct ball *bl )
{
  timeCounter_verifyTimer(&bl->tc);
  if ( bl->tc.timerReached  )
  {
    ball_move( bl );
    if (bl->ballReset) bl->ballReset = false;
    timeCounter_resetTimer(&bl->tc);
  }
  return -1;
}