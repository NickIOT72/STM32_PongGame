#include "Player.h"
#include "TimeCounter.h"
#include "listColors.h"
#include "fonts.h"
#include "tft.h"
#include "functions.h"

#define STEP 2 

int player_init( struct player *pl)
{
  bar_init(&pl->b);
  return -1;
}

int player_move( struct player *pl )
{
  pl->riseDirection?fillRect( pl->b.r.xo , pl->b.r.yo +  pl->b.r.heigth - pl->b.r.circleBorder , pl->b.r.width , pl->b.r.circleBorder, WHITE):fillRect( pl->b.r.xo , pl->b.r.yo , pl->b.r.width , pl->b.r.circleBorder, WHITE);
  pl->b.r.yo += pl->riseDirection ? -STEP: +STEP;
  rectangle_draw( &pl->b.r );
  return -1;
}

int player_animation( struct player *pl )
{
  timeCounter_verifyTimer(&pl->b.tm);
  if ( pl->b.tm.timerReached  )
  {
    if(  pl->b.r.yo > pl->upLimit && pl->riseDirection)
    {
      //pl->b.r.backgroundColor = WHITE;
      //rectangle_draw( &pl->b.r );
      //pl->b.r.backgroundColor = BLUE;
      //pl->b.r.yo -= 3;
      //rectangle_draw( &pl->b.r );
      
      fillRect( pl->b.r.xo , pl->b.r.yo +  pl->b.r.heigth - pl->b.r.circleBorder , pl->b.r.width , pl->b.r.circleBorder, WHITE);
      pl->b.r.yo -= STEP;
      rectangle_draw( &pl->b.r );
      //fillCircle( pl->b.r.xo+  pl->b.r.width/2 , pl->b.r.yo +  pl->b.r.heigth - pl->b.r.circleBorder - STEP ,pl->b.r.circleBorder , pl->b.r.backgroundColor );
      //fillRect( pl->b.r.xo , pl->b.r.yo +  pl->b.r.heigth - 2*pl->b.r.circleBorder - STEP , pl->b.r.width , pl->b.r.circleBorder , pl->b.r.backgroundColor);
      //fillRect( pl->b.r.xo , pl->b.r.yo - STEP  , pl->b.r.width , STEP , pl->b.r.backgroundColor);
      //fillCircle( pl->b.r.xo+  pl->b.r.width/2 , pl->b.r.yo - STEP ,pl->b.r.circleBorder , pl->b.r.backgroundColor );
      

      //pl->b.r.yo -= STEP;

      pl->riseDirection  = !(pl->b.r.yo <= pl->upLimit );
    }
    else if (pl->b.r.yo < pl->downLimit && !pl->riseDirection)
    {
      //pl->b.r.backgroundColor = WHITE;
      //rectangle_draw( &pl->b.r );
      //pl->b.r.backgroundColor = BLUE;
      //pl->b.r.yo += 3;
      //rectangle_draw( &pl->b.r );
      
      fillRect( pl->b.r.xo , pl->b.r.yo , pl->b.r.width , pl->b.r.circleBorder, WHITE);
      pl->b.r.yo += STEP;
      rectangle_draw( &pl->b.r );

      //fillRect( pl->b.r.xo , pl->b.r.yo +  pl->b.r.heigth, pl->b.r.width , pl->b.r.circleBorder*2 , pl->b.r.backgroundColor);
      //fillCircle( pl->b.r.xo+  pl->b.r.width/2 , pl->b.r.yo +  pl->b.r.heigth - pl->b.r.circleBorder*2 ,pl->b.r.circleBorder , pl->b.r.backgroundColor );
      //fillRect( pl->b.r.xo , pl->b.r.yo + pl->b.r.circleBorder , pl->b.r.width , pl->b.r.circleBorder*2 , pl->b.r.backgroundColor);
      //fillCircle( pl->b.r.xo+  pl->b.r.width/2 , pl->b.r.yo +  pl->b.r.heigth - pl->b.r.circleBorder*2 ,pl->b.r.circleBorder , pl->b.r.backgroundColor );

      pl->riseDirection = (pl->b.r.yo >= pl->downLimit);  
    }
    timeCounter_resetTimer(&pl->b.tm);
  }
  return -1;
}