#ifndef Controller_h
#define Controller_h

#include "Arduino.h"

#define MAX_READ      1024
#define CENTER        512


static const word BUTTON_A 			    = 768;
static const word BUTTON_B 			    = 512;
static const word BUTTON_AB 		    = 820;

static const byte THRESHOLD_BUTTONS = 20;
static const byte THRESHOLD_JOY     = 15;

static const byte PIN_BUTTONS 	    = A0;
static const byte PIN_AXIS_Y 		    = A1;
static const byte PIN_AXIS_X 		    = A2;

class Controller {
	public:
		Controller(void);
		
		word x;
		word y;
		bool a;
		bool b;
    word centerX;
    word centerY;
    
    bool left;
    bool right;
    bool up;
    bool down;
		
		void initialize(void);
		void update(void);
		void calibrateJoystick(void);
	
	private:
    
  
		void updateButtons(void);
		void updateJoystick(void);
};

#endif
