//
//  RAGameEngine.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#ifndef RAGameEngine_hpp
#define RAGameEngine_hpp

#include <stdio.h>
#include "RAUtil.h"
#include "RAPlayer.hpp"
#include "RAMap.hpp"
#include "RASceneProtocol.h"

class RAGameEngine
{
public:
    RAGameEngine(int gameMode, RASceneProtocol *gameListener);
    ~RAGameEngine();
    
    static RAGameEngine* createGame(int gameMode, RASceneProtocol *gameListener);
    RAMap *gameMap;

    RAPlayer* player1;
    RAPlayer* player2;
    RASceneProtocol *gameListener;
    
    bool doPlayerAction(RAPlayer *player, RADirection direction);
    
protected:

    int gameMode;
    int turnOrder;
    
    void switchTurn();
    
};

#endif /* RAGameEngine_hpp */
