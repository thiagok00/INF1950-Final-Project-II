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

void RASinglePlayerGameController::playerAttackedCreature (RAPlayer* player, RACreature *creature, int damage, bool died)
{
    gameScene->playerAttackedCreature(player, creature, damage, died);
}

void RASinglePlayerGameController::creatureMoved(RACreature *creature, int row, int col)
{
    gameScene->creatureMoved(creature, row, col);
}

void RASinglePlayerGameController::creatureAttackedPlayer(RACreature *creature, RAPlayer * player, int damage)
{
    gameScene->creatureAttackedPlayer(creature, player, damage);
}

