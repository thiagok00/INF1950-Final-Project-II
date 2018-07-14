//
//  RAEntity.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 04/07/2018.
//

#ifndef RAEntity_hpp
#define RAEntity_hpp

#include <stdio.h>

enum Status_ID
{
    BURNING,
    POISONED
};

class RAEntity
{
public:
    RAEntity(int maxHealth, int baseAtkDamage, int maxSpeed, int maxActionPoints, int armor);
    
    
    int actionPoints;
    int maxActionPoints;
    int maxSpeed;
    int speed;
    
    int healthPoints;
    int maxHealthPoints;
    
    bool isDead();
    void resetTurn();
    
    int row;
    int col;
    
    //bad status
    bool isBurning();
    bool isPoisoned();
    int burn();
    int poison();
    int burningTick;
    int poisonTick;
    
    //returns real damage took (damage - armor)
    int inflictDamage(int damage);
    int getAtkDamage();
    virtual ~RAEntity() {}

protected:
    bool dead;
    int baseAtkDamage;
    int armor;



};

#endif /* RAEntity_hpp */
