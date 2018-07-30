//
//  RAPath.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 28/07/2018.
//

#ifndef RAPath_hpp
#define RAPath_hpp

#include <stdio.h>
#include "RATile.hpp"
class RAPath
{
public:
    RAPath * rootTile;
    RATile * current;
    int cost;
    RAPath(int cost, RAPath* root, RATile* current);
};

#endif /* RAPath_hpp */
