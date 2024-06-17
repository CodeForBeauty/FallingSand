#include <iostream>

#include <App.h>
#include <Sprite.h>
#include <lm/lm.h>

#include "NewApp.h"


int main() 
{
    NewApp app = NewApp();

    /*ApusCore::Sprite* sp = app.CreateSprite();

    sp->Rotate(45);*/

    app.Init();

    return 0;
}