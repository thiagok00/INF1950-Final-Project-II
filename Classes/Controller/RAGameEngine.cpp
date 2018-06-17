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
        // ....
    }
    else
    {
        eng->player1 = new RAPlayer();
    }
    
    eng->gameMap = RALevelGenerator::generateLevel(0);
    
    if(eng->player1 != NULL)
    {
        eng->player1->tile = eng->gameMap->player1RespawnTile;
    }
    if(eng->player2 != NULL)
    {
        eng->player2->tile = eng->gameMap->player2RespawnTile;
    }
    //eng->player1->tile = eng->gameMap[]
    
    return eng;
}

bool RAGameEngine::movePlayer(RAPlayer *player, RADirection direction)
{
    if(player == NULL)
        return false;
    
    RATile *destTile = NULL;
    
    switch(direction)
    {
        case RIGHT:
            if (player->tile->getRow() == MAP_MAX_ROW) //on top
                return false;
            else
                destTile = gameMap->getTile(player->tile->getRow()+1, player->tile->getCol());
            break;
        case LEFT:
            if (player->tile->getRow() == 0) //on bottom
                return false;
            else
                destTile = gameMap->getTile(player->tile->getRow()-1, player->tile->getCol());
            break;
        case DOWN:
            if (player->tile->getCol() == 0)
                return false;
            else
                destTile = gameMap->getTile(player->tile->getRow(), player->tile->getCol()-1);
            break;
        case UP:
            if (player->tile->getCol() == MAP_MAX_COL)
                return false;
            else
                destTile = gameMap->getTile(player->tile->getRow(), player->tile->getCol()+1);
            break;
    }
    
    player->tile = destTile;
    return true;
}
