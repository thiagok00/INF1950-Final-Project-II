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
    gameEngine = RAGameEngine::createGame(gameScene->gameMode, gameScene);
}

void RASinglePlayerGameController::doPlayerAction(int playerID, RADirection direction)
{
    gameEngine->doPlayerAction(playerID, direction);
}

void RASinglePlayerGameController::doPlayerUseItem(int playerID, int slot)
{
    gameEngine->doPlayerUseItem(playerID, slot);
}

void RASinglePlayerGameController::playerPassTurn(int playerID)
{
    gameEngine->doPlayerPassTurn(playerID);
}

