#ifndef __RAGameScene_SCENE_H__
#define __RAGameScene_SCENE_H__

#include "cocos2d.h"

#include "RAUtil.h"
#include "RASceneProtocol.h"

//Game Controllers
#include "RAGameController.hpp"
#include "RASinglePlayerGameController.hpp"


class RAGameScene : public cocos2d::Scene, public RASceneProtocol
{
public:
    static cocos2d::Scene* createScene(int gameMode);

    virtual bool init(int gameMode);
    
    RAGameController *gameController;
    
    /* RASceneProtocol Methods */
    void renderMap (RAMap* map);
    
    cocos2d::LayerColor *varBackLayer;
    cocos2d::Size varScreenSize;
    // implement the "static create()" method manually
    //CREATE_FUNC(RAGameScene);
};

#endif // __RAGameScene_SCENE_H__
