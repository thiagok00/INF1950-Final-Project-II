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


RAPlayer::RAPlayer() : RAEntity(PLAYER_INI_HEALTH, PLAYER_INI_DMG, PLAYER_INI_SPEED, PLAYER_INI_ACTPTS, PLAYER_INI_ARMOR)
{
    this->experiencePoints = 0;
    this->experienceMultiplier = 1;
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
