#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "moduleInit.h"
#include "Bar.h"

#define PLAYER_DIR_DOWN false
#define PLAYER_DIR_UP true

struct player
{
  struct bar b;
  uint16_t upLimit;
  uint16_t downLimit;
  bool riseDirection;
};

int player_init( struct player *pl);
int player_animation( struct player *pl );
int player_move( struct player *pl );

#endif