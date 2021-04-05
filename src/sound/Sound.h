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
    void playMelody(Note* melody, byte length, bool relativeIntervals);

  private:
    bool silent;
    LimitedStack<Note> buffer = LimitedStack<Note>(NOTE_BUFFER_SIZE);
    byte currentMelodyLength;
    Note* currentMelody;
    bool melodyRelativeIntervals;
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
  currentMelodyLength = 0;
  currentMelody = NULL;
  melodyRelativeIntervals = false;
};

void Sound::update() {
  if (buffer.isEmpty() && currentMelodyLength > 0) {
    if (melodyRelativeIntervals) {
      byte relativeNoteLength = 16 / currentMelody->length;
      buffer.push(Note(0, relativeNoteLength));
      buffer.push(Note(currentMelody->tone, relativeNoteLength));
    } else {
      buffer.push(*currentMelody);
    }

    currentMelody++;
    currentMelodyLength--;
  }

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

void Sound::playMelody(Note* melody, byte length, bool relativeIntervals) {
  currentMelody = melody;
  currentMelodyLength = length;
  melodyRelativeIntervals = relativeIntervals;
};

// ----------------------------------------------------------------------------
// Private

#endif
