//
//  RAPlayer.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#ifndef RAPlayer_hpp
#define RAPlayer_hpp

#include <stdio.h>
#include "RATile.hpp"
#include "RAEntity.hpp"
#include "RAItem.hpp"

enum RADirection {
    UP, DOWN, LEFT, RIGHT
};

class RAPlayer: public RAEntity
{
public:
    RAPlayer();
    ~RAPlayer();
    
    int playerID;
    RATile *tile;
    
    int getExperiencePoints();
    bool addExperiencePoints(int experience);
    
    int manaPoints;
    int maxManaPoints;
    
    //Slots Methods
    bool addItemToSlot(RAItem* item);
    bool isSlotFull();
    
    RAItem * getItemAtSlot(int slot);
    void removeItemAtSlot(int slot);
    
protected:
    int experiencePoints;
    int experienceMultiplier;
    
    RAItem* itensSlots[6];
    int occupiedSlots;
    int maxSlots;
};

#endif /* RAPlayer_hpp */