//
//  RAPlayer.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#ifndef RAPlayer_hpp
#define RAPlayer_hpp

#include <stdio.h>
#include "RATile.hpp"

enum RADirection {
    UP, DOWN, LEFT, RIGHT
};

class RAPlayer
{
public:
    RAPlayer();
    ~RAPlayer();
    
    
    int healthPoints;
    int atkDamage;
    int actionPoints;
    
    RATile *tile;
};

#endif /* RAPlayer_hpp */
