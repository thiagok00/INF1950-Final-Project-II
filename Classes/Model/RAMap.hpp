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
#include "RAItem.hpp"
#include "RAEntity.hpp"
#include "RACreature.hpp"

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
    
    bool addEntityToTile(RAEntity* entity, int row, int col);
    bool moveEntityToTile(RAEntity* entity, int row, int col);

    bool addItemToTile(RAItem* item, int row, int col);
    RAItem* removeItemToTile(int row, int col);

    
    std::vector<RACreature*> creatures;

protected:
    std::vector<RATile*> map;

};


#endif /* RAMap_hpp */
