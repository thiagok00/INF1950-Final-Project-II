//
//  RATargetItem.cpp
//  Radius
//
//  Created by Thiago De Angelis on 06/07/2018.
//

#include "RATargetItem.hpp"


RATargetItem::RATargetItem(int charges) : RAItem(idItemTarget, charges)
{
    
}

RAOffensiveTargetItem::RAOffensiveTargetItem(int charges, int damage) : RATargetItem(charges)
{
    this->damage = damage;
}

void RAOffensiveTargetItem::doAction(RAEntity *target)
{
    if(charges > 0)
    {
        target->inflictDamage(damage);
        charges--;
    }
}
