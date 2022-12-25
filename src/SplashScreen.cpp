#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "SplashScreen.h"

SplashScreen::SplashScreen(u8g2_uint_t x, u8g2_uint_t y, u8g2_uint_t w, u8g2_uint_t h, const uint8_t *bitmap)
    : mX(x),
      mY(y),
      mWidth(w),
      mHeight(h),
      mBitmap(bitmap),
      mTransparent(false),
      mInvertedColor(false)
{
    mScreenType = SPLASH_SCREEN;
}

SplashScreen::~SplashScreen()
{
    delete mBitmap;
}

void SplashScreen::render(U8G2 *u8g2)
{
    preRender();
    u8g2->setBitmapMode(mTransparent);
    u8g2->setDrawColor(mInvertedColor ? 1 : 0); // 0 for original color, 1 to invert color
    u8g2->drawXBM(mX, mY, mWidth, mHeight, mBitmap);
    postRender();
}

void SplashScreen::propagateAction(Action action)
{
    propagateActionExternally(action);
}

void SplashScreen::setTransparent(bool transparent)
{
    mTransparent = transparent;
}

void SplashScreen::setInverted(bool inverted)
{
    mInvertedColor = inverted;
}
