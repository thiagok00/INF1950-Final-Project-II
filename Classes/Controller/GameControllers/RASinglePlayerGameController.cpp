//
//  RASinglePlayerGameController.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#include "RASinglePlayerGameController.hpp"


RASinglePlayerGameController::RASinglePlayerGameController(RASceneProtocol *gs) : RAGameController (gs)
{
}


void RASinglePlayerGameController::startGame()
{
    gameEngine = RAGameEngine::createGame(kGAMEMODE_SINGLEPLAYER);
    gameScene->renderMap(gameEngine->gameMap);
    gameScene->loadPlayer(gameEngine->player1);
}

void RASinglePlayerGameController::movePlayer(int direction)
{
    if(gameEngine == NULL)
        return;
    RADirection raDir;
    
    switch (direction) {
        case kDIRECTION_UP:
            raDir = UP;
            break;
        case kDIRECTION_DOWN:
            raDir = DOWN;
            break;
        case kDIRECTION_LEFT:
            raDir = LEFT;
            break;
        case kDIRECTION_RIGHT:
            raDir = RIGHT;
            break;
        default:
            return;
    }
    if (gameEngine->movePlayer(gameEngine->player1, raDir))
    {
        gameScene->playerMoved(gameEngine->player1, direction);
    }
}
