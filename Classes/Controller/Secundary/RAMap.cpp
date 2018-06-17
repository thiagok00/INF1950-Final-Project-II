//
//  RAMap.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 25/04/2018.
//

#include "RAMap.hpp"

RAMap::RAMap()
{

    //TODO: This is necessary?
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
