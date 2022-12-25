#ifndef IScreen_H_
#define IScreen_H_

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <U8g2lib.h>
#include "ScreenManagerConstants.h"

#define MAX_SCREEN_TITLE_LENGTH 15

class IScreen
{
protected:
    char *mTitle;
    uint16_t mTextHeight;
    ScreenType mScreenType;

    void (*mPreRender)();
    void (*mPostRender)();
    void (*mActionHandler)(Action action);

public:
    virtual void render(U8G2 *u8g2) = 0;
    virtual void propagateAction(Action action);
    void drawCenteredText(U8G2 *u8g2, char *text, u8g2_uint_t y);
    void drawTitle(U8G2 *u8g2);
    void setPreRender(void (*preRenderFunc)(void));
    void setPostRender(void (*postRenderFunc)(void));
    void preRender();
    void postRender();
    void setActionHandler(void (*actionHandler)(Action action));
    void propagateActionExternally(Action action);
    ScreenType getType();
};

#endif // IScreen_H_
