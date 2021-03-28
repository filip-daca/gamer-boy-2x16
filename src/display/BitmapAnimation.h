#ifndef BitmapAnimation_h
#define BitmapAnimation_h

#include "Arduino.h"

#define BITMAP_MAX_X 20
#define BITMAP_MAX_Y 16

#define DEBUG 0


class BitmapAnimation {
  public:
    BitmapAnimation(word** frames, word framesCount, byte screenPosition);
    byte** getSpritesFromFrame();
    void nextFrame();
    byte getScreenPosition();
    
  private:
    word** frames;
    word framesCount;
    word currentFrame;
    byte screenPosition;
};

#endif
