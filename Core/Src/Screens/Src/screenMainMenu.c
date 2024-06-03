#include "screenMainMenu.h"

#include "Text.h"
#include "Bar.h"
#include "Button.h"
#include "Circle.h"
#include "Player.h"
#include "Ball.h"

#include "TimeCounter.h"
#include "fonts.h"
#include "tft.h"
#include "functions.h"


#define DELAY_TIMER_MILLIS 0 
#define LOW_LIMIT_BARR 150
#define HIGH_LIMIT_BARR 70

#define DELAY_BAR_TIMER_MILLIS 10 

struct button btnStart;
struct button btnSettings;
struct player pl1;
struct player pl2;
struct ball bl;

bool intersctionCircles( int r1, int x1, int y1, int r2, int x2, int y2)
{
  float d = 0;
  d = sqrt( pow( x1 - x2  , 2 ) +  pow( y1- y2, 2 ));
  return d <= r1 + r2;
}

void screenMainMenu_collision()
{
  if ( bl.xdir == BALL_DIR_LEFT )
  {
    if(  bl.c.xo - bl.c.radius <= pl1.b.r.xo + pl1.b.r.width)
    {
      if (  bl.c.yo <= pl1.b.r.yo + pl1.b.r.heigth - pl1.b.r.circleBorder 
            && bl.c.yo >= pl1.b.r.yo + pl1.b.r.circleBorder &&  bl.c.xo + bl.c.radius  > pl1.b.r.xo)
      {
        bl.xdir = BALL_DIR_RIGHT;
      }
      else {
        int r1 = bl.c.radius;
        int x1 = bl.c.xo;
        int y1 = bl.c.yo;
        int r2 = pl1.b.r.circleBorder;
        int x2 = pl1.b.r.xo + pl1.b.r.width/2;
        int y2 = y1 < pl1.b.r.yo + pl1.b.r.circleBorder?  pl1.b.r.yo + pl1.b.r.circleBorder : y1 > pl1.b.r.yo + pl1.b.r.heigth - pl1.b.r.circleBorder ? pl1.b.r.yo + pl1.b.r.heigth - pl1.b.r.circleBorder :-1;
        if ( y2 != -1 )
        {
          if ( intersctionCircles( r1,x1,y1,r2,x2,y2 ) )
          {
            bl.xdir = x1 >= x2 ? BALL_DIR_RIGHT : BALL_DIR_LEFT;
            bl.ydir = y1 <= y2 ? BALL_DIR_UP : BALL_DIR_DOWN;
          }
        }
      }
    }
  }
  if ( bl.xdir == BALL_DIR_RIGHT )
  {
    if(  bl.c.xo + bl.c.radius >= pl2.b.r.xo )
    {
      if (  bl.c.yo <= pl2.b.r.yo + pl2.b.r.heigth - pl2.b.r.circleBorder 
            && bl.c.yo >= pl2.b.r.yo + pl2.b.r.circleBorder && bl.c.xo - bl.c.radius  < pl2.b.r.xo + pl2.b.r.width )
      { 
        bl.xdir = BALL_DIR_LEFT;
      }
      else
      {
        int r1 = bl.c.radius;
        int x1 = bl.c.xo;
        int y1 = bl.c.yo;
        int r2 = pl2.b.r.circleBorder;
        int x2 = pl2.b.r.xo + pl2.b.r.width/2;
        int y2 = y1 < pl1.b.r.yo + pl2.b.r.circleBorder?  pl2.b.r.yo + pl2.b.r.circleBorder : y1 > pl2.b.r.yo + pl2.b.r.heigth - pl2.b.r.circleBorder ? pl2.b.r.yo + pl2.b.r.heigth - pl2.b.r.circleBorder :-1;
        if ( y2 != -1 )
        {
          if ( intersctionCircles( r1,x1,y1,r2,x2,y2 ) )
          {
            bl.xdir = x1 >= x2 ? BALL_DIR_RIGHT : BALL_DIR_LEFT;
            bl.ydir = y1 <= y2 ? BALL_DIR_UP : BALL_DIR_DOWN;
          }
        }
      }
    }
  }
}

int screenMainMenu_show()
{
  int err = -1;

  struct text introtext;

  fillScreen(WHITE);
  
  introtext.color = BLACK;
  introtext.f = mono12x7bold;
  introtext.size = 3;
  strcpy( introtext.text, "PONG GAME" );
  introtext.xo = 40;
  introtext.yo = 60;
  text_draw(&introtext);

  player_init(&pl1);
  player_init(&pl2);
  
  button_init(&btnStart);
  button_init(&btnSettings);
  
  ball_init(&bl);

  return err;
}

int screenMainMenu_verifyTimer( )
{
  player_animation( &pl1 );
  player_animation( &pl2 );
  ball_animation(&bl);
  ball_direction(&bl);
  screenMainMenu_collision();
  return -1;
}

int screenMainMenu_init( struct screenManager *sm )
{
  int err = -1;
  sm->s.tc.delay = DELAY_TIMER_MILLIS;

  pl1.b.r.backgroundColor=BLUE;
  pl1.b.r.borderColor = 0;
  pl1.b.r.borderSize = 0;
  pl1.b.r.circleBorder = 10;
  pl1.b.r.heigth = 100;
  pl1.b.r.width = 20;
  pl1.b.r.xo = 40;
  pl1.b.r.yo = LOW_LIMIT_BARR;
  pl1.b.tm.delay = DELAY_BAR_TIMER_MILLIS +15;
  pl1.downLimit = LOW_LIMIT_BARR;
  pl1.upLimit = HIGH_LIMIT_BARR;
  pl1.riseDirection = PLAYER_DIR_UP;

  pl2.b.r.backgroundColor=BLUE;
  pl2.b.r.borderColor = 0;
  pl2.b.r.borderSize = 0;
  pl2.b.r.circleBorder = 10;
  pl2.b.r.heigth = 100;
  pl2.b.r.width = 20;
  pl2.b.r.xo = 380;
  pl2.b.r.yo = HIGH_LIMIT_BARR;
  pl2.b.tm.delay = DELAY_BAR_TIMER_MILLIS +15;
  pl2.downLimit = LOW_LIMIT_BARR;
  pl2.upLimit = HIGH_LIMIT_BARR;
  pl2.riseDirection = PLAYER_DIR_DOWN;

  btnStart.r.backgroundColor = CYAN;
  btnStart.r.borderColor = 0;
  btnStart.r.borderSize = 0;
  btnStart.r.circleBorder = 10;
  btnStart.r.xo = 40;
  btnStart.r.yo = 260;
  btnStart.r.width = 160;
  btnStart.r.heigth = 50;
  btnStart.t.color = WHITE;
  btnStart.t.f = mono12x7bold;
  btnStart.t.size = 1;
  strcpy(  btnStart.t.text , "START GAME");
  btnStart.t.xo = 50;
  btnStart.t.yo = 290;
  btnStart.isPressed = false;
  btnStart.pressedColor = BLACK;
  btnStart.pressedTextColor = WHITE;
  btnStart.releasedColor = CYAN;
  btnStart.releasedTextColor = WHITE;
  btnStart.tm.tStart = 500;

  btnSettings.r.backgroundColor = GREEN;
  btnSettings.r.borderColor = 0;
  btnSettings.r.borderSize = 0;
  btnSettings.r.circleBorder = 10;
  btnSettings.r.xo = 270;
  btnSettings.r.yo = 260;
  btnSettings.r.width = 130;
  btnSettings.r.heigth = 50;
  btnSettings.t.color = WHITE;
  btnSettings.t.f = mono12x7bold;
  btnSettings.t.size = 1;
  strcpy(  btnSettings.t.text , "SETTINGS");
  btnSettings.t.xo = 280;
  btnSettings.t.yo = 290;
  btnSettings.isPressed = false;
  btnSettings.pressedColor = BLACK;
  btnSettings.pressedTextColor = WHITE;
  btnSettings.releasedColor = GREEN;
  btnSettings.releasedTextColor = WHITE;
  btnSettings.tm.delay = 500;

  bl.c.backgroundColor = RED;
  bl.c.borderColor = 0;
  bl.c.borderSize = 0;
  bl.c.radius = 10;
  bl.c.xo = 240;
  bl.c.yo = 160;
  bl.tc.delay = 1;
  bl.step = 5;
  bl.xdir = BALL_DIR_LEFT;
  bl.ydir = BALL_DIR_UP;
  bl.bll.X_LeftLimit = 10;
  bl.bll.X_RigthLimit = 470;
  bl.bll.Y_DownLimit = LOW_LIMIT_BARR + 100;
  bl.bll.Y_UpLimit = HIGH_LIMIT_BARR;
  bl.xInit = 240;
  bl.yInit = 160;

  err = screenMainMenu_show();
  return err;
}

