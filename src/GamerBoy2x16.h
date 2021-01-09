#ifndef GamerBoy2x16_h
#define GamerBoy2x16_h

#include "Arduino.h"

#include "controller/Controller.h"


class GamerBoy2x16 {
  public:
    GamerBoy2x16(void);
    void initialize(void);
	void update(void);
	
	Controller controller;
};

#endif
