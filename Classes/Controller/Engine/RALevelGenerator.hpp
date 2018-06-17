//
//  RALevelGenerator.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#ifndef RALevelGenerator_hpp
#define RALevelGenerator_hpp

#include <stdio.h>
#include "RAMap.hpp"

class RALevelGenerator
{
public:
    static RAMap* generateLevel(int difficulty);
};

#endif /* RALevelGenerator_hpp */
