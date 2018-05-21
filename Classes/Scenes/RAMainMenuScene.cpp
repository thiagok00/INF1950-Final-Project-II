//
//  RAMainMenuScene.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#include "RAMainMenuScene.hpp"
#include "RAGameScene.h"

USING_NS_CC;

Scene* RAMainMenuScene::createScene()
{
    return RAMainMenuScene::create();
}

bool RAMainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }
    
    varScreenSize = this->getContentSize();//Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    varBackLayer = LayerColor::create(Color4B::BLACK, varScreenSize.width, varScreenSize.height);
    varBackLayer->setAnchorPoint(Vec2(0,0));
    varBackLayer->setPosition(Vec2(0,0));
    this->addChild(varBackLayer);
    
    varSinglePlayerButton = ui::Button::create("placeholderButton.png");
    varSinglePlayerButton->setPosition(Vec2(varScreenSize.width/2.0f,varScreenSize.height/2.0f));
    Size btnSize = Size(varScreenSize.width*0.6, varScreenSize.height*0.2);
    varSinglePlayerButton->setScale9Enabled(true);
    varSinglePlayerButton->setScale(btnSize.width/varSinglePlayerButton->getContentSize().width, btnSize.height/varSinglePlayerButton->getContentSize().height);
    
    varSinglePlayerButton->addTouchEventListener(CC_CALLBACK_2(RAMainMenuScene::startSinglePlayerCallback, this));
    
    
    varBackLayer->addChild(varSinglePlayerButton);
    
    
    
    return true;
}

void RAMainMenuScene::startSinglePlayerCallback(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    
    switch(type)
    {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            printf("Starting Single Player Game\n");
            _director->pushScene(RAGameScene::createScene(kGAMEMODE_SINGLEPLAYER));
            break;
        default:
            break;
    }
    
}


