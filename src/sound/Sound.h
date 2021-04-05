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

// ----------------------------------------------------------------------------
// Constructor

Sound::Sound(void) {
  
};

// ----------------------------------------------------------------------------
// Public

void Sound::initialize(void) {
};

void Sound::update(void) {
  if (timeout > 0) {
    timeout--;
  }
  if (timeout == 0) {
    noTone(PIN_SOUND);
  }
};

void Sound::playTone(int note, word length) {
  timeout = length;
  tone(PIN_SOUND, note);
};

// ----------------------------------------------------------------------------
// Private

#endif
