//
//  RAMainMenuScene.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#ifndef RAMainMenuScene_hpp
#define RAMainMenuScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"

class RAMainMenuScene : public cocos2d::Scene
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    cocos2d::LayerColor *varBackLayer;
    cocos2d::Size varScreenSize;
    cocos2d::ui::Button *varSinglePlayerButton;
    cocos2d::ui::Button *varMultiPlayerButton;
    cocos2d::ui::Button *varOnlineButton;

    // implement the "static create()" method manually
    CREATE_FUNC(RAMainMenuScene);
    void startSinglePlayerCallback(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
};

#endif /* RAMainMenuScene_hpp */
