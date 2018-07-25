//
//  RAGameEngine.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#include "RAGameEngine.hpp"
#include "RALevelGenerator.hpp"
#include "RASelfUseItem.hpp"


#define CREATURE_TURN   3


RAGameEngine::RAGameEngine(int gameMode, RASceneProtocol *gameListener)
{
    player1 = nullptr;
    player2 = nullptr;
    this->gameListener = gameListener;
    this->gameMode = gameMode;
    turnOrder = 0;
    level = 1;
}

RAGameEngine* RAGameEngine::createGame(int gameMode, RASceneProtocol *gameListener)
{
    RAGameEngine* eng = new RAGameEngine(gameMode, gameListener);
    
    eng->gameMap = RALevelGenerator::generateLevel(0);

    if(gameMode == kGAMEMODE_SINGLEPLAYER)
    {
        eng->player1 = new RAPlayer();
        eng->player1->playerID = PLAYER1_TURN;
        // ....
    }
    else if(gameMode == kGAMEMODE_OFFLINE_MULTIPLAYER)
    {
        eng->player1 = new RAPlayer();
        eng->player1->playerID = PLAYER1_TURN;
        
        eng->player2 = new RAPlayer();
        eng->player2->playerID = PLAYER2_TURN;
        
    }
    else
    {
        return nullptr;
    }
    
        
    if(eng->player1 != nullptr)
    {
        eng->gameMap->addEntityToTile(eng->player1, eng->gameMap->player1RespawnTile);
    }
    if(eng->player2 != nullptr)
    {
        eng->gameMap->addEntityToTile(eng->player2, eng->gameMap->player2RespawnTile);
    }
    //eng->player1->tile = eng->gameMap[]
    
    eng->turnOrder = PLAYER1_TURN;
    eng->player1->resetTurn();
    
    gameListener->loadMap(eng->gameMap);
    gameListener->loadPlayer(eng->player1);
    if(gameMode == kGAMEMODE_OFFLINE_MULTIPLAYER)
        gameListener->loadPlayer(eng->player2);
    
    gameListener->switchRound(PLAYER1_TURN);
    
    return eng;
}

bool RAGameEngine::doPlayerAction(int playerID, RADirection direction)
{
    RAPlayer *player = auxGetPlayerById(playerID);
    if(player == nullptr)
        return false;
    
    if (player->isDead())
        return false;
    
    //Not player turn
    if(turnOrder != player->playerID)
        return false;
    
    RATile *destTile = nullptr;
    switch(direction)
    {
        case RIGHT:
            if (player->col == MAP_MAX_COL - 1)
                return false;
            else
                destTile = gameMap->getTile(player->row, player->col + 1);
            break;
        case LEFT:
            if (player->col == 0)
                return false;
            else
                destTile = gameMap->getTile(player->row, player->col - 1);
            break;
        case DOWN:
            if (player->row == 0)
                return false;
            else
                destTile = gameMap->getTile(player->row - 1, player->col);
            break;
        case UP:
            if (player->row == MAP_MAX_ROW - 1)
                return false;
            else
                destTile = gameMap->getTile(player->row + 1, player->col);
            break;
    }
    
    if (destTile->entity == nullptr)
    {
        if (player->speed > 0 && destTile->isWakable())
        {
            gameMap->moveEntityToTile(player, destTile);
            player->speed--;
            
            if(destTile->getType() == Fire)
            {
                player->burningTick = 5;
                float damage = player->burn();
                if(player && gameListener != nullptr)
                {
                    gameListener->playerBadStatus(player->playerID, BURNING, damage);
                }
            }
            if(destTile->getType() == Poison)
            {
                player->poisonTick = 9;
                float damage = player->poison();
                if(player && gameListener != nullptr)
                {
                    gameListener->playerBadStatus(player->playerID, POISONED, damage);
                }
            }
            if(destTile->getType() == Stairs)
            {
                auxNewMap();
                return true;
            }
            if(auxPlayerCheckDeath(player))
                return false;
            
            int slot = -1;
            if( destTile->droppedItem != nullptr)
                slot = player->addItemToSlot(destTile->droppedItem);
            
            if(slot >= 0)
            {
                //player caught item
                RAItem *caughtItem = destTile->droppedItem;
                destTile->droppedItem = nullptr;
                if (gameListener != nullptr)
                {
                    gameListener->playerMovedAndCaughtItem(player->playerID, destTile->getRow(), destTile->getCol(), slot, caughtItem->getItemType(), caughtItem->getCharges());
                }
                
            }
            else if(gameListener != nullptr)
            {
                gameListener->playerMoved(player->playerID, destTile->getRow(), destTile->getCol());
            }
        }
    }
    else if (auto secondPlayer = dynamic_cast<RAPlayer*>(destTile->entity))
    {
        //trying to do action to other player tile
        return false;
    }
    else if(RACreature* creature = dynamic_cast<RACreature*>(destTile->entity))
    {
        if (!creature->isDead())
        {
            //attack
            if(player->actionPoints > 0)
            {
                CCLOG("ATTACK!");
                int damageTook = creature->inflictDamage(player->getAtkDamage());
                bool isDead = creature->isDead();
                int creatureID = creature->id;
                //add experience
                if (creature->isDead())
                {
                    const int experience = creature->experience;
                    score+= experience;
                    if(player1 != nullptr && !player1->isDead())
                    {
                        gameListener->playerWonExperience(player1->playerID, experience, player1->addExperiencePoints(experience));
                        
                    }
                    if(player2 != nullptr && !player2->isDead())
                    {
                        gameListener->playerWonExperience(player2->playerID, experience, player2->addExperiencePoints(experience));

                    }
                }
                player->actionPoints--;
                if (isDead)
                {
                    if(gameMap->removeEntityFromTile(creature, destTile))
                    {
                        delete creature;
                    }
                }
                gameListener->playerAttackedCreature(player->playerID,
                                                     creatureID,
                                                     damageTook,
                                                     isDead,
                                                     score
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
    }
    if (player->speed == 0 && player->actionPoints == 0)
    {
        switchTurn();
    }
    //CCLOG("MOVING FROM: %dx%d TO %dx%d",player->tile->getRow(),player->tile->getCol(),destTile->getRow(),destTile->getCol());
    return true;
}

bool RAGameEngine::doPlayerUseItem(int playerID, int slot)
{
    RAPlayer *player = auxGetPlayerById(playerID);
    
    if(player == nullptr)
        return false;
    
    if(turnOrder == playerID)
    {
        if(player->actionPoints > 0)
        {
            auto baseItem = player->getItemAtSlot(slot);
            if (baseItem == nullptr)
                return false;
            switch (baseItem->getItemType()) {
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
            //TODO: send right message for the client
            gameListener->loadPlayer(player);
            return true;
        }
    }
    return false;
}


bool RAGameEngine::doPlayerPassTurn(int playerID)
{
    if(turnOrder == playerID)
    {
        //auto player = auxGetPlayerById(playerID);
        switchTurn();
        return true;
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
    {
        player1->resetTurn();
        if (gameListener != nullptr)
            gameListener->switchRound(player1->playerID);
        checkNewTurnConditions(player1);
    }
    if(turnOrder == PLAYER2_TURN)
    {
        player2->resetTurn();
        if (gameListener != nullptr)
            gameListener->switchRound(player2->playerID);
        checkNewTurnConditions(player2);
    }
    if(turnOrder == CREATURE_TURN)
    {
        //creature actions...
        for(RACreature *cr : gameMap->creatures)
        {
            //TODO: creature AI
            if (!cr->isDead())
            {
                checkNewTurnConditions(cr);
                int row, col;
                row = cr->row - 1;
                col = cr->col;
                if (row < 0) row = 1;
                
                if(RAPlayer * atkPlayer = dynamic_cast<RAPlayer*>(gameMap->getTile(row, col)->entity))
                {
                    if (!atkPlayer->isDead())
                    {
                        //player standing in destiny tile, so attack
                        int damageTook = atkPlayer->inflictDamage(cr->getAtkDamage());
                        gameListener->creatureAttackedPlayer(cr->id, atkPlayer->playerID, damageTook);
                        
                        if(auxPlayerCheckDeath(atkPlayer)) return;
                        break;
                    }
                }
                //just move
                if(gameMap->moveEntityToTile(cr, row, col))
                   gameListener->creatureMoved(cr->id, row, col);
                else
                {
                    //creature tried to walk but it cant
                }
                CCLOG("CRIATURA SE MOVEU PARA X:%D Y:%D",row,col);
                
            }
        }
        switchTurn();
    } //end creature turn
}

void RAGameEngine::checkNewTurnConditions(RAEntity* entity)
{
    //TODO: extend bad status for monsters
    bool burned = entity->isBurning();
    bool poisoned = entity->isPoisoned();
    RAPlayer* player = dynamic_cast<RAPlayer*>(entity);
    if(burned)
    {
        float damage = entity->burn();
        if(player && gameListener != nullptr)
        {
            gameListener->playerBadStatus(player->playerID, BURNING, damage);
        }
    }
    if(poisoned)
    {
        float damage = entity->poison();
        if(player && gameListener != nullptr)
        {
            gameListener->playerBadStatus(player->playerID, POISONED, damage);
        }
    }
    if(player)
    {
        auxPlayerCheckDeath(player);
    }
}
bool RAGameEngine::auxCheckGameOver()
{
    if(gameMode == kGAMEMODE_SINGLEPLAYER)
    {
        if (player1->isDead())
            return true;
        return false;
    }
    else if(gameMode == kGAMEMODE_ONLINE_MULTIPLAYER || gameMode == kGAMEMODE_OFFLINE_MULTIPLAYER)
    {
        if(player1->isDead() && player2->isDead())
            return true;
        return false;
    }
    return false;
}

bool RAGameEngine::auxPlayerCheckDeath(RAPlayer *player)
{
    if(player->isDead()){
        bool isGameOver = auxCheckGameOver();
        gameListener->playerDied(player->playerID, isGameOver );
        gameMap->removeEntityFromTile(player,player->row,player->col);
        if(!auxCheckGameOver())
        {
            switchTurn();
        }
        return true;
    }
    return false;
}


RAPlayer* RAGameEngine::auxGetPlayerById(int playerID)
{
    if(player1 != nullptr && player1->playerID == playerID)
        return player1;
    if(player2 != nullptr && player2->playerID == playerID)
        return player2;
    return nullptr;
}

void RAGameEngine::auxNewMap()
{
    gameMap = RALevelGenerator::generateLevel(0);
    gameListener->loadMap(gameMap);

    if(player1 != nullptr && !player1->isDead())
    {
        gameMap->addEntityToTile(player1, gameMap->player1RespawnTile);
        gameListener->loadPlayer(player1);

    }
    if(player2 != nullptr && !player2->isDead())
    {
        gameMap->addEntityToTile(player2, gameMap->player2RespawnTile);
        gameListener->loadPlayer(player2);

    }
    turnOrder = PLAYER1_TURN;
    player1->resetTurn();
    
    gameListener->switchRound(PLAYER1_TURN);
    
}
