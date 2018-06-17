//
//  RACreature.hpp
//  Radius
//
//  Created by Thiago De Angelis on 17/06/2018.
//

#ifndef RACreature_hpp
#define RACreature_hpp

#include <stdio.h>

enum CreatureID
{
    Rat,
    Cave_rat
};

class RACreature
{
public:
    RACreature(CreatureID id, int maxHealthPoints, int atkDamage);
    ~RACreature();
    
    CreatureID id;
    int healthPoints;
    int maxHealthPoints;
    int atkDamage;
};

#endif /* RACreature_hpp */
