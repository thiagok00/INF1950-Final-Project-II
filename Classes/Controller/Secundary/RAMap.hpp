//
//  RAMap.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 25/04/2018.
//

#ifndef RAMap_hpp
#define RAMap_hpp

#include <stdio.h>
#include "RAMap.hpp"
#include "RATile.hpp"

#define MAP_MAX_ROW 8
#define MAP_MAX_COL 8

class RAMap
{
public:
    RAMap();
    ~RAMap();
    
    RATile* getTile(int row, int col);
    void setTile(int row, int col, RATile *t);
    
    RATile *player1RespawnTile;
    RATile *player2RespawnTile;
    
protected:
    std::vector<RATile*> map;

};


#endif /* RAMap_hpp */
