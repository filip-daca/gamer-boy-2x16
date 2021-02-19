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
  
  // DEBUG
  /*
  Serial.println("All frames: " + String(framesCount));
  Serial.println("This frame: " + String(currentFrame));
  for (word x = 0; x < 20; ++x) {
    Serial.print(String(frames[currentFrame][x]));
    Serial.print(' ');
  }
  Serial.println();
  */
  
  // DEBUG
  /*
  for (byte y = 0; y < 8; ++y) {
    for (byte x = 10; x < 15; ++x) {
      if (bitmap[y][x] == 1) {
        Serial.print('#');
      } else {
        Serial.print(' ');
      }
    }
    Serial.println();
  }
  */
  
  for (byte i = 0; i < 8; ++i) {
    memset(sprites[i], 0, 8);
  }
  
  // DEBUG
  /*
  for (byte y = 0; y < 8; ++y) {
    Serial.println(sprites[2][y], BIN);
  }
  Serial.println();
  */
  
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
  
  // DEBUG
  /*
  for (byte y = 0; y < 8; ++y) {
    Serial.println(sprites[2][y], BIN);
  }
  Serial.println();
  */
  
  spritesPointer = new byte*[8];
  for (byte i = 0; i < 8; ++i) {
    spritesPointer[i] = new byte[8];
    for (byte x = 0; x < 8; ++x) {
      spritesPointer[i][x] = sprites[i][x];
    }
  }
  
  /*
  for (byte y = 0; y < 8; ++y) {
    Serial.println(spritesPointer[2][y], BIN);
  }
  Serial.println();
  */
  
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
