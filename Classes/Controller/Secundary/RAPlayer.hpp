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
#include "RAEntity.hpp"

enum RADirection {
    UP, DOWN, LEFT, RIGHT
};

class RAPlayer: public RAEntity
{
public:
    RAPlayer();
    ~RAPlayer();
    
    int playerID;
    
    RATile *tile;

protected:
};

#endif /* RAPlayer_hpp */
