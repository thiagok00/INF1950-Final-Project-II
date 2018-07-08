//
//  RASelfUseItem.hpp
//  Radius
//
//  Created by Thiago De Angelis on 06/07/2018.
//

#ifndef RASelfUseItem_hpp
#define RASelfUseItem_hpp

#include <stdio.h>
#include "RAItem.hpp"
#include "RAPlayer.hpp"

class RASelfUseItem : public RAItem
{
public:

    RASelfUseItem(int charges);
    
    virtual bool doAction(RAPlayer *owner){return false;};

};

class RAHealItem : public RASelfUseItem
{
public:
    
    RAHealItem(int charges, int healthPointsHeal, int manaPointsHeal);
    
    bool doAction(RAPlayer *owner);
    
    //Factory Methods
    static RAHealItem* createHealthRune();
    static RAHealItem* createManaPotion();

protected:
    int healthPointsHeal;
    int manaPointsHeal;
};


#endif /* RASelfUseItem_hpp */
