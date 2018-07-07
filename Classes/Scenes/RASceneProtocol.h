//
//  RASceneProtocol.h
//  Radius
//
//  Created by Thiago De Angelis on 21/05/2018.
//

#ifndef RASceneProtocol_h
#define RASceneProtocol_h
#include "RAMap.hpp"
#include "RAPlayer.hpp"
#include "RACreature.hpp"

class RASceneProtocol
{
public:
    virtual void renderMap (RAMap* map) {}
    virtual void loadPlayer (RAPlayer *player) {}
    virtual void playerMoved (RAPlayer* player, RATile * tile) {}
    virtual void playerMovedAndCaughtItem (RAPlayer* player, RATile * tile, RAItem *item) {}
    virtual void playerAttackedCreature (RAPlayer* player, RACreature *creature, int damage, bool died) {}
    virtual void creatureMoved(RACreature *creature, int row, int col) {}
    virtual void creatureAttackedPlayer(RACreature *creature, RAPlayer * player, int damage) {}

};

#endif /* RASceneProtocol_h */
