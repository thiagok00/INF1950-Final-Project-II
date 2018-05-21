#include "RAGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* RAGameScene::createScene(int gameMode)
{
    RAGameScene *pRet = new(std::nothrow) RAGameScene(); \
    if (pRet && pRet->init(gameMode))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
    
}

bool RAGameScene::init(int gameMode)
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
    
    if(gameMode == kGAMEMODE_SINGLEPLAYER)
    {
        gameController = new RASinglePlayerGameController(this);
        gameController->startGame();
    }
    
    
    return true;
}

void RAGameScene::renderMap (RAMap* map)
{
    printf("Rendering Map\n");
}
