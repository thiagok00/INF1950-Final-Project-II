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

class RAGameEngine
{
public:
    RAGameEngine(int gameMode);
    ~RAGameEngine();
    
    static RAGameEngine* createGame(int gameMode);
    RAMap *gameMap;

    RAPlayer* player1;
    RAPlayer* player2;
    
    bool movePlayer(RAPlayer *player, RADirection direction);
    
protected:

    
    int gameMode;
    int playerTurn;
    
};

#endif /* RAGameEngine_hpp */
