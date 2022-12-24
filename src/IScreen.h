#ifndef IScreen_H_
#define IScreen_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "ScreenManagerConstants.h"

#define MAX_SCREEN_TITLE_LENGTH 15

class U8G2;

class IScreen
{
protected:
    char *mTitle;
    uint16_t mTextHeight;

public:
    virtual void render(U8G2 *u8g2) = 0;
    virtual void propagateAction(Action action);
    void drawCenteredText(U8G2 *u8g2, char *text, uint16_t y);
    void drawTitle(U8G2 *u8g2);
};

#endif // IScreen_H_