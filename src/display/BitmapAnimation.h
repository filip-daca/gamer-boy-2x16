#ifndef BitmapAnimation_h
#define BitmapAnimation_h

#include "Arduino.h"

#define BITMAP_MAX_X 20
#define BITMAP_MAX_Y 16

#define DEBUG 0


class BitmapAnimation {
  public:
    BitmapAnimation(word** frames, word framesCount, byte screenPosition);
    byte** getGlyphsFromFrame();
    void nextFrame();
    byte getScreenPosition();
    
  private:
    word** frames;
    word framesCount;
    word currentFrame;
    byte screenPosition;
};

// ----------------------------------------------------------------------------
// Constructor

BitmapAnimation::BitmapAnimation(word** frames, word framesCount,
    byte screenPosition) {
  this->frames = frames;
  this->framesCount = framesCount;
  this->screenPosition = screenPosition;
  currentFrame = 0;
};

// ----------------------------------------------------------------------------
// Public

byte** BitmapAnimation::getGlyphsFromFrame() {
  byte glyphs[8][8];
  byte bitmap[BITMAP_MAX_Y][BITMAP_MAX_X];
  byte** glyphsPointer;
  
  word* frame = frames[currentFrame];
  for (byte x = 0; x < BITMAP_MAX_X; ++x) {
    for (byte y = 0; y < BITMAP_MAX_Y; ++y) {
      bitmap[y][x] = (frame[x] >> y) & 1;
    }
  }
  
  for (byte i = 0; i < 8; ++i) {
    memset(glyphs[i], 0, 8);
  }
  
  for (byte y = 0; y < 8; ++y) {
    byte line = 0;
    for (byte x = 0; x < BITMAP_MAX_X; ++x) {
      byte i = x / 5;
      glyphs[i][y] = glyphs[i][y] | (bitmap[y][x] << (4 - (x % 5)));
    }
  }
  
  for (byte y = 8; y < BITMAP_MAX_Y; ++y) {
    byte line = 0;
    for (byte x = 0; x < BITMAP_MAX_X; ++x) {
      byte i = x / 5;
      glyphs[i + 4][y - 8] = glyphs[i + 4][y - 8] | (bitmap[y][x] << (4 - (x % 5)));
    }
  }
  
  glyphsPointer = new byte*[8];
  for (byte i = 0; i < 8; ++i) {
    glyphsPointer[i] = new byte[8];
    for (byte x = 0; x < 8; ++x) {
      glyphsPointer[i][x] = glyphs[i][x];
    }
  }
  
  return glyphsPointer;
};

void BitmapAnimation::nextFrame() {
  currentFrame = (currentFrame + 1) % framesCount;
};

byte BitmapAnimation::getScreenPosition() {
  return screenPosition;
}

// ----------------------------------------------------------------------------
// Private


#endif
