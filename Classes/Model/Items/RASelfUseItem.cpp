//
//  RASelfUseItem.cpp
//  Radius
//
//  Created by Thiago De Angelis on 06/07/2018.
//

#include "RASelfUseItem.hpp"

RASelfUseItem::RASelfUseItem(int charges) : RAItem(idItemSelfUse, charges)
{
    
}

RAHealItem::RAHealItem(int charges,  int healthPointsHeal, int manaPointsHeal) : RASelfUseItem(charges)
{
    this->healthPointsHeal = healthPointsHeal;
    this->manaPointsHeal = manaPointsHeal;
}

bool RAHealItem::doAction(RAPlayer *owner)
{
    
    if (owner != nullptr && !owner->isDead() && charges > 0)
    {
        //prevent owner try to heal while full health
        if(owner->maxHealthPoints == owner->healthPoints)
            return false;
        
        //Heal Health
        if(owner->healthPoints + healthPointsHeal > owner->maxHealthPoints)
            owner->healthPoints = owner->maxHealthPoints;
        else
            owner->healthPoints += healthPointsHeal;
        
        //Heal Mana
        if(owner->manaPoints + manaPointsHeal > owner->maxManaPoints)
            owner->manaPoints = owner->maxManaPoints;
        else
            owner->manaPoints += manaPointsHeal;
        
        charges--;
        return true;
    }
    return false;
}

//MARK: Factory Methods

RAHealItem* RAHealItem::createHealthRune()
{
    const int charges = 1;
    const int healthPoints = 10;
    const int manaPoints = 0;
    RAHealItem *healthRune = new RAHealItem(charges, healthPoints, manaPoints);
    return healthRune;
}

RAHealItem* RAHealItem::createManaPotion()
{
    const int charges = 1;
    const int healthPoints = 0;
    const int manaPoints = 10;
    RAHealItem *healthRune = new RAHealItem(charges, healthPoints, manaPoints);
    return healthRune;
}
