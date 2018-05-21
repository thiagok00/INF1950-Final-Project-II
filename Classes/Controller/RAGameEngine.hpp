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

protected:
    RAPlayer* player1;
    RAPlayer* player2;
    
    int gameMode;
    int playerTurn;
    
};

#endif /* RAGameEngine_hpp */
