#ifndef Sprite_h
#define Sprite_h

#include "Arduino.h"

class Sprite {
  public:
    Sprite(byte* rows);

  private:
    byte* rows;
};

#endif
