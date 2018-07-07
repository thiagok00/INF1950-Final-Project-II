//
//  RACreature.cpp
//  Radius
//
//  Created by Thiago De Angelis on 17/06/2018.
//

#include "RACreature.hpp"


RACreature::RACreature(CreatureID id, int maxHealthPoints, int atkDamage, int experience, int armor) : RAEntity(maxHealthPoints, atkDamage, 1, 1, armor)
{
    this->id = id;
    this->experience = experience;
}

RACreature::~RACreature()
{
    
}

