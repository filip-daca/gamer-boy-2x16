#ifndef Sound_h
#define Sound_h

#include "Arduino.h"
#include "Note.h"

#define DEBUG 0

static const byte PIN_SOUND = 8;
static const byte NOTE_BUFFER_SIZE = 8;

class Sound {
  public:
    Sound();

    void initialize();
    void update();

    void playTone(word note, word length);

  private:
    bool silent;
    LimitedStack<Note> buffer = LimitedStack<Note>(NOTE_BUFFER_SIZE);
};

// ----------------------------------------------------------------------------
// Constructor

Sound::Sound() {
  
};

// ----------------------------------------------------------------------------
// Public

void Sound::initialize() {
  while (!buffer.isEmpty()) {
    buffer.pop();
  }
  silent = true;
};

void Sound::update() {
  if (buffer.isEmpty()) {
    if (!silent) {
      noTone(PIN_SOUND);
      silent = true;
    }
  } else {
    Note note = buffer.pop();

    tone(PIN_SOUND, note.tone);
    silent = false;
    note.length--;
    
    if (note.length > 0) {
      buffer.push(note);
    }
  }
};

void Sound::playTone(word note, word length) {
  buffer.push(Note(note, length));
};

// ----------------------------------------------------------------------------
// Private

#endif
