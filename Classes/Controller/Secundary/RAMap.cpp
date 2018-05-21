//
//  RAMap.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 25/04/2018.
//

#include "RAMap.hpp"

RAMap::RAMap()
{

}

RAMap::~RAMap()
{
    
}

RATile* RAMap::getTile(int row, int col)
{
    return this->map[row + col*MAP_MAX_ROW];
}

void RAMap::setTile(int row, int col, RATile *t)
{
    this->map[row + col*MAP_MAX_ROW] = t;
}
