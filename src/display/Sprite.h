#ifndef Sprite_h
#define Sprite_h

#include "Arduino.h"

class Sprite {
  public:
    Sprite(byte* rows);
    byte* rows;
};

// ----------------------------------------------------------------------------
// Constructor

Sprite::Sprite(byte* rows) {
  this->rows = rows;
};


#endif
