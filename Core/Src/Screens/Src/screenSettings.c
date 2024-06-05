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

#define INIT_POS_YO_MODE 95
#define SELECTOR_DISTANCE 20 
#define SELECTOR_INIT_POS_X 10
#define SELECTOR_END_POS_X 30
#define SELECTOR_STEP_DIST 60 

struct button modeTime;
struct button modeScore;
struct button timerSel;
struct button scoreSel;
struct button buttonExit;
struct triangle selector2;
struct joystick js2;
struct gameSetting gs = { MODE_TIMER, 2, 30, 2 };

uint8_t actual_position_option = 0;

int setupOption( int opt )
{
  if ( opt == 1 )
  {
    modeTime.r.backgroundColor = gs.mode == MODE_TIMER?WHITE:BLUE;
    modeTime.r.borderColor = gs.mode == MODE_TIMER?BLUE:0;
    modeTime.r.borderSize = gs.mode == MODE_TIMER?5:0;
    modeTime.t.color = gs.mode == MODE_TIMER?BLUE:WHITE;

    modeScore.r.backgroundColor = gs.mode == MODE_SCORE?WHITE:BLUE;
    modeScore.r.borderColor = gs.mode == MODE_SCORE?BLUE:0;
    modeScore.r.borderSize = gs.mode == MODE_SCORE?5:0;
    modeScore.t.color = gs.mode == MODE_SCORE?BLUE:WHITE;

    button_draw(&modeTime);
    button_draw(&modeScore);
  }
  else if ( opt == 2 )
  {
    timerSel.r.backgroundColor = WHITE;
    timerSel.r.borderColor = BLUE;
    timerSel.r.borderSize = 2;
    timerSel.t.color = BLUE;
    button_draw(&timerSel);
  }
  else if ( opt == 3 )
  {
    scoreSel.r.backgroundColor = WHITE;
    scoreSel.r.borderColor = BLUE;
    scoreSel.r.borderSize = 2;
    scoreSel.t.color = BLUE;
    button_draw(&scoreSel);
  }
  else if ( opt == 4 )
  {
    buttonExit.r.backgroundColor = WHITE;
    buttonExit.r.borderColor = RED;
    buttonExit.r.borderSize = 2;
    buttonExit.t.color = RED;
    button_draw(&buttonExit);
  }
}

int checkPostionJoystick( struct joystick *js )
{
  if ( actual_position_option == 0 || actual_position_option == 2  || actual_position_option == 3)
  {
    if ( js->adc_y >= 500 && js->adc_y <= 3500  )
    {
      if (!js->sw) return -1;
      if ( js->tm.delay == 250 ) js->tm.delay = 50;
      return 1;
    }
  }
  else if ( actual_position_option == 1 )
  {
    if ( js->adc_X >= 500 && js->adc_X <= 3500  )
    {
      if (!js->sw) return -1;
      if ( js->tm.delay == 250 ) js->tm.delay = 50;
      return 1;
    }
    else if ( js->adc_X>= 500 && js->adc_X <= 3500  ) return 1;
  }
  return -1;
}

void checkOptions(struct joystick *js)
{
  int err = checkPostionJoystick(js);
  if (err == 1) return;
  if (  actual_position_option == 0 )
  {
    if( js->adc_y < 500 && selector2.y0 <  INIT_POS_YO_MODE + 3*SELECTOR_STEP_DIST )
    {
      selector2.backgroundColor = WHITE;
      triangle_draw(&selector2);
      selector2.y0 += SELECTOR_STEP_DIST;
      selector2.y1 += SELECTOR_STEP_DIST;
      selector2.y2 += SELECTOR_STEP_DIST;
      selector2.backgroundColor = RED;
      triangle_draw(&selector2);
      if (  js->tm.delay == 50 ) js->tm.delay = 250;
    } else if( js->adc_y > 3500 && selector2.y0 >  INIT_POS_YO_MODE )
    {
      selector2.backgroundColor = WHITE;
      triangle_draw(&selector2);
      selector2.y0 -= SELECTOR_STEP_DIST;
      selector2.y1 -= SELECTOR_STEP_DIST;
      selector2.y2 -= SELECTOR_STEP_DIST;
      selector2.backgroundColor = RED;
      triangle_draw(&selector2);
      if (  js->tm.delay == 50 ) js->tm.delay = 250;
    }
    else if ( js->adc_y >= 500 && js->adc_y <= 3500 && !js->sw)  {
      if ( !js->sw ) actual_position_option = (selector2.y0 - INIT_POS_YO_MODE)/SELECTOR_STEP_DIST + 1;
      while (!js->sw) joystick_getSWvalue(js);
      setupOption( actual_position_option );
      selector2.backgroundColor = GREEN;
      triangle_draw(&selector2);
      timeCounter_resetTimer( &js->tm );
    }
  }
  else if ( actual_position_option == 1  )
  {
    if ( js->adc_X >= 500 && js->adc_X <= 3500  && !js->sw )
    {
      while (!js->sw) joystick_getSWvalue(js);
      actual_position_option = 0;

      modeTime.r.borderSize = gs.mode == MODE_TIMER?2:0;
      modeScore.r.borderSize = gs.mode == MODE_SCORE?2:0;;

      button_draw(&modeTime);
      button_draw(&modeScore);

      selector2.backgroundColor = RED;
      triangle_draw(&selector2);
      timeCounter_resetTimer( &js->tm );
    }
    else{
      uint8_t prev_mode = gs.mode;
      gs.mode = js->adc_X > 3500 && gs.mode == MODE_TIMER ? MODE_SCORE : js->adc_X < 500 && gs.mode == MODE_SCORE ? MODE_TIMER: gs.mode;
      if ( prev_mode != gs.mode )setupOption(1);
    }
  } 
  else if ( actual_position_option == 2  )
  {
    if ( js->adc_X >= 500 && js->adc_X <= 3500  && !js->sw )
    {
      while (!js->sw) joystick_getSWvalue(js);
      actual_position_option = 0;

      timerSel.r.backgroundColor = BLUE;
      timerSel.r.borderColor = 0;
      timerSel.r.borderSize = 0;
      timerSel.t.color = WHITE;
      button_draw(&timerSel);

      selector2.backgroundColor = RED;
      triangle_draw(&selector2);

      timeCounter_resetTimer( &js->tm );
    }
    else{
      uint16_t totalseconds = gs.time_minutes*MIN_TO_SECONDS + gs.time_seconds;
      totalseconds += totalseconds < MAX_MINUTES*MIN_TO_SECONDS && js->adc_y > 3500? TIMER_STEP : totalseconds > MIN_SECONDS && js->adc_y < 500 ? -TIMER_STEP: 0;
      gs.time_minutes = (int)totalseconds/MIN_TO_SECONDS;
      gs.time_seconds = totalseconds%MIN_TO_SECONDS;
      sprintf( timerSel.t.text , "%02d:%02d" , gs.time_minutes, gs.time_seconds );
      button_draw(&timerSel);
      if (  js->tm.delay == 50 ) js->tm.delay = 250;
    }
  }
  else if ( actual_position_option == 3  )
  {
    if ( js->adc_X >= 500 && js->adc_X <= 3500  && !js->sw )
    {
      while (!js->sw) joystick_getSWvalue(js);
      actual_position_option = 0;

      scoreSel.r.backgroundColor = BLUE;
      scoreSel.r.borderColor = 0;
      scoreSel.r.borderSize = 0;
      scoreSel.t.color = WHITE;
      button_draw(&scoreSel);

      selector2.backgroundColor = RED;
      triangle_draw(&selector2);

      timeCounter_resetTimer( &js->tm );
    }
    else{
      uint16_t totalscore = gs.score;
      totalscore += totalscore < MAX_SCORE && js->adc_y > 3500? 1 : totalscore > 2 && js->adc_y < 500 ? -1: 0;
      gs.score = totalscore;
      sprintf( scoreSel.t.text , "%02d" , gs.score );
      button_draw(&scoreSel);
      if (  js->tm.delay == 50 ) js->tm.delay = 250;
    }

    
  }
}

int screenSettings_eval(struct screenManager *sm)
{
  joystick_getValuesByTimer(&js2 , checkOptions );
  if( actual_position_option == 4 ){
    sm->actualScreen = 3;
    return -1;
  }
  joystick_getADCvalues(&js2);
  checkPostionJoystick(&js2);
  HAL_Delay(1);
  return -1;
}

int screenSettings_show()
{
  struct text introtext;
  struct text modetext;
  struct text timertext;
  struct text scoretext;

  introtext.color = BLACK;
  introtext.f = mono12x7bold;
  introtext.size = 3;
  strcpy( introtext.text, "Settings" );
  introtext.xo = 60;
  introtext.yo = 40;

  modetext.color = BLACK;
  modetext.f = mono12x7bold;
  modetext.size = 1;
  strcpy( modetext.text, "Mode:" );
  modetext.xo = 60;
  modetext.yo = 110;

  timertext.color = BLACK;
  timertext.f = mono12x7bold;
  timertext.size = 1;
  strcpy( timertext.text, "Timer:" );
  timertext.xo = 60;
  timertext.yo = 175;
  
  scoretext.color = BLACK;
  scoretext.f = mono12x7bold;
  scoretext.size = 1;
  strcpy( scoretext.text, "Score:" );
  scoretext.xo = 60;
  scoretext.yo = 235;

  fillScreen(WHITE);
  text_draw(&introtext);
  text_draw(&modetext);
  text_draw(&timertext);
  text_draw(&scoretext);

  modeTime.r.backgroundColor = gs.mode == MODE_TIMER?WHITE:BLUE;
  modeTime.r.borderColor = gs.mode == MODE_TIMER?BLUE:0;
  modeTime.r.borderSize = gs.mode == MODE_TIMER?1:0;
  modeTime.r.circleBorder = 5;
  modeTime.r.xo = 150;
  modeTime.r.yo = 90;
  modeTime.r.width = 90;
  modeTime.r.heigth = 30;
  modeTime.t.color = gs.mode == MODE_TIMER?BLUE:WHITE;
  modeTime.t.f = mono12x7bold;
  modeTime.t.size = 1;
  strcpy(  modeTime.t.text , "TIMER");
  modeTime.t.xo = 160;
  modeTime.t.yo = 110;
  modeTime.isPressed = false;
  modeTime.pressedColor = BLACK;
  modeTime.pressedTextColor = WHITE;
  modeTime.releasedColor = BLUE;
  modeTime.releasedTextColor = WHITE;
  modeTime.tm.tStart = 500;

  button_draw(&modeTime);

  modeScore.r.backgroundColor = gs.mode == MODE_SCORE?WHITE:BLUE;
  modeScore.r.borderColor = gs.mode == MODE_SCORE?BLUE:0;
  modeScore.r.borderSize = gs.mode == MODE_SCORE?2:0;
  modeScore.r.circleBorder = 5;
  modeScore.r.xo = 280;
  modeScore.r.yo = 90;
  modeScore.r.width = 90;
  modeScore.r.heigth = 30;
  modeScore.t.color = gs.mode == MODE_SCORE?BLUE:WHITE;
  modeScore.t.f = mono12x7bold;
  modeScore.t.size = 1;
  strcpy(  modeScore.t.text , "SCORE");
  modeScore.t.xo = 290;
  modeScore.t.yo = 110;
  modeScore.isPressed = false;
  modeScore.pressedColor = BLACK;
  modeScore.pressedTextColor = WHITE;
  modeScore.releasedColor = BLUE;
  modeScore.releasedTextColor = WHITE;
  modeScore.tm.tStart = 500;

  button_draw(&modeScore);

  timerSel.r.backgroundColor = BLUE;
  timerSel.r.borderColor =   0;
  timerSel.r.borderSize =0;
  timerSel.r.circleBorder = 5;
  timerSel.r.xo = 160;
  timerSel.r.yo = 155;
  timerSel.r.width = 80;
  timerSel.r.heigth = 30;
  timerSel.t.color = WHITE;
  timerSel.t.f = mono12x7bold;
  timerSel.t.size = 1;
  sprintf( timerSel.t.text , "%02d:%02d" , gs.time_minutes, gs.time_seconds );
  //strcpy(  timerSel.t.text , "0:00");
  timerSel.t.xo = 170;
  timerSel.t.yo = 175;
  timerSel.isPressed = false;
  timerSel.pressedColor = BLACK;
  timerSel.pressedTextColor = WHITE;
  timerSel.releasedColor = BLUE;
  timerSel.releasedTextColor = WHITE;
  timerSel.tm.tStart = 500;

  button_draw(&timerSel);

  struct text minutestext;

  minutestext.color = BLACK;
  minutestext.f = mono12x7bold;
  minutestext.size = 1;
  strcpy( minutestext.text, "M:SS" );
  minutestext.xo = 250;
  minutestext.yo = 175;

  text_draw(&minutestext);

  scoreSel.r.backgroundColor = BLUE;;
  scoreSel.r.borderColor = 0;
  scoreSel.r.borderSize = 0;
  scoreSel.r.circleBorder = 5;
  scoreSel.r.xo = 160;
  scoreSel.r.yo = 215;
  scoreSel.r.width = 45;
  scoreSel.r.heigth = 30;
  scoreSel.t.color = WHITE;
  scoreSel.t.f = mono12x7bold;
  scoreSel.t.size = 1;
  sprintf( scoreSel.t.text , "%02d" , gs.score );
  //strcpy(  scoreSel.t.text , "0");
  scoreSel.t.xo = 170;
  scoreSel.t.yo = 235;
  scoreSel.isPressed = false;
  scoreSel.pressedColor = BLACK;
  scoreSel.pressedTextColor = WHITE;
  scoreSel.releasedColor = BLUE;
  scoreSel.releasedTextColor = WHITE;
  scoreSel.tm.tStart = 500;

  button_draw(&scoreSel);

  buttonExit.r.backgroundColor = RED;
  buttonExit.r.borderColor = 0;
  buttonExit.r.borderSize = 0;
  buttonExit.r.circleBorder = 10;
  buttonExit.r.xo = 40;
  buttonExit.r.yo = 260;
  buttonExit.r.width = 80;
  buttonExit.r.heigth = 50;
  buttonExit.t.color = WHITE;
  buttonExit.t.f = mono12x7bold;
  buttonExit.t.size = 1;
  strcpy(  buttonExit.t.text , "EXIT");
  buttonExit.t.xo = 50;
  buttonExit.t.yo = 290;
  buttonExit.isPressed = false;
  buttonExit.pressedColor = BLACK;
  buttonExit.pressedTextColor = WHITE;
  buttonExit.releasedColor = CYAN;
  buttonExit.releasedTextColor = WHITE;
  buttonExit.tm.tStart = 500;

  button_draw(&buttonExit);

  selector2.x0 = SELECTOR_INIT_POS_X;
  selector2.y0 = INIT_POS_YO_MODE;
  selector2.x1 = SELECTOR_INIT_POS_X;
  selector2.y1 = INIT_POS_YO_MODE + SELECTOR_DISTANCE;
  selector2.x2 = SELECTOR_END_POS_X;
  selector2.y2 = INIT_POS_YO_MODE + SELECTOR_DISTANCE/2 ;
  selector2.backgroundColor = RED;
  selector2.borderColor = 0;
  selector2.borderSize = 0;

  triangle_draw( &selector2 );

  js2.sw_port = JS_SW_GPIO_Port;
  js2.swPin = JS_SW_Pin;
  js2.hadc_js = &hadc1;
  js2.adcChannels[0] = 12;
  js2.adcChannels[1] = 13;

  js2.tm.delay = 50;

  joystick_init(&js2);

  actual_position_option = 0;
}

int screenSettings_init( struct screenManager *sm )
{
  int err = -1;
  sm->s.tc.delay = 0;
  err = screenSettings_show();
  return err;
}
