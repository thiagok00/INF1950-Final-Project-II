//
//  RAGameEngine.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#include "RAGameEngine.hpp"
#include "RALevelGenerator.hpp"

#define PLAYER1_TURN    1
#define PLAYER2_TURN    2
#define CREATURE_TURN   3


RAGameEngine::RAGameEngine(int gameMode, RASceneProtocol *gameListener)
{
    player1 = nullptr;
    player2 = nullptr;
    this->gameListener = gameListener;
    gameMode = gameMode;
    turnOrder = 0;
}

RAGameEngine* RAGameEngine::createGame(int gameMode, RASceneProtocol *gameListener)
{
    RAGameEngine* eng = new RAGameEngine(gameMode, gameListener);
    
    if(gameMode == kGAMEMODE_SINGLEPLAYER)
    {
        eng->player1 = new RAPlayer();
        eng->player1->playerID = PLAYER1_TURN;
        // ....
    }
    else
    {
        eng->player1 = new RAPlayer();
    }
    
    eng->gameMap = RALevelGenerator::generateLevel(0);
    
    if(eng->player1 != nullptr)
    {
        eng->player1->tile = eng->gameMap->player1RespawnTile;
    }
    if(eng->player2 != nullptr)
    {
        eng->player2->tile = eng->gameMap->player2RespawnTile;
    }
    //eng->player1->tile = eng->gameMap[]
    
    eng->turnOrder = PLAYER1_TURN;
    eng->player1->resetTurn();
    
    return eng;
}

bool RAGameEngine::doPlayerAction(RAPlayer *player, RADirection direction)
{
    if(player == nullptr)
        return false;
    
    //Not player turn
    if(turnOrder != player->playerID)
        return false;
    
    RATile *destTile = nullptr;
    switch(direction)
    {
        case RIGHT:
            if (player->tile->getCol() == MAP_MAX_COL - 1)
                return false;
            else
                destTile = gameMap->getTile(player->tile->getRow(), player->tile->getCol() + 1);
            break;
        case LEFT:
            if (player->tile->getCol() == 0)
                return false;
            else
                destTile = gameMap->getTile(player->tile->getRow(), player->tile->getCol() - 1);
            break;
        case DOWN:
            if (player->tile->getRow() == 0)
                return false;
            else
                destTile = gameMap->getTile(player->tile->getRow() - 1, player->tile->getCol());
            break;
        case UP:
            if (player->tile->getRow() == MAP_MAX_ROW - 1)
                return false;
            else
                destTile = gameMap->getTile(player->tile->getRow() + 1, player->tile->getCol());
            break;
    }
    
    if(destTile->creature != nullptr && !destTile->creature->isDead())
    {
        //attack
        if(player1->actionPoints > 0)
        {
            CCLOG("ATTACK!");
            gameListener->playerAttackedCreature(player,
                                                 destTile->creature,
                                                 destTile->creature->inflictDamage(player->atkDamage),
                                                 destTile->creature->isDead()
                                                 );
            player->actionPoints--;
            return true;
        }
        else
        {
            CCLOG("FAIL ATTACK! - NO ACTION POINTS");
        }
    }
    //CCLOG("MOVING FROM: %dx%d TO %dx%d",player->tile->getRow(),player->tile->getCol(),destTile->getRow(),destTile->getCol());
    if (player->speed > 0 )
    {
        player->tile = destTile;
        if(gameListener != nullptr)
        {
            gameListener->playerMoved(player, destTile);
        }
        player->speed--;
    }
    if (player->speed == 0 || player->actionPoints == 0)
    {
        switchTurn();

    }
    return true;
    
}

void RAGameEngine::switchTurn()
{
    int nextTurn = -1;
    if(turnOrder == PLAYER1_TURN)
    {
        if(player2 != nullptr && !player2->isDead())
        {
            nextTurn = PLAYER2_TURN;
        }
        else
        {
            nextTurn = CREATURE_TURN;
        }
    }
    else if(turnOrder == PLAYER2_TURN)
    {
            nextTurn = CREATURE_TURN;
    }
    else if(turnOrder == CREATURE_TURN)
    {
        if(player1 != nullptr && !player1->isDead())
        {
            nextTurn = PLAYER1_TURN;
        }
        else if (player2 != nullptr && !player2->isDead())
        {
            nextTurn = PLAYER2_TURN;
        }
    }
    
    turnOrder = nextTurn;

    if(turnOrder == PLAYER1_TURN)
        player1->resetTurn();
    if(turnOrder == PLAYER2_TURN)
        player2->resetTurn();
    if(turnOrder == CREATURE_TURN)
    {
        //creature actions...
        for(RACreature *cr : gameMap->creatures)
        {
            //TODO: creature AI
            if (!cr->isDead())
            {
                int row, col;
                row = cr->row - 1;
                col = cr->col;
                if (row < 0) row = 1;
                
                if(player1->tile == gameMap->getTile(row, col))
                {
                    //player standing in destiny tile, so attack
                    gameListener->creatureAttackedPlayer(cr, player1, cr->atkDamage);
                }
                else
                {
                    //just move
                    gameMap->moveCreatureToTile(cr, row, col);
                    gameListener->creatureMoved(cr, row, col);
                }
                
                
                CCLOG("CRIATURA SE MOVEU PARA X:%D Y:%D",row,col);
            }
        }
        switchTurn();
    }
}
