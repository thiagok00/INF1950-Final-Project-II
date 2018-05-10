//
//  TileModel.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 25/04/2018.
//

#include "TileModel.hpp"

TileModel::TileModel(int row, int col, bool walkable)
{
    this->row = row;
    this->col = col;
    this->walkable = walkable;
}

TileModel::~TileModel()
{
    
}

int TileModel::getRow()
{
    return this->row;
}

int TileModel::getCol()
{
    return this->col;
}

bool TileModel::isWakable()
{
    return this->walkable;
}
