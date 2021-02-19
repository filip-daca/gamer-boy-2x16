#include "BitmapAnimation.h"

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

byte** BitmapAnimation::getSpritesFromFrame() {
  byte sprites[8][8];
  byte bitmap[16][20];
  byte** spritesPointer;
  
  word* frame = frames[currentFrame];
  for (byte x = 0; x < 20; ++x) {
    for (byte y = 0; y < 16; ++y) {
      bitmap[y][x] = (frame[x] >> y) & 1;
    }
  }
  
  for (byte i = 0; i < 8; ++i) {
    memset(sprites[i], 0, 8);
  }
  
  for (byte y = 0; y < 8; ++y) {
    byte line = 0;
    for (byte x = 0; x < 20; ++x) {
      byte i = x / 5;
      sprites[i][y] = sprites[i][y] | (bitmap[y][x] << (4 - (x % 5)));
    }
  }
  
  for (byte y = 8; y < 16; ++y) {
    byte line = 0;
    for (byte x = 0; x < 20; ++x) {
      byte i = x / 5;
      sprites[i + 4][y - 8] = sprites[i + 4][y - 8] | (bitmap[y][x] << (4 - (x % 5)));
    }
  }
  
  spritesPointer = new byte*[8];
  for (byte i = 0; i < 8; ++i) {
    spritesPointer[i] = new byte[8];
    for (byte x = 0; x < 8; ++x) {
      spritesPointer[i][x] = sprites[i][x];
    }
  }
  
  return spritesPointer;
};

void BitmapAnimation::nextFrame() {
  currentFrame = (currentFrame + 1) % framesCount;
};

byte BitmapAnimation::getScreenPosition() {
  return screenPosition;
}

// ----------------------------------------------------------------------------
// Private
