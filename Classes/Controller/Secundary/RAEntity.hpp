//
//  RAEntity.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 04/07/2018.
//

#ifndef RAEntity_hpp
#define RAEntity_hpp

#include <stdio.h>

class RAEntity
{
public:
    RAEntity(int maxHealth, int atkDamage, int maxSpeed, int maxActionPoints);
    
    
    int actionPoints;
    int maxActionPoints;
    int maxSpeed;
    int speed;
    
    int healthPoints;
    int maxHealthPoints;
    int atkDamage;
    int armor;
    
    bool isDead();
    void resetTurn();
    
    int row;
    int col;
    
    //returns real damage took (damage - armor)
    int inflictDamage(int damage);
    
    
protected:
    bool dead;

};

#endif /* RAEntity_hpp */
