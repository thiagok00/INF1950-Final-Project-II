//
//  RAPlayer.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#include "RAPlayer.hpp"

#define PLAYER_INI_HEALTH   100
#define PLAYER_INI_DMG      1
#define PLAYER_INI_SPEED    2
#define PLAYER_INI_ACTPTS   1
#define PLAYER_INI_ARMOR    1
#define PLAYER_INI_MANA     100
#define PLAYER_INI_MAXSLOTS 6


RAPlayer::RAPlayer() : RAEntity(PLAYER_INI_HEALTH, PLAYER_INI_DMG, PLAYER_INI_SPEED, PLAYER_INI_ACTPTS, PLAYER_INI_ARMOR)
{
    this->experiencePoints = 0;
    this->experienceMultiplier = 1;
    this->maxManaPoints = PLAYER_INI_MANA;
    this->manaPoints = PLAYER_INI_MANA;
    this->maxSlots = PLAYER_INI_MAXSLOTS;
    for(int i = 0; i < PLAYER_INI_MAXSLOTS; i++)
    {
        this->itensSlots[i] = nullptr;
    }
    occupiedSlots = 0;
}

RAPlayer::~RAPlayer()
{
    
}

int RAPlayer::getExperiencePoints()
{
    return this->experiencePoints;
}

bool RAPlayer::addExperiencePoints(int experience)
{
    this->experiencePoints += experience * this->experienceMultiplier;
    return true;
}

//MARK: Slots Methods

bool RAPlayer::addItemToSlot(RAItem* item)
{
    if(isSlotFull())
        return false;
    
    for(int i = 0; i < this->maxSlots; i++)
    {
        if(itensSlots[i] == nullptr)
        {
            itensSlots[i] = item;
            occupiedSlots++;
            return true;
        }
    }
    //should not reach here
    return false;
}

bool RAPlayer::isSlotFull()
{
    if (occupiedSlots == maxSlots)
        return true;
    return false;
}

RAItem * RAPlayer::getItemAtSlot(int slot)
{
    if(slot-1 < maxSlots && slot-1 >= 0)
    {
        return itensSlots[slot-1];
    }
    return nullptr;
}

void RAPlayer::removeItemAtSlot(int slot)
{
    if(slot < maxSlots)
    {
        if(itensSlots[slot] != nullptr)
        {
            itensSlots[slot] = nullptr;
            occupiedSlots--;
        }
    }
}

