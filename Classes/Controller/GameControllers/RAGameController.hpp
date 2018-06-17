//
//  RAGameController.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#ifndef RAGameController_hpp
#define RAGameController_hpp

#define kDIRECTION_UP    1
#define kDIRECTION_DOWN  2
#define kDIRECTION_LEFT  3
#define kDIRECTION_RIGHT 4


#include <stdio.h>
#include "RAGameEngine.hpp"

#include "RASceneProtocol.h"

class RAGameController
{
public:

    RAGameController(RASceneProtocol *gs);
    ~RAGameController();
    virtual void startGame() {}
    virtual void playerAction(RADirection direction) {}

protected:
    RAGameEngine *gameEngine;
    RASceneProtocol  *gameScene;
    
    
};

#endif /* RAGameController_hpp */
