//
//  RAEntity.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 04/07/2018.
//

#include "RAEntity.hpp"

RAEntity::RAEntity(int maxHealth, int atkDamage, int maxSpeed, int maxActionPoints)
{
    this->maxHealthPoints = maxHealth;
    this->healthPoints = maxHealth;
    this->atkDamage = atkDamage;
    
    this->maxActionPoints = maxActionPoints;
    this->dead = false;
    this->maxSpeed = maxSpeed;
    
    this->actionPoints = 0;
    this->speed = 0;
}

bool RAEntity::isDead()
{
    return this->dead;
}

void RAEntity::resetTurn()
{
    this->speed = this->maxSpeed;
    this->actionPoints = this->maxActionPoints;
}

int RAEntity::inflictDamage(int damage)
{
    int realDamage = damage - armor;
    if(realDamage < 0) realDamage = 0;

    healthPoints = healthPoints - realDamage;
    if(healthPoints <= 0)
    {
        dead = true;
    }
    return realDamage;
}
