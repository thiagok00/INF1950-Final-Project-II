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
    gameEngine = RAGameEngine::createGame(kGAMEMODE_SINGLEPLAYER, this);
    gameScene->renderMap(gameEngine->gameMap);
    gameScene->loadPlayer(gameEngine->player1);
}

void RASinglePlayerGameController::playerAction(RADirection direction)
{
    if(gameEngine == nullptr)
        return;

    gameEngine->doPlayerAction(gameEngine->player1, direction);

}

void RASinglePlayerGameController::playerMoved (RAPlayer* player, RATile * tile)
{
    gameScene->playerMoved(player, tile);
}

void RASinglePlayerGameController::playerAttackedCreature (RAPlayer* player, RACreature *creature, float damage)
{
    gameScene->playerAttackedCreature(player, creature, damage);
}
