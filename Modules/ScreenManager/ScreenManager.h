#ifndef __SCREENMANAGER_H__
#define __SCREENMANAGER_H__

#include "moduleInit.h"
#include "Screen.h"

struct screenManager {
  uint8_t actualScreen;
  uint8_t totalScreens;
  struct Screen s;
};

int screenManager_init(struct screenManager *sm);
int screenManager_updateScreen(struct screenManager *sm , struct Screen *s);

#endif