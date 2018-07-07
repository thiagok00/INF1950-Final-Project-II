//
//  RATargetItem.hpp
//  Radius
//
//  Created by Thiago De Angelis on 06/07/2018.
//

#ifndef RATargetItem_hpp
#define RATargetItem_hpp

#include <stdio.h>
#include "RAEntity.hpp"
#include "RAItem.hpp"

class RATargetItem: public RAItem
{
public:
    RATargetItem(int charges);
    
    virtual void doAction(RAEntity *target) {};
};

class RAOffensiveTargetItem: public RATargetItem
{
public:
    
    RAOffensiveTargetItem(int charges, int damage);
    
    void doAction(RAEntity *target);
    
protected:
    int damage;
};


#endif /* RATargetItem_hpp */
