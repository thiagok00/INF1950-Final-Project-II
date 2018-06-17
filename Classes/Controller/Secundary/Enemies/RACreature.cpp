//
//  RACreature.cpp
//  Radius
//
//  Created by Thiago De Angelis on 17/06/2018.
//

#include "RACreature.hpp"


RACreature::RACreature(CreatureID id, int maxHealthPoints, int atkDamage)
{
    this->id = id;
    this->maxHealthPoints = maxHealthPoints;
    this->healthPoints = maxHealthPoints;
    this->atkDamage = atkDamage;
}

RACreature::~RACreature()
{
    
}

