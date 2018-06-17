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

void RASinglePlayerGameController::playerAction(RADirection direction)
{
    if(gameEngine == nullptr)
        return;

    if (gameEngine->movePlayer(gameEngine->player1, direction))
    {
        gameScene->playerMoved(gameEngine->player1, direction);
    }
}
