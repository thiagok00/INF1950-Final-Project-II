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

class RASceneProtocol
{
public:
    virtual void renderMap (RAMap* map) {}
    virtual void loadPlayer (RAPlayer *player) {}
    virtual void playerMoved (RAPlayer* player, int direction) {}
};

#endif /* RASceneProtocol_h */
