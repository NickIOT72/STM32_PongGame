#include "screenGame.h"
#include "screenSettings.h"

#include "main.h"

#include "Text.h"
#include "Bar.h"
#include "Button.h"
#include "Circle.h"
#include "Player.h"
#include "Ball.h"
#include "Triangle.h"
#include "Joystick.h"
#include "TimeCounter.h"

#include "fonts.h"
#include "tft.h"
#include "functions.h"

extern ADC_HandleTypeDef hadc1;

#define DELAY_TIMER_MILLIS 0 
#define LOW_LIMIT_BARR 180
#define HIGH_LIMIT_BARR 50

#define DELAY_BAR_TIMER_MILLIS 10 

struct button buttonExitGame;
struct button buttonNewGame;
struct button scoreGameTable;
struct button timerTable;
struct player pl1Game;
struct player pl2Game;
struct ball blGame;
struct game gpong;
struct gameSetting gspong;
struct joystick js3;
struct button centerText;
struct timeCounter timerTock;
struct triangle selectorGame;


struct triangle selectorGameModal;
struct button buttonNewGameModal;
struct button buttonExitGameModal;

uint8_t countPong = 0;


bool changeScreen = false;





int changeRowGameModal(struct joystick *js   )
{
  if ( (selectorGameModal.x0 == buttonExitGameModal.r.xo - 30 && js->adc_X > 3500) || (selectorGameModal.x0 == buttonNewGameModal.r.xo - 30 && js->adc_X < 500) )
  {
    selectorGameModal.backgroundColor = WHITE;
    triangle_draw(&selectorGameModal);
    selectorGameModal.x0 = selectorGameModal.x0 == buttonExitGameModal.r.xo - 30  ? buttonNewGameModal.r.xo - 30: buttonExitGameModal.r.xo - 30;
    selectorGameModal.x1 = selectorGameModal.x1 = selectorGameModal.x0;
    selectorGameModal.x2 = selectorGameModal.x2 = selectorGameModal.x0 + 20;
    selectorGameModal.backgroundColor = RED;
    triangle_draw(&selectorGameModal);
  }
  return -1;
}

int optionPressedGameModal( struct button *btn, struct joystick *js , struct triangle *t , uint16_t distance )
{
  if ( !btn->isPressed && !js->sw && (int)(btn->r.xo - t->x0) < distance && (int)(btn->r.xo - t->x0) > 0)
  {
    btn->isPressed = true;
    btn->r.backgroundColor = btn->pressedColor;
    btn->t.color = btn->pressedTextColor;
    btn->r.borderColor = btn->pressedTextColor;
    btn->r.borderSize = 2;
    button_draw(btn);
    selectorGameModal.backgroundColor = GREEN;
    triangle_draw(&selectorGameModal);
  }
  else if( btn->isPressed && js->sw && (int)(btn->r.xo - t->x0) < distance && (int)(btn->r.xo - t->x0) > 0 )
  {
    btn->isPressed = false;
    btn->r.backgroundColor = btn->releasedColor;
    btn->t.color = btn->releasedTextColor;
    btn->r.borderColor = 0;
    btn->r.borderSize = 0;
    button_draw(btn);
    selectorGameModal.backgroundColor = RED;
    triangle_draw(&selectorGameModal);
    return 1;
  }
  return -1;
}

int btnNewGameVal = 0;
int btnExitVal = 0;

int screenGame_optionPressedModal(struct joystick *js)
{
  btnNewGameVal = optionPressedGameModal( &buttonNewGameModal, js, &selectorGameModal, 40 );
  btnExitVal = optionPressedGameModal( &buttonExitGameModal, js, &selectorGameModal , 40);
  return -1;
}

void checkButtonsGameModal( struct joystick *js  )
{
  if ( !buttonNewGameModal.isPressed && !buttonExitGameModal.isPressed )
  {
    changeRowGameModal(js);
  }
  screenGame_optionPressedModal(js);
}

void modalPause()
{
  centerText.t.xo = 190;
  centerText.t.yo = 180;
  uint16_t prevrxo = centerText.r.xo;
  uint16_t prevtxo = centerText.t.xo;
  uint16_t prevryo = centerText.r.yo;
  uint8_t prevsizetext= centerText.t.size;
  centerText.t.size = 2;
  centerText.t.xo -= 20;
  strcpy( centerText.t.text, "PAUSE" );
  button_draw(&centerText);

  buttonExitGameModal.r.backgroundColor = RED;
  buttonExitGameModal.r.borderColor = 0;
  buttonExitGameModal.r.borderSize = 0;
  buttonExitGameModal.r.circleBorder = 10;
  buttonExitGameModal.r.xo = centerText.t.xo - 30;
  buttonExitGameModal.r.yo = centerText.t.yo + 30;
  buttonExitGameModal.r.width = 80;
  buttonExitGameModal.r.heigth = 30;
  buttonExitGameModal.t.color = WHITE;
  buttonExitGameModal.t.f = mono12x7bold;
  buttonExitGameModal.t.size = 1;
  strcpy(  buttonExitGameModal.t.text , "EXIT");
  buttonExitGameModal.t.xo = buttonExitGameModal.r.xo + 10;
  buttonExitGameModal.t.yo = buttonExitGameModal.r.yo + 20;
  buttonExitGameModal.isPressed = false;
  buttonExitGameModal.pressedColor = WHITE;
  buttonExitGameModal.pressedTextColor = RED;
  buttonExitGameModal.releasedColor = RED;
  buttonExitGameModal.releasedTextColor = WHITE;
  buttonExitGameModal.tm.tStart = 500;

  button_draw(&buttonExitGameModal);

  buttonNewGameModal.r.backgroundColor = BLUE;
  buttonNewGameModal.r.borderColor = 0;
  buttonNewGameModal.r.borderSize = 0;
  buttonNewGameModal.r.circleBorder = 10;
  buttonNewGameModal.r.xo = buttonExitGameModal.r.xo +  buttonExitGameModal.r.width + 40;
  buttonNewGameModal.r.yo = buttonExitGameModal.r.yo;
  buttonNewGameModal.r.width = 100;
  buttonNewGameModal.r.heigth = 30;
  buttonNewGameModal.t.color = WHITE;
  buttonNewGameModal.t.f = mono12x7bold;
  buttonNewGameModal.t.size = 1;
  strcpy(  buttonNewGameModal.t.text , "RESUME");
  buttonNewGameModal.t.xo = buttonNewGameModal.r.xo +10;
  buttonNewGameModal.t.yo = buttonExitGameModal.r.yo + 20;
  buttonNewGameModal.isPressed = false;
  buttonNewGameModal.pressedColor = WHITE;
  buttonNewGameModal.pressedTextColor = BLUE;
  buttonNewGameModal.releasedColor = BLUE;
  buttonNewGameModal.releasedTextColor = WHITE;
  buttonNewGameModal.tm.tStart = 500;

  button_draw(&buttonNewGameModal);

  selectorGameModal.x0 = buttonExitGameModal.r.xo - 30;
  selectorGameModal.y0 = 215;
  selectorGameModal.x1 = selectorGameModal.x0;
  selectorGameModal.y1 = 235;
  selectorGameModal.x2 = selectorGameModal.x0 + 20;
  selectorGameModal.y2 = 225;
  selectorGameModal.backgroundColor = RED;
  selectorGameModal.borderColor = 0;
  selectorGameModal.borderSize = 0;

  triangle_draw(&selectorGameModal);

  while (1)
  {
    joystick_getValuesByTimer(&js3 , checkButtonsGameModal );
    if ( btnNewGameVal == 1 )
    {
      btnNewGameVal = 0;
      btnExitVal = 0;
      break;
    }
    else if ( btnExitVal == 1 )
    {
      changeScreen = true;
      break;
    }
  }
  centerText.r.backgroundColor = WHITE;
  centerText.r.borderColor = 0;
  centerText.r.borderSize = 0;
  centerText.r.circleBorder = 10;
  centerText.r.xo = 80;
  centerText.r.yo = 80;
  centerText.r.width = 280;
  centerText.r.heigth = 170;
  centerText.t.color = BLACK;
  centerText.t.f = mono12x7bold;
  centerText.t.size = 5;
  strcpy( centerText.t.text, "" );
  centerText.t.xo = 190;
  centerText.t.yo = 180;
  rectangle_draw(&centerText.r);


}






int changeRowGame(struct joystick *js   )
{
  if ( (selectorGame.x0 == 20 && js->adc_X > 3500) || (selectorGame.x0 == 270 && js->adc_X < 500) )
  {
    selectorGame.backgroundColor = WHITE;
    triangle_draw(&selectorGame);
    selectorGame.x0 = selectorGame.x0 ==20 ? 270: 20;
    selectorGame.x1 = selectorGame.x1 ==20 ? 270: 20;
    selectorGame.x2 = selectorGame.x2 ==40 ? 290: 40;
    selectorGame.backgroundColor = RED;
    triangle_draw(&selectorGame);
  }
  return -1;
}

int optionPressedGame( struct button *btn, struct joystick *js , struct triangle *t , uint16_t distance )
{
  if ( !btn->isPressed && !js->sw && (int)(btn->r.xo - t->x0) < distance && (int)(btn->r.xo - t->x0) > 0)
  {
    btn->isPressed = true;
    btn->r.backgroundColor = btn->pressedColor;
    btn->t.color = btn->pressedTextColor;
    btn->r.borderColor = btn->pressedTextColor;
    btn->r.borderSize = 2;
    button_draw(btn);
    selectorGame.backgroundColor = GREEN;
    triangle_draw(&selectorGame);
  }
  else if( btn->isPressed && js->sw && (int)(btn->r.xo - t->x0) < distance && (int)(btn->r.xo - t->x0) > 0 )
  {
    btn->isPressed = false;
    btn->r.backgroundColor = btn->releasedColor;
    btn->t.color = btn->releasedTextColor;
    btn->r.borderColor = 0;
    btn->r.borderSize = 0;
    button_draw(btn);
    selectorGame.backgroundColor = RED;
    triangle_draw(&selectorGame);
    return 1;
  }
  return -1;
}

int screenGame_optionPressed(struct joystick *js)
{
  btnNewGameVal = optionPressedGame( &buttonNewGame, js, &selectorGame, 40 );
  btnExitVal = optionPressedGame( &buttonExitGame, js, &selectorGame , 40);
  return -1;
}

void checkButtonsGame( struct joystick *js  )
{
  if ( !buttonNewGame.isPressed && !buttonExitGame.isPressed )
  {
    changeRowGame(js);
  }
  screenGame_optionPressed(js);
}




int showCount()
{
  
  for( int i = 0 ; i < 4; i++ )
  {
    if ( i< 3 ) sprintf(centerText.t.text , "%d" , 3-i );
    else {
      centerText.t.xo = 130;
      centerText.t.yo = 180;
      strcpy( centerText.t.text, "GO!" );
    }
    button_draw(&centerText);  
    HAL_Delay(1000); 
  }
  rectangle_draw(&centerText.r);
}

bool intersectionCircles( int r1, int x1, int y1, int r2, int x2, int y2)
{
  float d = 0;
  d = sqrt( pow( x1 - x2  , 2 ) +  pow( y1- y2, 2 ));
  return d <= r1 + r2;
}

int screenGame_collision(struct player *pl1 , struct player *pl2 , struct ball *bl)
{
  if ( bl->xdir == BALL_DIR_LEFT )
  {
    if(  bl->c.xo - bl->c.radius <= pl1->b.r.xo + pl1->b.r.width)
    {
      if (  bl->c.yo <= pl1->b.r.yo + pl1->b.r.heigth - pl1->b.r.circleBorder 
            && bl->c.yo >= pl1->b.r.yo + pl1->b.r.circleBorder &&  bl->c.xo + bl->c.radius  > pl1->b.r.xo)
      {
        bl->xdir = BALL_DIR_RIGHT;
        countPong+= 1;
      }
      else {
        int r1 = bl->c.radius;
        int x1 = bl->c.xo;
        int y1 = bl->c.yo;
        int r2 = pl1->b.r.circleBorder;
        int x2 = pl1->b.r.xo + pl1->b.r.width/2;
        int y2 = y1 < pl1->b.r.yo + pl1->b.r.circleBorder?  pl1->b.r.yo + pl1->b.r.circleBorder : y1 > pl1->b.r.yo + pl1->b.r.heigth - pl1->b.r.circleBorder ? pl1->b.r.yo + pl1->b.r.heigth - pl1->b.r.circleBorder :-1;
        if ( y2 != -1 )
        {
          if ( intersectionCircles( r1,x1,y1,r2,x2,y2 ) )
          {
            bl->xdir = x1 >= x2 ? BALL_DIR_RIGHT : BALL_DIR_LEFT;
            bl->ydir = y1 <= y2 ? BALL_DIR_UP : BALL_DIR_DOWN;
            countPong+= 1;
          }
        }
      }
    }
  }
  if ( bl->xdir == BALL_DIR_RIGHT )
  {
    if(  bl->c.xo + bl->c.radius >= pl2->b.r.xo )
    {
      if (  bl->c.yo <= pl2->b.r.yo + pl2->b.r.heigth - pl2->b.r.circleBorder 
            && bl->c.yo >= pl2->b.r.yo + pl2->b.r.circleBorder && bl->c.xo - bl->c.radius  < pl2->b.r.xo + pl2->b.r.width )
      { 
        bl->xdir = BALL_DIR_LEFT;
        countPong+= 1;
      }
      else
      {
        int r1 = bl->c.radius;
        int x1 = bl->c.xo;
        int y1 = bl->c.yo;
        int r2 = pl2->b.r.circleBorder;
        int x2 = pl2->b.r.xo + pl2->b.r.width/2;
        int y2 = y1 < pl1->b.r.yo + pl2->b.r.circleBorder?  pl2->b.r.yo + pl2->b.r.circleBorder : y1 > pl2->b.r.yo + pl2->b.r.heigth - pl2->b.r.circleBorder ? pl2->b.r.yo + pl2->b.r.heigth - pl2->b.r.circleBorder :-1;
        if ( y2 != -1 )
        {
          if ( intersectionCircles( r1,x1,y1,r2,x2,y2 ) )
          {
            bl->xdir = x1 >= x2 ? BALL_DIR_RIGHT : BALL_DIR_LEFT;
            bl->ydir = y1 <= y2 ? BALL_DIR_UP : BALL_DIR_DOWN;
            countPong+= 1;
          }
        }
      }
    }
  }
  return -1;
}

int screenGame_verifyScore( )
{
  if ( blGame.c.xo >= blGame.bll.X_RigthLimit )
  {
    gpong.pl1Score += 1;
    sprintf( scoreGameTable.t.text , "%02d-%02d" , gpong.pl1Score, gpong.pl2Score);
    button_draw(&scoreGameTable);
    blGame.step = 5;
  }
  else if( blGame.c.xo <= blGame.bll.X_LeftLimit  )
  {
    gpong.pl2Score += 1;
    sprintf( scoreGameTable.t.text , "%02d-%02d" , gpong.pl1Score, gpong.pl2Score);
    button_draw(&scoreGameTable);
    blGame.step = 5;
  }
}

int checkBallSpeed( )
{
  if ( countPong % 5 == 0 && countPong > 0)
  {
    blGame.step += 1;
    countPong = 0;
  }
  return -1;
}

int movePlayer(struct joystick *js)
{
  if ( js->adc_y < 500  ){
    pl1Game.riseDirection = PLAYER_DIR_DOWN;
    if ( pl1Game.b.r.yo < pl1Game.downLimit  ) player_move( &pl1Game );
    else rectangle_draw( &pl1Game.b.r );
  } else  if ( js->adc_y > 3500  ){
    pl1Game.riseDirection = PLAYER_DIR_UP;
    if ( pl1Game.b.r.yo > pl1Game.upLimit  ) player_move( &pl1Game );
    else rectangle_draw( &pl1Game.b.r );
  }
  else{
    rectangle_draw( &pl1Game.b.r );
  }
}

int checkTimer()
{
  timeCounter_verifyTimer(&timerTock);
  if (  timerTock.timerReached )
  {
    uint16_t totalseconds = gpong.timeMinutes*MIN_TO_SECONDS + gpong.timeSeconds;
    totalseconds += gspong.mode == MODE_TIMER?-1:1;
    gpong.timeMinutes = (int)totalseconds/MIN_TO_SECONDS;
    gpong.timeSeconds = totalseconds%MIN_TO_SECONDS;
    sprintf( timerTable.t.text , "%02d:%02d" , gpong.timeMinutes, gpong.timeSeconds );
    button_draw(&timerTable);
    timeCounter_resetTimer(&timerTock);
  }
  return -1;
}

int screenGame_eval(struct screenManager *sm)
{
  if ( changeScreen ){
    sm->actualScreen = 3;
    changeScreen = false;
    return -1;
  }
  joystick_getValuesByTimer(&js3 , movePlayer );
  player_animation( &pl2Game );
  ball_animation(&blGame);
  screenGame_verifyScore( );
  ball_direction(&blGame);
  screenGame_collision(&pl1Game , &pl2Game , &blGame );
  checkBallSpeed( );
  checkTimer();
  if ( gspong.mode == MODE_TIMER ){
    if ( gpong.timeMinutes == 0 && gpong.timeSeconds == 0){
      blGame.c.backgroundColor = WHITE;
      circle_draw(&blGame.c);
      strcpy( centerText.t.text, "TIME!" );
      centerText.t.size = 3;
      button_draw(&centerText);
      HAL_Delay(1000);
      if (  gpong.pl1Score != gpong.pl2Score )
      {
        strcpy( centerText.t.text, "WINNER:" );
        centerText.t.size = 2;
        button_draw(&centerText);
        if ( gpong.pl1Score > gpong.pl2Score )
        {
          strcpy( centerText.t.text, "Player 1" );
        }
        else {
          strcpy( centerText.t.text, "Player 2" );
        }
        //strcpy( centerText.t.text, "Player 1" );
        centerText.t.yo += 50;
        centerText.t.xo -= 10;
        text_draw( &centerText.t );
        centerText.t.yo -= 50;
        centerText.t.xo += 10;
        HAL_Delay(2000);
        //rectangle_draw( &centerText.r );
        button_draw(&buttonExitGame);
        button_draw(&buttonNewGame);
        triangle_draw( &selectorGame );
        while (1)
        {
          joystick_getValuesByTimer(&js3 , checkButtonsGame );
          if ( btnNewGameVal == 1 )
          {
            screenGame_show();
            break;
          }
          else if ( btnExitVal == 1 )
          {
            changeScreen = true;
            break;
          }
        }
      }
      else{
        strcpy( centerText.t.text, "TIE!" );
        button_draw(&centerText);
        HAL_Delay(2000);
        button_draw(&buttonExitGame);
        button_draw(&buttonNewGame);
        triangle_draw( &selectorGame );
        while (1)
        {
          joystick_getValuesByTimer(&js3 , checkButtonsGame );
          if ( btnNewGameVal == 1 )
          {
            screenGame_show();
            break;
          }
          else if ( btnExitVal == 1 )
          {
            changeScreen = true;
            break;
          }
        }
      }
    }
  }
  else{
    if ( gspong.mode == MODE_SCORE )
    {
      if ( gpong.pl1Score == gspong.score  || gpong.pl2Score == gspong.score )
      {
        blGame.c.backgroundColor = WHITE;
        circle_draw(&blGame.c);
        strcpy( centerText.t.text, "WINNER:" );
        centerText.t.size = 2;
        button_draw(&centerText);
        if ( gpong.pl1Score == gspong.score )
        {
          strcpy( centerText.t.text, "Player 1" );
        }
        else if ( gpong.pl2Score == gspong.score  ) {
          strcpy( centerText.t.text, "Player 2" );
        }
        //strcpy( centerText.t.text, "Player 1" );
        centerText.t.yo += 50;
        centerText.t.xo -= 10;
        text_draw( &centerText.t );
        centerText.t.yo -= 50;
        centerText.t.xo += 10;
        HAL_Delay(2000);
        //rectangle_draw( &centerText.r );
        button_draw(&buttonExitGame);
        button_draw(&buttonNewGame);
        triangle_draw( &selectorGame );
        while (1)
        {
          joystick_getValuesByTimer(&js3 , checkButtonsGame );
          if ( btnNewGameVal == 1 )
          {
            screenGame_show();
            break;
          }
          else if ( btnExitVal == 1 )
          {
            changeScreen = true;
            break;
          }
        }
      } 
    }
  }
  if ( !js3.sw ){
    modalPause();
  }
  HAL_Delay(1);
  return -1;
}

int screenGame_show()
{
  int err = -1;

  //struct text introtext;

  fillScreen(WHITE);
  
  /*introtext.color = BLACK;
  introtext.f = mono12x7bold;
  introtext.size = 2;
  strcpy( introtext.text, "PONG GAME" );
  introtext.xo = 140;
  introtext.yo = 40;
  text_draw(&introtext);*/

  screenSettings_getSettings( &gspong);

  gpong.pl1Score = 0;
  gpong.pl2Score = 0;
  gpong.timeMinutes = gspong.mode == MODE_TIMER? gspong.time_minutes:0;
  gpong.timeSeconds = gspong.mode == MODE_TIMER? gspong.time_seconds:0;
  gpong.tm.delay = 1000;
  timeCounter_init(&gpong.tm);

  gpong.pl1Score = 0;
  gpong.pl2Score = 0;

  btnNewGameVal = 0;
  btnExitVal = 0;

  scoreGameTable.r.backgroundColor = WHITE;
  scoreGameTable.r.borderColor = 0;
  scoreGameTable.r.borderSize = 0;
  scoreGameTable.r.circleBorder = 10;
  scoreGameTable.r.xo = 150;
  scoreGameTable.r.yo = 10;
  scoreGameTable.r.width = 150;
  scoreGameTable.r.heigth = 50;
  scoreGameTable.t.color = BLACK;
  scoreGameTable.t.f = mono12x7bold;
  scoreGameTable.t.size = 2;
  sprintf( scoreGameTable.t.text , "%02d-%02d" , gpong.pl1Score, gpong.pl2Score);
  scoreGameTable.t.xo = 160;
  scoreGameTable.t.yo = 40;
  scoreGameTable.isPressed = false;
  scoreGameTable.pressedColor = WHITE;
  scoreGameTable.pressedTextColor = BLACK;
  scoreGameTable.releasedColor = BLACK;
  scoreGameTable.releasedTextColor = WHITE;
  scoreGameTable.tm.tStart = 500;

  button_draw(&scoreGameTable);

  if (gspong.mode == MODE_SCORE)
  {
    struct text introtext;

    introtext.color = BLACK;
    introtext.f = mono12x7bold;
    introtext.size = 1;
    sprintf( introtext.text , "Score:%02d" , gspong.score);
    //strcpy( introtext.text, "PONG GAME" );
    introtext.xo = 10;
    introtext.yo = 30;
    text_draw(&introtext);
  }

  buttonExitGame.r.backgroundColor = RED;
  buttonExitGame.r.borderColor = 0;
  buttonExitGame.r.borderSize = 0;
  buttonExitGame.r.circleBorder = 10;
  buttonExitGame.r.xo = 300;
  buttonExitGame.r.yo = 280;
  buttonExitGame.r.width = 80;
  buttonExitGame.r.heigth = 30;
  buttonExitGame.t.color = WHITE;
  buttonExitGame.t.f = mono12x7bold;
  buttonExitGame.t.size = 1;
  strcpy(  buttonExitGame.t.text , "EXIT");
  buttonExitGame.t.xo = 310;
  buttonExitGame.t.yo = 300;
  buttonExitGame.isPressed = false;
  buttonExitGame.pressedColor = WHITE;
  buttonExitGame.pressedTextColor = RED;
  buttonExitGame.releasedColor = RED;
  buttonExitGame.releasedTextColor = WHITE;
  buttonExitGame.tm.tStart = 500;

  //button_draw(&buttonExitGame);

  buttonNewGame.r.backgroundColor = BLUE;
  buttonNewGame.r.borderColor = 0;
  buttonNewGame.r.borderSize = 0;
  buttonNewGame.r.circleBorder = 10;
  buttonNewGame.r.xo = 50;
  buttonNewGame.r.yo = 280;
  buttonNewGame.r.width = 140;
  buttonNewGame.r.heigth = 30;
  buttonNewGame.t.color = WHITE;
  buttonNewGame.t.f = mono12x7bold;
  buttonNewGame.t.size = 1;
  strcpy(  buttonNewGame.t.text , "NEW GAME");
  buttonNewGame.t.xo = 60;
  buttonNewGame.t.yo = 300;
  buttonNewGame.isPressed = false;
  buttonNewGame.pressedColor = WHITE;
  buttonNewGame.pressedTextColor = BLUE;
  buttonNewGame.releasedColor = BLUE;
  buttonNewGame.releasedTextColor = WHITE;
  buttonNewGame.tm.tStart = 500;

  //button_draw(&buttonNewGame);
  
  timerTable.r.backgroundColor = BLACK;
  timerTable.r.borderColor =   0;
  timerTable.r.borderSize =0;
  timerTable.r.circleBorder = 5;
  timerTable.r.xo = 390;
  timerTable.r.yo = 10;
  timerTable.r.width = 80;
  timerTable.r.heigth = 30;
  timerTable.t.color = WHITE;
  timerTable.t.f = mono12x7bold;
  timerTable.t.size = 1;
  sprintf( timerTable.t.text , "%02d:%02d" ,gpong.timeMinutes, gpong.timeSeconds);
  //strcpy(  timerTable.t.text , "0:00");
  timerTable.t.xo = 395;
  timerTable.t.yo = 30;
  timerTable.isPressed = false;
  timerTable.pressedColor = BLACK;
  timerTable.pressedTextColor = WHITE;
  timerTable.releasedColor = BLUE;
  timerTable.releasedTextColor = WHITE;
  timerTable.tm.tStart = 500;

  button_draw(&timerTable);

  pl1Game.b.r.backgroundColor=BLUE;
  pl1Game.b.r.borderColor = 0;
  pl1Game.b.r.borderSize = 0;
  pl1Game.b.r.circleBorder = 10;
  pl1Game.b.r.heigth = 100;
  pl1Game.b.r.width = 20;
  pl1Game.b.r.xo = 40;
  pl1Game.b.r.yo = LOW_LIMIT_BARR - 75;
  pl1Game.b.tm.delay = DELAY_BAR_TIMER_MILLIS +15;
  pl1Game.downLimit = LOW_LIMIT_BARR;
  pl1Game.upLimit = HIGH_LIMIT_BARR;
  pl1Game.riseDirection = PLAYER_DIR_UP;

  player_init(&pl1Game);

  pl2Game.b.r.backgroundColor=BLUE;
  pl2Game.b.r.borderColor = 0;
  pl2Game.b.r.borderSize = 0;
  pl2Game.b.r.circleBorder = 10;
  pl2Game.b.r.heigth = 100;
  pl2Game.b.r.width = 20;
  pl2Game.b.r.xo = 420;
  pl2Game.b.r.yo = LOW_LIMIT_BARR - 75;
  pl2Game.b.tm.delay = DELAY_BAR_TIMER_MILLIS +15;
  pl2Game.downLimit = LOW_LIMIT_BARR;
  pl2Game.upLimit = HIGH_LIMIT_BARR;
  pl2Game.riseDirection = PLAYER_DIR_DOWN;

  player_init(&pl2Game);

  blGame.c.backgroundColor = RED;
  blGame.c.borderColor = 0;
  blGame.c.borderSize = 0;
  blGame.c.radius = 10;
  blGame.c.xo = 240;
  blGame.c.yo = 160;
  blGame.tc.delay = 1;
  blGame.step = 5;
  blGame.xdir = BALL_DIR_LEFT;
  blGame.ydir = BALL_DIR_UP;
  blGame.bll.X_LeftLimit = 10;
  blGame.bll.X_RigthLimit = 470;
  blGame.bll.Y_DownLimit = LOW_LIMIT_BARR + 100;
  blGame.bll.Y_UpLimit = HIGH_LIMIT_BARR;
  blGame.xInit = 240;
  blGame.yInit = 160;

  js3.sw_port = JS_SW_GPIO_Port;
  js3.swPin = JS_SW_Pin;
  js3.hadc_js = &hadc1;
  js3.adcChannels[0] = 12;
  js3.adcChannels[1] = 13;

  js3.tm.delay = 25;

  selectorGame.x0 = 20;
  selectorGame.y0 = 280;
  selectorGame.x1 = 20;
  selectorGame.y1 = 300;
  selectorGame.x2 = 40;
  selectorGame.y2 = 290;
  selectorGame.backgroundColor = RED;
  selectorGame.borderColor = 0;
  selectorGame.borderSize = 0;

  centerText.r.backgroundColor = WHITE;
  centerText.r.borderColor = 0;
  centerText.r.borderSize = 0;
  centerText.r.circleBorder = 10;
  centerText.r.xo = 80;
  centerText.r.yo = 80;
  centerText.r.width = 330;
  centerText.r.heigth = 170;
  centerText.t.color = BLACK;
  centerText.t.f = mono12x7bold;
  centerText.t.size = 5;
  //strcpy( centerText.t.text, "3" );
  centerText.t.xo = 190;
  centerText.t.yo = 180;

  HAL_Delay(1000);
  showCount();
  
  ball_init(&blGame);

  timerTock.delay = 1000;
  timeCounter_init(&timerTock);
  timeCounter_initTimer(&timerTock);

}

int screenGame_init( struct screenManager *sm  )
{
  int err = -1;
  sm->s.tc.delay = 0;
  err = screenGame_show();
  return err;
}
