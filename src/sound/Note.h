#ifndef Note_h
#define Note_h

#include "Arduino.h"

class Note {
  public:
    Note(word tone, word length);
	  word tone;
	  word length;
};

// ----------------------------------------------------------------------------
// Constructor

Note::Note(word tone, word length) {
  this->tone = tone;
  this->length = length;
};

#endif
