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
    
    bool doPlayerAction(int playerID, RADirection direction);
    bool doPlayerUseItem(int playerID, int slot);
    bool doPlayerPassTurn(int playerID);
protected:
    
    int gameMode;
    int turnOrder;
    
    void switchTurn();
    void checkNewTurnConditions(RAEntity* entity);
    
    RAPlayer* auxGetPlayerById(int playerID);
    
};

#endif /* RAGameEngine_hpp */
