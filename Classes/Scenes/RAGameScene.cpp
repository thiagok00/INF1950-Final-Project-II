#include "RAGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define MOVE_ACTION_TAG 1000

#define zORDER_CREATURE 110
#define zORDER_PLAYER 111
#define zORDER_ITEM 105
#define zORDER_TILE 101
#define zORDER_EFFECTS 120
#define zORDER_HUD 999

#define TAG_BTN_SLOT1   1
#define TAG_BTN_SLOT2   2
#define TAG_BTN_SLOT3   3
#define TAG_BTN_SLOT4   4
#define TAG_BTN_SLOT5   5
#define TAG_BTN_SLOT6   6


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
    
    //
    //HUD
    //
    varExperienceLabel = Label::createWithTTF("----", "fonts/arial.ttf", 32);
    varExperienceLabel->setAnchorPoint(Vec2(0.5, 0.5));
    varExperienceLabel->setPosition(Vec2(varScreenSize.width/2.0f, varScreenSize.height - varExperienceLabel->getBoundingBox().size.height/2.0f));
    
    //health bar
    healthBarBaseSize = Size(varScreenSize.width*0.6, varScreenSize.height*0.05);
    healthBarBase = LayerColor::create(Color4B::BLACK, healthBarBaseSize.width, healthBarBaseSize.height);
    healthBarBase->setAnchorPoint(Vec2(0.5,0.5));
    healthBarBase->setPosition(varScreenSize.width*0.3, healthBarBase->getBoundingBox().size.height*2);
    varBackLayer->addChild(healthBarBase);
    
    healthBar = LayerColor::create(Color4B::RED, healthBarBaseSize.width, healthBarBaseSize.height);
    healthBar->setAnchorPoint(Vec2(0.0,0.0));
    healthBar->setPosition(Vec2(0,0));
    healthBarBase->addChild(healthBar);
    
    //mana bar
    manaBarBase = LayerColor::create(Color4B::BLACK, healthBarBaseSize.width, healthBarBaseSize.height);
    manaBarBase->setAnchorPoint(Vec2(0.5,0.5));
    manaBarBase->setPosition(varScreenSize.width*0.3, manaBarBase->getBoundingBox().size.height/2.0f);
    varBackLayer->addChild(manaBarBase);
    
    manaBar = LayerColor::create(Color4B::BLUE, healthBarBaseSize.width, healthBarBaseSize.height);
    manaBar->setAnchorPoint(Vec2(0.0,0.0));
    manaBar->setPosition(Vec2(0,0));
    manaBarBase->addChild(manaBar);
    
    
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

    
    //ITEM SLOT BUTTONS
    Size slotBtnSize = Size(varScreenSize.width*0.1, varScreenSize.width*0.1);

    ui::Button* btnVec[6];
    Vec2 pos[6];
    pos[0] = Vec2(slotBtnSize.width/2.0f, slotBtnSize.height + slotBtnSize.height/2.0f);
    pos[1] = Vec2(pos[0].x + slotBtnSize.width, pos[0].y);
    pos[2] = Vec2(pos[1].x + slotBtnSize.width, pos[0].y);
    pos[3] = Vec2(pos[0].x, pos[0].y - slotBtnSize.height);
    pos[4] = Vec2(pos[3].x + slotBtnSize.width, pos[3].y);
    pos[5] = Vec2(pos[4].x + slotBtnSize.width, pos[3].y);
    
    for(int i = 0; i < 6; i++)
    {
        btnVec[i] = ui::Button::create("placeholderButton.png");
        btnVec[i]->setAnchorPoint(Vec2(0.5, 0.5));
        btnVec[i]->setPosition(pos[i]);
        btnVec[i]->setScale9Enabled(true);
        btnVec[i]->setScale(slotBtnSize.width/btnVec[i]->getContentSize().width, slotBtnSize.height/btnVec[i]->getContentSize().height);
        btnVec[i]->_ID = i+1;
        btnVec[i]->addTouchEventListener(CC_CALLBACK_2(RAGameScene::useItemSlotButton, this));
        varBackLayer->addChild(btnVec[i], zORDER_HUD);
    }
    varItemSlot1Button = btnVec[0];
    varItemSlot2Button = btnVec[1];
    varItemSlot3Button = btnVec[2];
    varItemSlot4Button = btnVec[3];
    varItemSlot5Button = btnVec[4];
    varItemSlot6Button = btnVec[5];

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

void RAGameScene::auxUpdateManaBar(float manaPercentage)
{
    manaBar->removeFromParentAndCleanup(true);
    manaBar = LayerColor::create(Color4B::BLUE, healthBarBaseSize.width*manaPercentage, healthBarBaseSize.height);
    manaBar->setAnchorPoint(Vec2(0.5,0.5));
    manaBar->setPosition(Vec2(0,0));
    manaBarBase->addChild(healthBar);
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
            
            //render item
            if(t->droppedItem != nullptr)
            {
                Color4B color;
                color = Color4B::MAGENTA;
                LayerColor* itemSpr = LayerColor::create(color, tileSize.width*0.6, tileSize.height*0.6);
                itemSpr->setAnchorPoint(Vec2(0.5, 0.5));
                tileSprite->addChild(itemSpr, zORDER_ITEM);
                
                itemExample.iSprite = itemSpr;
                itemExample.iController = t->droppedItem;
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

void RAGameScene::playerMovedAndCaughtItem (RAPlayer* player, RATile * tile, RAItem *item)
{
    playerMoved(player, tile);
    
    //TODO: implement this right
    this->itemExample.iSprite->removeFromParentAndCleanup(true);
    this->varItemSlot1Button->setColor(Color3B::MAGENTA);
    
    
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

void RAGameScene::useItemSlotButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    int slot = (int) pSender->_ID;
    
    RAPlayer *player = player1Node.pController;

    switch(type)
    {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            CCLOG("clicked button tag %u", pSender->_ID);
            if(gameController->playerUseItem(player1Node.pController, slot))
                varItemSlot1Button->setColor(Color3B::RED);
            //FIXME: tirar essa linha
            this->auxUpdateHealthBar((float)player->healthPoints/(float)player->maxHealthPoints);
            break;
        default:
            break;
    }
}
