//
//  RATile.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 25/04/2018.
//

#include "RATile.hpp"

RATile::RATile(int row, int col, bool walkable)
{
    this->row = row;
    this->col = col;
    this->walkable = walkable;
    this->creature = nullptr;
    this->droppedItem = nullptr;
}

RATile::~RATile()
{
    
}

int RATile::getRow()
{
    return this->row;
}

int RATile::getCol()
{
    return this->col;
}

bool RATile::isWakable()
{
    return this->walkable;
}
