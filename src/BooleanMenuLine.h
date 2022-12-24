#ifndef BooleanMenuLine_H_
#define BooleanMenuLine_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "ScreenManagerConstants.h"
#include "IMenuLine.h"

class U8G2;

class BooleanMenuLine : public IMenuLine
{
private:
    bool *mBooleanValue;

    void (*onStateChangedHandler)(void);

public:
    BooleanMenuLine(char *label, const uint8_t *font, bool *booleanValue);
    BooleanMenuLine(const __FlashStringHelper *label, const uint8_t *font, bool *booleanValue);
    virtual ~BooleanMenuLine();
    virtual void render(U8G2 *u8g2, uint8_t y, bool highlight);
    virtual void propagateAction(Action action);
    void setOnStateChangedHandler(void (*handler)(void));
};

#endif // BooleanMenuLine_H_