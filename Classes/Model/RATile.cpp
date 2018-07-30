//
//  RATile.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 25/04/2018.
//

#include "RATile.hpp"
#include <limits.h>

RATile::RATile(TileType type, int row, int col, bool walkable)
{
    this->type = type;
    this->row = row;
    this->col = col;
    this->walkable = walkable;
    this->entity = nullptr;
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

int RATile::getType()
{
    return this->type;
}

void RATile::setFire()
{
    this->type = Fire;
}

void RATile::setPoison()
{
    this->type = Poison;
}

int RATile::getCost()
{
    if(entity != nullptr)
    {
    if(RACreature *creature = dynamic_cast<RACreature*>(entity))
        return 1000000;
    }
    if(!isWakable())
        return 1000000;
    
    switch (type)
    {
        case Normal:
            return 5;
        case Fire:
            return 500;
            break;
        case Poison:
            return 500;
            break;
        case Stairs:
            return 10000000;
        case Rock:
            return 10000000;
            break;
    }
    return 1;
}
