#include <U8g2lib.h>
#include "IMenuLine.h"

void IMenuLine::drawButton(U8G2 *u8g2, uint8_t y, bool highlight)
{
    u8g2->drawButtonUTF8(5, y, highlight ? U8G2_BTN_INV : U8G2_BTN_BW0, u8g2->getDisplayWidth(), 5, 1, mLabel);
}

void IMenuLine::setOnClickHandler(void (*handler)(void))
{
    onClickHandler = handler;
}

void IMenuLine::click()
{
    if (onClickHandler)
    {
        onClickHandler();
    }
}
