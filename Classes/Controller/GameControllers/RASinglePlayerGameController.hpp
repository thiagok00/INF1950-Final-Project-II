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
    void doPlayerAction(int playerID, RADirection direction);
    void doPlayerUseItem(int playerID, int slot);
    void playerPassTurn(int playerID);


    
    //virtual void renderMap (RAMap* map) {}
    //virtual void loadPlayer (RAPlayer *player) {}
    void playerMoved (int playerID, int row, int col);
    void playerMovedAndCaughtItem (int playerID, int row, int col,int atSlot, ItemID itemType, int charges);
    void playerAttackedCreature (int playerID, int creatureID, int damage, bool died, int playerExperience);
    void creatureMoved(int creatureID, int row, int col);
    void creatureAttackedPlayer(int creatureID, int playerID, int damage);

protected:
    
};

#endif /* RASinglePlayerController_hpp */
