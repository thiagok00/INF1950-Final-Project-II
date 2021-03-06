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
    
    auto backgroundImage = Sprite::create("backgroundapp.png");
    varBackLayer->addChild(backgroundImage);
    backgroundImage->setAnchorPoint(Vec2(0,0));
    backgroundImage->setPosition(Vec2(0,0));
    backgroundImage->setScale(varScreenSize.height/backgroundImage->getContentSize().height);
    
    varSinglePlayerButton = ui::Button::create("SINGLEPLAYER BUTTON.png");
    varSinglePlayerButton->setPosition(Vec2(varScreenSize.width/2.0f,varScreenSize.height/2.0f));
    Size btnSize = Size(varScreenSize.width*0.8, varScreenSize.height*0.11);
    varSinglePlayerButton->setScale9Enabled(true);
    varSinglePlayerButton->setScale(btnSize.width/varSinglePlayerButton->getContentSize().width, btnSize.height/varSinglePlayerButton->getContentSize().height);
    varSinglePlayerButton->_ID = kGAMEMODE_SINGLEPLAYER;
    varSinglePlayerButton->addTouchEventListener(CC_CALLBACK_2(RAMainMenuScene::startSinglePlayerCallback, this));
    
    
    varBackLayer->addChild(varSinglePlayerButton);
    
    varMultiPlayerButton = ui::Button::create("MULTIPLAYER BUTTON.png");
    varMultiPlayerButton->setPosition(Vec2(varScreenSize.width/2.0f,varScreenSize.height*0.35));
    varMultiPlayerButton->setScale9Enabled(true);
    varMultiPlayerButton->setScale(btnSize.width/varMultiPlayerButton->getContentSize().width, btnSize.height/varMultiPlayerButton->getContentSize().height);
    varMultiPlayerButton->_ID = kGAMEMODE_OFFLINE_MULTIPLAYER;
    varMultiPlayerButton->addTouchEventListener(CC_CALLBACK_2(RAMainMenuScene::startSinglePlayerCallback, this));
    
    
    varOnlineButton = ui::Button::create("ONLINE MODE.png");
    varOnlineButton->setPosition(Vec2(varScreenSize.width/2.0f,varScreenSize.height*0.20));
    varOnlineButton->setScale9Enabled(true);
    varOnlineButton->setScale(btnSize.width/varOnlineButton->getContentSize().width, btnSize.height/varOnlineButton->getContentSize().height);
    
    
    
    
    auto heroArt = Sprite::create("heroArt.png");
    
    heroArt->setPosition(Vec2(varScreenSize.width/2.0f, varScreenSize.height - heroArt->getContentSize().height));
    varBackLayer->addChild(heroArt);
    varBackLayer->addChild(varMultiPlayerButton);
    varBackLayer->addChild(varOnlineButton);
    
    return true;
}

void RAMainMenuScene::startSinglePlayerCallback(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    
    switch(type)
    {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            printf("RAMainMenuScene: Starting Single Player Game\n");
            _director->pushScene(RAGameScene::createScene(pSender->_ID));
            break;
        default:
            break;
    }
    
}
