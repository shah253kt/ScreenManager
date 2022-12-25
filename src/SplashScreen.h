#ifndef SplashScreen_H_
#define SplashScreen_H_

#include <U8g2lib.h>
#include "IScreen.h"
#include "ScreenManagerConstants.h"

class SplashScreen : public IScreen
{
private:
    bool mTransparent, mInvertedColor;
    u8g2_uint_t mX, mY, mWidth, mHeight;
    const uint8_t *mBitmap;

public:
    SplashScreen(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, const uint8_t *bitmap);
    ~SplashScreen();
    virtual void render(U8G2 *u8g2);
    virtual void propagateAction(Action action);

    void setTransparent(bool transparent);
    void setInverted(bool inverted);
};

#endif // SplashScreen_H_
