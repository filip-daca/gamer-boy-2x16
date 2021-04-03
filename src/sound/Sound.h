#ifndef Sound_h
#define Sound_h

#include "Arduino.h"
#include "Note.h"

#define DEBUG 0


static const byte PIN_SOUND = 8;

class Sound {
  public:
    Sound(void);

    void initialize();
    void update();

    void playTone(int note, word length);

  private:
    word timeout;
};

#endif
