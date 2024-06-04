#ifndef __JOYSTICK_H__
#define __JOYSTICK_H__

#include "moduleInit.h"
#include "TimeCounter.h"

struct joystick
{
  uint16_t adc_X;
  uint16_t adc_y;
  bool sw;
  uint16_t swPin;
  uint8_t adcChannels[2];// vrx , vry
  ADC_HandleTypeDef *hadc_js;
  GPIO_TypeDef *sw_port;
  struct timeCounter tm;
};

int joystick_init( struct joystick *js);
int joystick_getADCvalues(struct joystick *js);
int joystick_getSWvalue(struct joystick *js);
int joystick_getValuesByTimer( struct joystick *js , void (*f)(struct joystick *js ) );

#endif