#ifndef CustomScreen_H_
#define CustomScreen_H_

#include "ScreenManagerConstants.h"
#include "IScreen.h"

class U8G2;

class CustomScreen : public IScreen
{
private:
    void (*mExternalRender)(void);

public:
    CustomScreen();
    ~CustomScreen();
    virtual void render(U8G2 *u8g2);
    virtual void propagateAction(Action action);

    void setRender(void (*renderFunc)(void));
};

#endif // CustomScreen_H_
