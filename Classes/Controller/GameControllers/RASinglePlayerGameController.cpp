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


//Not using anymore
void RASinglePlayerGameController::playerMoved (int playerID, int row, int col)
{
    gameScene->playerMoved(playerID, row, col);
}

void RASinglePlayerGameController::playerAttackedCreature (int playerID, int creatureID, int damage, bool died, int playerExperience)
{
    gameScene->playerAttackedCreature(playerID, creatureID, damage, died, playerExperience);
}

void RASinglePlayerGameController::creatureMoved(int creatureID, int row, int col)
{
    gameScene->creatureMoved(creatureID, row, col);
}

void RASinglePlayerGameController::creatureAttackedPlayer(int creatureID, int playerID, int damage)
{
    gameScene->creatureAttackedPlayer(creatureID, playerID, damage);
}

void RASinglePlayerGameController::playerMovedAndCaughtItem (int playerID, int row, int col, int atSlot, ItemID itemType, int charges)
{
    gameScene->playerMovedAndCaughtItem(playerID, row, col, atSlot, itemType, charges);
}
