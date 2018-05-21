//
//  RAGameEngine.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#include "RAGameEngine.hpp"
#include "RALevelGenerator.hpp"

#define PLAYER1_TURN 1
#define PLAYER2_TURN 2


RAGameEngine::RAGameEngine(int gameMode)
{
    player1 = NULL;
    player2 = NULL;
    gameMode = gameMode;
    playerTurn = 0;
}

RAGameEngine* RAGameEngine::createGame(int gameMode)
{
    RAGameEngine* eng = new RAGameEngine(gameMode);
    
    if(gameMode == kGAMEMODE_SINGLEPLAYER)
    {
        eng->player1 = new RAPlayer();
    }
    
    eng->gameMap = RALevelGenerator::generateLevel(0);
    
    return eng;
}

