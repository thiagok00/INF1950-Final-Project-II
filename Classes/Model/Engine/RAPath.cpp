//
//  RAPath.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 28/07/2018.
//

#include "RAPath.hpp"

RAPath::RAPath(int cost, RAPath* root, RATile* current)
{
    this->cost = cost;
    this->rootTile = root;
    this->current = current;
}
