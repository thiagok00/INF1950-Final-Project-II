//
//  RASinglePlayerGameController.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#ifndef RASinglePlayerController_hpp
#define RASinglePlayerController_hpp

#include <stdio.h>

#include "RAGameController.hpp"

class RASinglePlayerGameController: public RAGameController, public RASceneProtocol
{
public:
    
    RASinglePlayerGameController(RASceneProtocol *gs);
    ~RASinglePlayerGameController();
    void startGame();
    void playerAction(RADirection direction);
    
    //virtual void renderMap (RAMap* map) {}
    //virtual void loadPlayer (RAPlayer *player) {}
    void playerMoved (RAPlayer* player, RATile * tile);
    void playerAttackedCreature (RAPlayer* player, RACreature *creature, int damage, bool died);
    void creatureMoved(RACreature *creature, int row, int col);
    void creatureAttackedPlayer(RACreature *creature, RAPlayer * player, int damage);

protected:
    
};

#endif /* RASinglePlayerController_hpp */
