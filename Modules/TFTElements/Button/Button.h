#ifndef __BUTTON_H__
#define __BUTTON_H__

#include "moduleInit.h"
#include "Rectangle.h"
#include "Text.h"
#include "TimeCounter.h"

struct button
{
  struct Rectangle r;
  struct text t;
  bool isPressed;
  uint16_t pressedColor;
  uint16_t releasedColor;
  uint16_t pressedTextColor;
  uint16_t releasedTextColor;
  struct timeCounter tm;
};

int button_init( struct button *btn);
int button_draw( struct button *btn );

#endif