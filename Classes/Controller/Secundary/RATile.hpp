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

class RATile
{
public:
    
    RATile(int row,int col, bool walkable);
    ~RATile();
    
    int getRow();
    int getCol();
    bool isWakable();
    const char * getDescription();
    RACreature *creature;
    
protected:
    int row;
    int col;
    bool walkable;
};

#endif /* RATile_hpp */
