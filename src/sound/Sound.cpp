#include "Sound.h"

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
