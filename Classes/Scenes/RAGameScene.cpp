#include "RAGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define MOVE_ACTION_TAG 100

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
   
    //SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Untitled.plist");

    varScreenSize = this->getContentSize();//Director::getInstance()->getVisibleSize();
    //Vec2 origin = Director::getInstance()->getVisibleOrigin();

    varBackLayer = LayerColor::create(Color4B(97, 24, 22, 255), varScreenSize.width, varScreenSize.height);
    varBackLayer->setAnchorPoint(Vec2(0,0));
    varBackLayer->setPosition(Vec2(0,0));
    this->addChild(varBackLayer, 0);
    
    if(gameMode == kGAMEMODE_SINGLEPLAYER)
    {
        gameController = new RASinglePlayerGameController(this);
        gameController->startGame();
    }
    
    //touch events
    auto listener1 = EventListenerTouchOneByOne::create();
    listener1->onTouchBegan = CC_CALLBACK_2(RAGameScene::onTouchBegan, this);
    listener1->onTouchMoved = CC_CALLBACK_2(RAGameScene::onTouchMoved, this);
    listener1->onTouchEnded = CC_CALLBACK_2(RAGameScene::onTouchEnded, this);
    listener1->onTouchCancelled = CC_CALLBACK_2(RAGameScene::onTouchCancelled, this);
    // Add listener
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener1, this);
    isTouchDown = false;
    initialTouchPos[0] = 0;
    initialTouchPos[1] = 0;
    this->scheduleUpdate();

    
    return true;
}

//  MARK: RASceneProtocol Methods
void RAGameScene::renderMap (RAMap* map)
{
    printf("RAGameScene: Rendering Map\n");

    Size tileSize;
    tileSize.width = varScreenSize.width/MAP_MAX_ROW;
    tileSize.height = tileSize.width;
    
    int xPos;
    int yPos = varScreenSize.height*0.3;
    
    for(int i = 0; i < MAP_MAX_ROW; i++)
    {
        xPos = tileSize.width/2.0f;
        for(int j = 0; j < MAP_MAX_COL; j++)
        {
            RATile *t;
            t = map->getTile(i, j);
            
            //temp
            Sprite *tileSprite = Sprite::create("cave_ground.png");
            tileSprite->setScale(tileSize.width/tileSprite->getContentSize().width);
            tileSprite->setAnchorPoint(Vec2(0.5,0.5));
            tileSprite->setPosition(xPos,yPos);
            
            mapSprites.push_back(tileSprite);
            
            varBackLayer->addChild(tileSprite,100);
            
            
            xPos += tileSize.width;
            if (j+1 == MAP_MAX_COL)
                yPos += tileSize.height;
        }
        
    }
}

void RAGameScene::loadPlayer (RAPlayer* player)
{
    Size playerSize;
    playerSize.width = varScreenSize.width/MAP_MAX_ROW;
    playerSize.height = playerSize.width;
    
    Sprite *playerSprite = Sprite::create("player_idle_south.png");

    playerSprite->setScale(playerSize.width/playerSprite->getContentSize().width);
    playerSprite->setAnchorPoint(Vec2(0.5,0.5));
    
    playerSprite->setPosition(mapSprites.at(MAP_MAX_COL*player->tile->getCol() + player->tile->getRow())->getPosition());
    varBackLayer->addChild(playerSprite,101);
    
    player1Node.pSprite = playerSprite;
    player1Node.pController = player;
}

void RAGameScene::playerMoved(RAPlayer* player, int direction)
{
    Sprite *playerSprite;

    playerSprite = player1Node.pSprite;
    
    Vec2 destination = mapSprites.at(MAP_MAX_COL*player->tile->getCol() + player->tile->getRow())->getPosition();

    auto moveAction = MoveTo::create(0.5, destination);
    
    moveAction->setTag(MOVE_ACTION_TAG);
    playerSprite->runAction(moveAction);
}

// MARK: Touch Events
bool RAGameScene::onTouchBegan(Touch* touch, Event* event)
{
    printf("RAGameScene onTouchBegan\n");
    
    initialTouchPos[0] = touch->getLocation().x;
    initialTouchPos[1] = touch->getLocation().y;
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;
    
    isTouchDown = true;
    
    return true;
}

void RAGameScene::onTouchMoved(Touch *touch, Event *event)
{
    currentTouchPos[0] = touch->getLocation().x;
    currentTouchPos[1] = touch->getLocation().y;

}

void RAGameScene::onTouchCancelled(Touch *touch, Event *event)
{
    onTouchEnded(touch, event);
}

void RAGameScene::onTouchEnded(Touch *touch, Event *event)
{
    isTouchDown = false;
}

void RAGameScene::update(float dt)
{
    if (true == isTouchDown)
    {
        
        if(player1Node.pSprite->getActionByTag(MOVE_ACTION_TAG) != nullptr)
            return;
        
        if (initialTouchPos[0] - currentTouchPos[0] > varScreenSize.width * 0.05)
        {
            CCLOG("SWIPED LEFT");
            isTouchDown = false;
            
            gameController->movePlayer(kDIRECTION_LEFT);
        }
        else if (initialTouchPos[0] - currentTouchPos[0] < - varScreenSize.width * 0.05)
        {
            CCLOG("SWIPED RIGHT");
            isTouchDown = false;
            
            gameController->movePlayer(kDIRECTION_RIGHT);

        }
        else if (initialTouchPos[1] - currentTouchPos[1] > varScreenSize.width * 0.05)
        {
            CCLOG("SWIPED DOWN");
            isTouchDown = false;
            
            gameController->movePlayer(kDIRECTION_DOWN);

        }
        else if (initialTouchPos[1] - currentTouchPos[1] < - varScreenSize.width * 0.05)
        {
            CCLOG("SWIPED UP");
            isTouchDown = false;
            
            gameController->movePlayer(kDIRECTION_UP);

        }
    }
}
