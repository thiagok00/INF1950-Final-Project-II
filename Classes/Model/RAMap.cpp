//
//  RAMap.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 25/04/2018.
//

#include "RAMap.hpp"

RAMap::RAMap()
{

    for (int i = 0; i < MAP_MAX_COL * MAP_MAX_ROW; i++)
    {
        map.push_back(nullptr);
    }
    player1RespawnTile = nullptr;
    player2RespawnTile = nullptr;
}

RAMap::~RAMap()
{
    
}

RATile* RAMap::getTile(int row, int col)
{
    return this->map[col + row*MAP_MAX_COL];
}

void RAMap::setTile(int row, int col, RATile *t)
{
    this->map[col + row*MAP_MAX_COL] = t;
}

bool RAMap::addEntityToTile(RAEntity* entity, int row, int col)
{
    return addEntityToTile(entity, getTile(row, col));
}


bool RAMap::addEntityToTile(RAEntity* entity, RATile* tile)
{
    if(tile->entity == nullptr)
    {
        entity->row = tile->getRow();
        entity->col = tile->getCol();
        tile->entity = entity;
        if (RACreature * cr = dynamic_cast<RACreature*>(entity))
            creatures.push_back(cr);
        return true;
    }
    else
    {
        return false;
    }
}

bool RAMap::moveEntityToTile(RAEntity* entity, RATile* tile)
{
    RATile *oldTile = getTile(entity->row,entity->col);
    
    if(tile->entity != nullptr)
        return false; //tile occupied
    
    if (oldTile->entity == entity)
    {
        oldTile->entity = nullptr;
    }
    tile->entity = entity;
    entity->row = tile->getRow();
    entity->col = tile->getCol();
    return true;
}


bool RAMap::moveEntityToTile(RAEntity* entity, int row, int col)
{
    return moveEntityToTile(entity, getTile(row, col));
}

bool RAMap::removeEntityFromTile(RAEntity* entity, RATile* tile)
{
    if(tile->entity == entity)
    {
        tile->entity = nullptr;
        entity->row = -1;
        entity->col = -1;
        
        if(RACreature *creature = dynamic_cast<RACreature*>(entity))
        {
            //erase–remove idiom
            creatures.erase(std::remove(creatures.begin(), creatures.end(), creature), creatures.end());
        }
        
        return true;
    }
    return false;
}

bool RAMap::removeEntityFromTile(RAEntity* entity, int row, int col)
{
    return removeEntityFromTile(entity, getTile(row,col));
}



bool RAMap::addItemToTile(RAItem* item, int row, int col)
{
    RATile* tile = this->getTile(row, col);
    if(tile->droppedItem == nullptr)
    {
        tile->droppedItem = item;
        return true;
    }
    return false;
}

RAItem* RAMap::removeItemToTile(int row, int col)
{
    RATile* tile = this->getTile(row, col);
    RAItem* item = tile->droppedItem;
    tile->droppedItem = nullptr;
    //FIXME: possible memmory leak point
    return item;
}

bool auxCheckConditionsNeighbours(RATile *tile)
{
    if(!tile->isWakable())
        return false;
    if(tile->getType() == Rock)
        return false;
    if(tile->entity != nullptr)
        if(RACreature *creature = dynamic_cast<RACreature*>(tile->entity))
            return false;
    return true;
}
std::vector<RATile*> RAMap::getNeighboursTiles(RATile* tile)
{
    //TODO: maybe use heaps here?
    std::vector<RATile*> neighboursTiles;
    
    int row = tile->getRow(); int col = tile->getCol();
    
    if(row > 0)
    {
        RATile* tile = getTile(row-1, col);
        if(auxCheckConditionsNeighbours(tile))
            neighboursTiles.push_back(tile);
    }
    if(row < MAP_MAX_ROW-1)
    {
        RATile* tile = getTile(row+1, col);
        if(auxCheckConditionsNeighbours(tile))
            neighboursTiles.push_back(tile);
    }
    if(col > 0)
    {
        RATile *tile = getTile(row, col-1);
        if(auxCheckConditionsNeighbours(tile))
            neighboursTiles.push_back(tile);
    }
    if(col < MAP_MAX_COL-1)
    {
        RATile* tile = getTile(row, col+1);
        if(auxCheckConditionsNeighbours(tile))
            neighboursTiles.push_back(tile);
    }
    return neighboursTiles;
}
