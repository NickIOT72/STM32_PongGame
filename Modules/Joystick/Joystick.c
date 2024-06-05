#include "Joystick.h"

void Error_Handler_js(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

int joystick_getADCvalues(struct joystick *js)
{
  /*HAL_ADC_Start(js->hadc_js);
  HAL_ADC_PollForConversion( js->hadc_js,HAL_MAX_DELAY );
  if ( js->adcChannels[0] < js->adcChannels[1])
  {
    js->adc_y = HAL_ADC_GetValue(js->hadc_js);
    HAL_ADC_PollForConversion( js->hadc_js,HAL_MAX_DELAY );
    js->adc_X = HAL_ADC_GetValue(js->hadc_js);
  }
  else{
    js->adc_X = HAL_ADC_GetValue(js->hadc_js);
    HAL_ADC_PollForConversion( js->hadc_js,HAL_MAX_DELAY );
    js->adc_y = HAL_ADC_GetValue(js->hadc_js);
  }
  HAL_ADC_Stop(&js->hadc_js);*/

  uint16_t adc_r[2];
  int status = HAL_ADC_Start(js->hadc_js);
  if (status != HAL_OK) {
    Error_Handler_js();
  }
  for( int i=0; i < sizeof(js->adcChannels)/sizeof(js->adcChannels[0]); ++i) {
    status = HAL_ADC_PollForConversion(js->hadc_js, HAL_MAX_DELAY);
    if (status != HAL_OK) {
      Error_Handler_js();
    }
    adc_r[i] = HAL_ADC_GetValue(js->hadc_js);
  }
  status = HAL_ADC_Stop(js->hadc_js);
  if (status != HAL_OK) {
    Error_Handler_js();
  }
  js->adc_X = js->adcChannels[0] > js->adcChannels[1]? adc_r[0]:adc_r[1];
  js->adc_y = js->adcChannels[0] < js->adcChannels[1]? adc_r[0]:adc_r[1];
  return -1;
}

int joystick_getSWvalue(struct joystick *js)
{
  js->sw = HAL_GPIO_ReadPin( js->sw_port, js->swPin );
  return -1;
}

int joystick_getValuesByTimer( struct joystick *js , void (*f)(struct joystick *js ) )
{
  timeCounter_verifyTimer( &js->tm );
  if ( js->tm.timerReached )
  {
    joystick_getADCvalues(js);
    joystick_getSWvalue(js);
    joystick_getSWvalue(js);
    //f(js);
    (*f)(js);

    timeCounter_resetTimer(&js->tm);
  }
  return -1;
}

int joystick_init( struct joystick *js)
{
  joystick_getADCvalues(js);
  joystick_getSWvalue(js);
  timeCounter_init(&js->tm);
  return -1;
}