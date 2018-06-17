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

class RASinglePlayerGameController: public RAGameController
{
public:
    
    RASinglePlayerGameController(RASceneProtocol *gs);
    ~RASinglePlayerGameController();
    void startGame();
    void playerAction(RADirection direction);

protected:
    
};

#endif /* RASinglePlayerController_hpp */
