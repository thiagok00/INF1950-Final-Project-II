//
//  RAPlayer.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#include "RAPlayer.hpp"

#define PLAYER_INI_HEALTH   1
#define PLAYER_INI_DMG      1
#define PLAYER_INI_ACTPTS   1
#define PLAYER_INI_SPEED    2

RAPlayer::RAPlayer() : RAEntity(PLAYER_INI_HEALTH, PLAYER_INI_DMG, PLAYER_INI_ACTPTS, PLAYER_INI_SPEED)
{

}

RAPlayer::~RAPlayer()
{
    
}
