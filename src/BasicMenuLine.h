#ifndef BasicMenuLine_H_
#define BasicMenuLine_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <U8g2lib.h>
#include "ScreenManagerConstants.h"
#include "IMenuLine.h"

class BasicMenuLine : public IMenuLine
{
private:
public:
    BasicMenuLine(char *label, const uint8_t *font);
    BasicMenuLine(const __FlashStringHelper* label, const uint8_t *font);
    ~BasicMenuLine();
    virtual void render(U8G2 *u8g2, u8g2_uint_t y, bool highlight = false);
    virtual void propagateAction(Action action);
};

#endif // BasicMenuLine_H_
