#ifndef IMenuLine_H_
#define IMenuLine_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <U8g2lib.h>
#include "ScreenManagerConstants.h"

#define MAX_MENU_LABEL_LENGTH 15

class IMenuLine
{
protected:
    const uint8_t *mFont;
    char *mLabel;

    void (*onClickHandler)(void);

public:
    virtual void render(U8G2 *u8g2, u8g2_uint_t y, bool highlight = false) = 0;
    virtual void propagateAction(Action action);
    void drawButton(U8G2 *u8g2, u8g2_uint_t y, bool highlight = false);
    void setOnClickHandler(void (*handler)(void));
    void click();
};

#endif // IMenuLine_H_
