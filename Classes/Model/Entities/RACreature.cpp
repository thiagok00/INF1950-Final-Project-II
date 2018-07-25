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

RACreature * RACreature::createCreature (int difficulty)
{
    if (difficulty == 1)
    {
        const int maxHealth = 100;
        const int atkDamage = 10;
        const int experience = 50;
        const int armor = 0;
        return new RACreature(GreenGhost, maxHealth, atkDamage, experience, armor);
    }
    if(difficulty == 2)
    {
        const int maxHealth = 200;
        const int atkDamage = 20;
        const int experience = 250;
        const int armor = 5;
        return new RACreature(BlueGhost, maxHealth, atkDamage, experience, armor);
    }
    else
    {
        const int maxHealth = 300;
        const int atkDamage = 30;
        const int experience = 400;
        const int armor = 10;
        return new RACreature(RedGhost, maxHealth, atkDamage, experience, armor);
    }
}

