#ifndef NumericalEditScreen_H_
#define NumericalEditScreen_H_

#include "ScreenManagerConstants.h"
#include "IScreen.h"

class U8G2;

class NumericalEditScreen : public IScreen
{
private:
    const uint8_t *mFont;
    float *mValue, mTempValue;
    uint8_t mIntegerDigits, mFractionalDigits;
    uint8_t mActiveIndex;
    char *mValueStr;

public:
    NumericalEditScreen(char *title, const uint8_t *font, float *value, uint8_t integerDigits = 3, uint8_t fractionalDigits = 2);
    ~NumericalEditScreen();
    virtual void render(U8G2 *u8g2);
    virtual void propagateAction(Action action);
    void setValue(float *value);
};

#endif // NumericalEditScreen_H_
