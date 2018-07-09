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
    gameEngine = RAGameEngine::createGame(kGAMEMODE_SINGLEPLAYER, gameScene);
}

void RASinglePlayerGameController::doPlayerAction(RAPlayer* player, RADirection direction)
{
    gameEngine->doPlayerAction(player, direction);
}

void RASinglePlayerGameController::doPlayerUseItem(RAPlayer *player, int slot)
{
    gameEngine->doPlayerUseItem(player, slot);
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

void RASinglePlayerGameController::playerMovedAndCaughtItem (RAPlayer* player, RATile * tile, RAItem *item)
{
    gameScene->playerMovedAndCaughtItem(player, tile, item);
}
