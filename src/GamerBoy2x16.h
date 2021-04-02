#ifndef GamerBoy2x16_h
#define GamerBoy2x16_h

#include "Arduino.h"

#include "controller/Controller.h"
#include "display/Display.h"
#include "sound/Sound.h"

#define DEBUG 0

class GamerBoy2x16 {
  public:
    GamerBoy2x16(void);
    void initialize(void);
    void update(void);
  
    Controller controller;
    Display display;
    Sound sound;
};

#endif
