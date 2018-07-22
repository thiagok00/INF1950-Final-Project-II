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
    RATile* tile = this->getTile(row, col);
    if(tile->entity == nullptr)
    {
        entity->row = row;
        entity->col = col;
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

bool RAMap::moveEntityToTile(RAEntity* entity, int row, int col)
{
    //TODO: improve this
    for (RATile * t : this->map)
    {
        if (t->entity == entity)
        {
            t->entity = nullptr;
            RATile *destTile = this->getTile(row, col);
            if (destTile != nullptr)
            {
                destTile->entity = entity;
                entity->row = row;
                entity->col = col;
                return true;
            }
            return false;
        }
    }
    return false;
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
