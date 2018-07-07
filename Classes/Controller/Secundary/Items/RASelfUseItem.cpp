//
//  RASelfUseItem.cpp
//  Radius
//
//  Created by Thiago De Angelis on 06/07/2018.
//

#include "RASelfUseItem.hpp"

RAHealItem::RAHealItem(int charges, int heal) : RASelfUseItem(charges)
{
    this->heal = heal;
}

void RAHealItem::doAction(RAPlayer *owner)
{
    if (owner != nullptr && !owner->isDead())
    {
        owner->healthPoints += heal;
    }
}
