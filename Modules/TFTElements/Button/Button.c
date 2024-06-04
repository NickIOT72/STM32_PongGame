#include "Button.h"
#include "fonts.h"
#include "tft.h"
#include "functions.h"

int button_init( struct button *btn)
{
  button_draw(btn);
  timeCounter_init(&btn->tm);
  return -1;
}

int button_draw( struct button *btn )
{
  rectangle_draw(&btn->r);
  text_draw( &btn->t );
  return -1;
}