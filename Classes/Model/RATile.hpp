//
//  RATile.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 25/04/2018.
//

#ifndef RATile_hpp
#define RATile_hpp

#include <stdio.h>
#include "RACreature.hpp"
#include "RAItem.hpp"

enum TileType
{
    Normal,
    Stairs,
    Fire,
    Poison,
    Rock
};

class RATile
{
public:
    
    RATile(TileType type, int row,int col, bool walkable);
    ~RATile();
    
    int getRow();
    int getCol();
    bool isWakable();
    const char  * getDescription();
    RAEntity  *entity;
    RAItem      *droppedItem;
    
    int getType();
    
    void setFire();
    void setPoison();
    
protected:
    int row;
    int col;
    bool walkable;
    int type;
};

#endif /* RATile_hpp */
