#include "RAGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define MOVE_ACTION_TAG 1000

#define zORDER_CREATURE 102
#define zORDER_PLAYER 103
#define zORDER_TILE 101
#define zORDER_EFFECTS 104
#define zORDER_HUD 999


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
    
    //HUD
    varExperienceLabel = Label::createWithTTF("----", "fonts/arial.ttf", 32);
    varExperienceLabel->setAnchorPoint(Vec2(0.5, 0.5));
    varExperienceLabel->setPosition(Vec2(varScreenSize.width/2.0f, varScreenSize.height - varExperienceLabel->getBoundingBox().size.height/2.0f));
    
    healthBarBaseSize = Size(varScreenSize.width*0.6, varScreenSize.height*0.08);
    healthBarBase = LayerColor::create(Color4B::BLACK, healthBarBaseSize.width, healthBarBaseSize.height);
    healthBarBase->setAnchorPoint(Vec2(0.5,0.5));
    healthBarBase->setPosition(varScreenSize.width*0.3, healthBarBase->getBoundingBox().size.height/2.0f);
    varBackLayer->addChild(healthBarBase);
    
    healthBar = LayerColor::create(Color4B::RED, healthBarBaseSize.width, healthBarBaseSize.height);
    healthBar->setAnchorPoint(Vec2(0.0,0.0));
    healthBar->setPosition(Vec2(0,0));
    healthBarBase->addChild(healthBar);
    
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
    /*************/

    varBackLayer->addChild(varExperienceLabel);

    
    return true;
}

//
//MARK: AUX Methods
//

void RAGameScene::auxUpdateExperienceLabelText(int experiencePoints)
{
    std::ostringstream oss1;
    oss1 << experiencePoints;
    std::string buf = oss1.str();
    
    varExperienceLabel->setString(buf);
}

void RAGameScene::auxUpdateHealthBar(float healthPercentage)
{
    healthBar->removeFromParentAndCleanup(true);
    healthBar = LayerColor::create(Color4B::RED, healthBarBaseSize.width*healthPercentage, healthBarBaseSize.height);
    healthBar->setAnchorPoint(Vec2(0.5,0.5));
    healthBar->setPosition(Vec2(0,0));
    healthBarBase->addChild(healthBar);
}

Label* RAGameScene::auxCreateDamageLabel(int damage, Color4B textColor, Vec2 pos)
{
    std::ostringstream oss1;
    oss1 << damage;
    std::string buf = oss1.str();
    Label *damageLabel = Label::createWithTTF(buf, "fonts/arial.ttf", 25);
    damageLabel->setAnchorPoint(Vec2(0.5,0.5));
    damageLabel->setTextColor(textColor);
    damageLabel->setPosition(pos);
    varBackLayer->addChild(damageLabel, zORDER_EFFECTS);
    
    auto act1 = MoveBy::create(1, Vec2(0, tileSize.width));
    auto act2 = FadeOut::create(1);
    
    damageLabel->runAction(act1);
    damageLabel->runAction(act2);
    //TODO: remove from parent damageLabel
    
    
    return damageLabel;
}


//
//  MARK: RASceneProtocol Methods
//
void RAGameScene::renderMap (RAMap* map)
{
    printf("RAGameScene: Rendering Map\n");

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

            //render creature of tile
            if(t->creature != nullptr)
            {
                Sprite *creatureSprite;
                Size creatureSize = tileSize;
                switch(t->creature->id)
                {
                    case Rat:
                        creatureSprite = Sprite::create("creature_example.png");
                        break;
                    case Cave_rat:
                        creatureSprite = Sprite::create("creature_example.png");
                        break;
                }
                this->creatureExample.cSprite = creatureSprite;
                this->creatureExample.cController = t->creature;
                
                creatureSprite->setScale(creatureSize.width/creatureSprite->getContentSize().width);
                creatureSprite->setAnchorPoint(Vec2(0.5,0.5));
                creatureSprite->setPosition(xPos,yPos);
                varBackLayer->addChild(creatureSprite,zORDER_CREATURE);
            }
            
            mapSprites.push_back(tileSprite);
            
            varBackLayer->addChild(tileSprite,zORDER_TILE);
            xPos += tileSize.width;
        }
        yPos += tileSize.height;
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
    
    playerSprite->setPosition(mapSprites.at(MAP_MAX_ROW*player->tile->getRow() + player->tile->getCol())->getPosition());
    varBackLayer->addChild(playerSprite,zORDER_PLAYER);
    
    player1Node.pSprite = playerSprite;
    player1Node.pController = player;
    
    auxUpdateExperienceLabelText(player->getExperiencePoints());
}

void RAGameScene::playerMoved(RAPlayer* player, RATile * tile)
{
    Sprite *playerSprite;

    playerSprite = player1Node.pSprite;
    
    Vec2 destination = mapSprites.at(MAP_MAX_ROW*tile->getRow() + tile->getCol())->getPosition();

    auto moveAction = MoveTo::create(0.3, destination);
    
    moveAction->setTag(MOVE_ACTION_TAG);
    playerSprite->runAction(moveAction);
}

void RAGameScene::playerAttackedCreature (RAPlayer* player, RACreature *creature, int damage, bool died)
{
    auto blinkAction = Blink::create(0.5, 3);
    creatureExample.cSprite->runAction(blinkAction);
    
    //Damage Feedback
    auxCreateDamageLabel(damage,Color4B::YELLOW,creatureExample.cSprite->getPosition());
    

    
    
    if (died)
    {
        //creature died, do something
        auxUpdateExperienceLabelText(player->getExperiencePoints());
    }
}

void RAGameScene::creatureMoved(RACreature *creature, int row, int col)
{
    Sprite * creatureSprite = creatureExample.cSprite;
    Vec2 destination = mapSprites[col + row*MAP_MAX_COL]->getPosition();
    
    auto moveAction = MoveTo::create(0.3, destination);
    
    moveAction->setTag(MOVE_ACTION_TAG);
    creatureSprite->runAction(moveAction);
}

void RAGameScene::creatureAttackedPlayer(RACreature *creature, RAPlayer * player, int damage)
{
    auto rt = RotateBy::create(0.5, 0.8);
    auto rt2 = rt->reverse();
    auto seq = Sequence::create(rt,rt2, NULL);
    this->creatureExample.cSprite->runAction(seq);
    
    auxCreateDamageLabel(damage, Color4B::RED, player1Node.pSprite->getPosition());
    
    auto blinkAction = Blink::create(0.5, 3);
    player1Node.pSprite->runAction(blinkAction);
    
    auxUpdateHealthBar((float)player->healthPoints/(float)player->maxHealthPoints);
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
            
            gameController->playerAction(LEFT);
        }
        else if (initialTouchPos[0] - currentTouchPos[0] < - varScreenSize.width * 0.05)
        {
            CCLOG("SWIPED RIGHT");
            isTouchDown = false;
            
            gameController->playerAction(RIGHT);

        }
        else if (initialTouchPos[1] - currentTouchPos[1] > varScreenSize.width * 0.05)
        {
            CCLOG("SWIPED DOWN");
            isTouchDown = false;
            
            gameController->playerAction(DOWN);

        }
        else if (initialTouchPos[1] - currentTouchPos[1] < - varScreenSize.width * 0.05)
        {
            CCLOG("SWIPED UP");
            isTouchDown = false;
            
            gameController->playerAction(UP);

        }
    }
}
