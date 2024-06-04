#include "screenIntro.h"
#include "Rectangle.h"
#include "Text.h"
#include "Circle.h"

#include "listColors.h"
#include "fonts.h"
#include "tft.h"
#include "functions.h"

#define DELAY_TIMER_MILLIS 2000 

int screenIntro_show()
{
  int err = -1;

  struct Rectangle rect1;
  struct Rectangle rect2;

  struct text introtext;

  struct circle circ1;

  introtext.color = BLACK;
  introtext.f = mono12x7bold;
  introtext.size = 3;
  strcpy( introtext.text, "PONG\n   GAME" );
  introtext.xo = 120;
  introtext.yo = 100;

  rect1.backgroundColor = BLUE;
  rect1.borderColor = 0;
  rect1.borderSize = 0;
  rect1.circleBorder = 10;
  rect1.heigth = 300;
  rect1.width = 40;
  rect1.xo = 10;
  rect1.yo = 10;

  rect2.backgroundColor = BLUE;
  rect2.borderColor = 0;
  rect2.borderSize = 0;
  rect2.circleBorder = 10;
  rect2.heigth = 300;
  rect2.width = 40;
  rect2.xo = 420;
  rect2.yo = 10;/**/

  circ1.backgroundColor = RED;
  circ1.borderColor = 0;
  circ1.borderSize = 0;
  circ1.radius = 10;
  circ1.xo = 100;
  circ1.yo = 240;


  fillScreen(WHITE);

  //setCursor(140, 100);
  //setTextColor(BLACK);
  //setFont(&mono12x7bold);
  //setTextSize(3);
  //printstr("PONG");

  //setCursor(140, 170);
  //printstr("GAME");
  
  text_draw(&introtext);

  rectangle_draw(&rect1);
  rectangle_draw(&rect2);

  //fillRoundRect(20, 10, 40, 300, 10, BLUE);
  //fillRoundRect(420, 10, 40, 300, 10, BLUE);

  for( int i = 0 ; i < 8; i++ )
  {
    circ1.xo += 30;
    circ1.yo = 240 + 30*(i%2);
    circle_draw(&circ1);
    //fillCircle( 120 +i*30 , 240 + 30*(i%2) , 10, RED );
  }

  return err;
}

int screenIntro_init( struct screenManager *sm )
{
  int err = -1;
  sm->s.tc.delay = DELAY_TIMER_MILLIS;
  err = screenIntro_show();
  return err;
}

