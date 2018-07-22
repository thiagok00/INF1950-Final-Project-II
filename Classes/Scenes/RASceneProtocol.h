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
    int gameMode;
    virtual void loadMap (RAMap* map) {}
    virtual void loadPlayer (RAPlayer *player) {}
    virtual void playerMoved (int playerID, int row, int col) {}
    virtual void playerMovedAndCaughtItem (int playerID, int row, int col, int atSlot, ItemID itemType, int charges) {}
    virtual void playerAttackedCreature (int playerID, int creatureID, int damage, bool died, int score, bool leveledUp) {}
    virtual void creatureMoved(int creatureID, int row, int col) {}
    virtual void creatureAttackedPlayer(int creatureID, int playerID, int damage) {}
    virtual void playerBadStatus(int playerID, Status_ID statusID, int damage) {}
    virtual void switchRound(int playerID) {}
};

#endif /* RASceneProtocol_h */
