//
//  RAGameEngine.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#include "RAGameEngine.hpp"
#include "RALevelGenerator.hpp"
#include "RASelfUseItem.hpp"

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
    
    gameListener->loadMap(eng->gameMap);
    gameListener->loadPlayer(eng->player1);
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
            int damageTook = destTile->creature->inflictDamage(player->getAtkDamage());
            bool isDead = destTile->creature->isDead();
            
            //add experience
            if (destTile->creature->isDead())
            {
                player->addExperiencePoints(destTile->creature->experience);
            }
            player->actionPoints--;

            gameListener->playerAttackedCreature(player,
                                                 destTile->creature,
                                                 damageTook,
                                                 isDead
                                                 );
            return true;
        }
        else
        {
            //Fail to Attack - Do nothing
            CCLOG("FAIL ATTACK! - NO ACTION POINTS");
            return false;
        }
    }
    //CCLOG("MOVING FROM: %dx%d TO %dx%d",player->tile->getRow(),player->tile->getCol(),destTile->getRow(),destTile->getCol());
    if (player->speed > 0 )
    {
        player->tile = destTile;
        player->speed--;
        
        if(destTile->droppedItem != nullptr && player->addItemToSlot(destTile->droppedItem))
        {
            //player caught item
            RAItem *caughtItem = destTile->droppedItem;
            destTile->droppedItem = nullptr;
            if (gameListener != nullptr)
            {
                gameListener->playerMovedAndCaughtItem(player, destTile, caughtItem);
            }
        }
        else if(gameListener != nullptr)
        {
            gameListener->playerMoved(player, destTile);
        }
    }
    if (player->speed == 0 || player->actionPoints == 0)
    {
        switchTurn();
    }
    return true;
    
}

bool RAGameEngine::doPlayerUseItem(RAPlayer *player, int slot)
{
    if(turnOrder == PLAYER1_TURN)
    {
        if(player->actionPoints > 0)
        {
            auto baseItem = player->getItemAtSlot(slot);
            if (baseItem == nullptr)
                return false;
            switch (baseItem->getItemID()) {
                case idItemTarget:
                    
                    break;
                case idItemSelfUse:
                    if(RASelfUseItem *item = dynamic_cast<RASelfUseItem*>(baseItem))
                    {
                        if(!item->doAction(player))
                            return false;
                    }
                    break;
                case idItemAreaItem:
                    //TODO: not implemented yet
                    break;
            }
            player->actionPoints--;
            if (baseItem->getCharges() <= 0)
            {
                player->removeItemAtSlot(slot);
            }
            gameListener->loadPlayer(player);
            return true;
        }
    }
    return false;
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
                    int damageTook = player1->inflictDamage(cr->getAtkDamage());
                    gameListener->creatureAttackedPlayer(cr, player1, damageTook);
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
