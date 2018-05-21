#include "RAGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* RAGameScene::createScene()
{
    return RAGameScene::create();
}

bool RAGameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    varScreenSize = this->getContentSize();//Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();

    varBackLayer = LayerColor::create(Color4B::WHITE, varScreenSize.width, varScreenSize.height);
    varBackLayer->setAnchorPoint(Vec2(0,0));
    varBackLayer->setPosition(Vec2(0,0));
    this->addChild(varBackLayer);
    
    
    
    return true;
}

