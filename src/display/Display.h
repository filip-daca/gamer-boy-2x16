#ifndef Display_h
#define Display_h

#include "Arduino.h"
#include "LiquidCrystal.h"
#include "BitmapAnimation.h"

#define MAX_SPRITES   8
#define SPRITE_LEN    8
#define COLS          16
#define ROWS          2

#define DEBUG 0


static const byte PIN_RS = 2;
static const byte PIN_EN = 3;
static const byte PIN_D4 = 4;
static const byte PIN_D5 = 5;
static const byte PIN_D6 = 6;
static const byte PIN_D7 = 7;

class Display {
  public:
    Display(void);
    
    void initialize();
    void update();
    void clear();
    void draw(byte sprite[], byte x, byte y);
    void flush();
    void setCursor(byte col, byte row);
    void write(const char* message);
    void drawCurrentFrame(BitmapAnimation& bitmapAnimation);
    void drawBitmap(word bitmap[], byte col);
    
  private:
    LiquidCrystal lcd;
    byte screen[ROWS][COLS][SPRITE_LEN];
    byte customSprites[MAX_SPRITES][SPRITE_LEN];
    bool spriteUsed[MAX_SPRITES];
    bool fieldActive[ROWS][COLS];
    
    byte findOrCreateSprite(byte sprite[]);
    byte getUsedSpriteCount();
};

#endif
