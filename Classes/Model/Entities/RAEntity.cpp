//
//  RAEntity.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 04/07/2018.
//

#include "RAEntity.hpp"

RAEntity::RAEntity(int maxHealth, int baseAtkDamage, int maxSpeed, int maxActionPoints, int armor)
{
    this->maxHealthPoints = maxHealth;
    this->healthPoints = maxHealth;
    this->baseAtkDamage = baseAtkDamage;
    
    this->maxActionPoints = maxActionPoints;
    this->dead = false;
    this->maxSpeed = maxSpeed;
    
    this->actionPoints = 0;
    this->speed = 0;
    
    this->armor = armor;
    
    this->burningTick = 0;
    this->poisonTick = 0;
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
    if(isDead())
        return 0;
    
    int realDamage = damage - armor;
    if(realDamage < 0) realDamage = 0;

    if(healthPoints - realDamage <= 0)
    {
        int damageTook = realDamage - (realDamage - healthPoints) ;
        dead = true;
        healthPoints = 0;
        return damageTook;
    }
    else
    {
        healthPoints = healthPoints - realDamage;
        if (realDamage == 0) realDamage = 1;
        return realDamage;
    }
}

int RAEntity::getAtkDamage()
{
    return this->baseAtkDamage;
}

bool RAEntity::isBurning()
{
    if(burningTick > 0)
        return true;
    return false;
}
bool RAEntity::isPoisoned()
{
   if(poisonTick > 0)
       return true;
    return false;
}

int RAEntity::burn()
{
    if (isBurning())
    {
        const int burnDamage = 10;
        this->healthPoints -= burnDamage;
        if( healthPoints <= 0)
        {
            //Entity died
            this->dead = true;
        }
        burningTick--;
        return burnDamage;
    }
    return 0;
}

int RAEntity::poison()
{
    if(isPoisoned())
    {
        const int poisonDamage = (poisonTick-1)/3 + 1;
        this->healthPoints -= poisonDamage;
        if( healthPoints <= 0)
        {
            //Entity died
            this->dead = true;
        }
        poisonTick--;
        return poisonDamage;
    }
    return 0;
}
