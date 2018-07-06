//
//  RACreature.hpp
//  Radius
//
//  Created by Thiago De Angelis on 17/06/2018.
//

#ifndef RACreature_hpp
#define RACreature_hpp

#include <stdio.h>
#include "RAEntity.hpp"

enum CreatureID
{
    Rat,
    Cave_rat
};

class RACreature: public RAEntity
{
public:
    RACreature(CreatureID id, int maxHealthPoints, int atkDamage, int experience, int armor);
    ~RACreature();
    
    CreatureID id;
    int experience;
    
    void resetTurn();

};

#endif /* RACreature_hpp */
