#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <U8g2lib.h>
#include "NumericalEditScreen.h"

NumericalEditScreen::NumericalEditScreen(char *title, const uint8_t *font, float *value, uint8_t integerDigits, uint8_t fractionalDigits)
    : mFont(font),
      mIntegerDigits(integerDigits),
      mFractionalDigits(fractionalDigits),
      mActiveIndex(0)
{
    mScreenType = NUMERICAL_EDIT_SCREEN;
    mTitle = title;
    setValue(value);
}

NumericalEditScreen::~NumericalEditScreen()
{
    delete[] mTitle;
    delete mValue;
}

void NumericalEditScreen::render(U8G2 *u8g2)
{
    preRender();
    drawTitle(u8g2);

    u8g2_uint_t buffStrWidth = u8g2->getStrWidth(mValueStr) * 2;
    u8g2_uint_t buffStrStartX = (u8g2->getDisplayWidth() - buffStrWidth) / 2;
    u8g2_uint_t buffStrStartY = (u8g2->getDisplayHeight() / 2) - 3;

    char tempStr[strlen(mValueStr) + 1];
    strcpy(tempStr, mValueStr); // strncpy is buggy.
    tempStr[mActiveIndex] = '\0';
    u8g2_uint_t cursorX = buffStrStartX + (u8g2->getStrWidth(tempStr) * 2) + 2;

    u8g2->drawStrX2(buffStrStartX, buffStrStartY, mValueStr);
    u8g2->setFont(u8g2_font_unifont_t_75);
    u8g2->drawGlyph(cursorX, 15, 0x25b5); // Arrow up
    u8g2->drawGlyph(cursorX, 40, 0x25be); // Arrow down
    // u8g2->drawGlyph(buffStrStartX, 15, 0x25b5); // Arrow up
    // u8g2->drawGlyph(buffStrStartX, 40, 0x25be); // Arrow down
    u8g2->drawGlyph(0, buffStrStartY, 0x25c0);                                                      // Arrow left
    u8g2->drawGlyph(u8g2->getDisplayWidth() - 10, buffStrStartY, 0x25b6);                           // Arrow right
    u8g2->setFont(mFont);

    postRender();
}

void NumericalEditScreen::propagateAction(Action action)
{
    if (action == ACTION_ENTER)
    {
        *mValue = mTempValue;
    }
    else if (action == ACTION_ARROW_UP)
    {
        // Increase value here
        if (mActiveIndex == 0)
        {
            // +/-
            mTempValue *= -1;
            mValueStr[0] = mTempValue > 0 ? '+' : '-';
        }
        else if(mValueStr[mActiveIndex] != '.')
        {
            if(++mValueStr[mActiveIndex] > '9')
            {
                mValueStr[mActiveIndex] = '0';
            }

            mTempValue = atof(mValueStr);
        }
    }
    else if (action == ACTION_ARROW_DOWN)
    {
        // Decrease value here
        if (mActiveIndex == 0)
        {
            // +/-
            mTempValue *= -1;
            mValueStr[0] = mTempValue > 0 ? '+' : '-';
        }
        else if(mValueStr[mActiveIndex] != '.')
        {
            if(--mValueStr[mActiveIndex] < '0')
            {
                mValueStr[mActiveIndex] = '9';
            }
            
            mTempValue = atof(mValueStr);
        }
    }
    else if (action == ACTION_ARROW_LEFT)
    {
        // Highlight previous digit
        if (mActiveIndex > 0 && mValueStr[--mActiveIndex] == '.')
        {
            --mActiveIndex;
        }
    }
    else if (action == ACTION_ARROW_RIGHT)
    {
        // Highlight next digit
        if (mActiveIndex < strlen(mValueStr) - 1 && mValueStr[++mActiveIndex] == '.')
        {
            ++mActiveIndex;
        }
    }

    propagateActionExternally(action);
}

void NumericalEditScreen::setValue(float *value)
{
    mValue = value;
    mTempValue = *value;
    int temp = mTempValue * pow(10, mFractionalDigits);
    mTempValue = (temp % (int)pow(10, mIntegerDigits + mFractionalDigits)) / pow(10, mFractionalDigits);

    // Convert number to string
    delete mValueStr;
    mValueStr = new char[mIntegerDigits + mFractionalDigits + 3]; // Integer + fractional + (+/-) + decimal point + \0

    // Parse float to string. Need to negate the number to make space for +/- symbol.
    dtostrf(mTempValue > 0 ? mTempValue * -1 : mTempValue, mIntegerDigits + mFractionalDigits + 2, mFractionalDigits, mValueStr);
    mValueStr[0] = mTempValue > 0 ? '+' : '-'; // Change back the symbol to positive if needed.
}
