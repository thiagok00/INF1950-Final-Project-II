#include "RAGameScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

#define MOVE_ACTION_TAG 1000
#define ATK_ACTION_TAG  1001
#define HURT_ACTION_TAG 1002

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
    
    //////////////////////////////
    // 2. init vars
    player1Node = nullptr;
    player2Node = nullptr;
    mapNode = nullptr;
    
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
    
    //ITEM SLOT BUTTONS
    Size slotBtnSize = Size(varScreenSize.width*0.1, varScreenSize.width*0.1);
    
    Vec2 pos[6];
    pos[0] = Vec2(slotBtnSize.width/2.0f, slotBtnSize.height + slotBtnSize.height/2.0f);
    pos[1] = Vec2(pos[0].x + slotBtnSize.width, pos[0].y);
    pos[2] = Vec2(pos[1].x + slotBtnSize.width, pos[0].y);
    pos[3] = Vec2(pos[0].x, pos[0].y - slotBtnSize.height);
    pos[4] = Vec2(pos[3].x + slotBtnSize.width, pos[3].y);
    pos[5] = Vec2(pos[4].x + slotBtnSize.width, pos[3].y);
    
    for(int i = 0; i < 6; i++)
    {
        auto btn = ui::Button::create("placeholderButton.png");
        btn->setAnchorPoint(Vec2(0.5, 0.5));
        btn->setPosition(pos[i]);
        btn->setScale9Enabled(true);
        btn->setScale(slotBtnSize.width/btn->getContentSize().width, slotBtnSize.height/btn->getContentSize().height);
        btn->_ID = i;
        btn->addTouchEventListener(CC_CALLBACK_2(RAGameScene::useItemSlotButton, this));
        varBackLayer->addChild(btn, zORDER_HUD);
        varItensSlotButtons.push_back(btn);
    }
    
    //pass turn button
    auto passTurnButton = ui::Button::create("placeholderButton.png");
    passTurnButton->setAnchorPoint(Vec2(0.5, 0.5));
    passTurnButton->setPosition(Vec2(varScreenSize.width/2.0f, varScreenSize.height*0.23));
    Size passTurnBtnSize = Size(varScreenSize.width*0.6, varScreenSize.height*0.05);
    passTurnButton->setScale(passTurnBtnSize.width/passTurnButton->getContentSize().width, passTurnBtnSize.height/passTurnButton->getContentSize().height);
    passTurnButton->addTouchEventListener(CC_CALLBACK_2(RAGameScene::passTurnButtonCallback, this));
    
    varBackLayer->addChild(passTurnButton, zORDER_HUD);
    
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
    
    this->gameMode = gameMode;
    if(gameMode == kGAMEMODE_SINGLEPLAYER || gameMode == kGAMEMODE_OFFLINE_MULTIPLAYER)
    {
        gameController = new RASinglePlayerGameController(this);
        gameController->startGame();
    }
    return true;
}

//
//MARK: AUX Methods
//

void RAGameScene::auxUpdateScoreLabelText()
{
    int score = 0;
    if (player1Node != nullptr)
        score += player1Node->pController->score;
    if (player2Node != nullptr)
        score += player2Node->pController->score;
    std::ostringstream oss1;
    oss1 << score;
    std::string buf = oss1.str();
    
    varExperienceLabel->setString(buf);
}

void RAGameScene::auxUpdateHealthBar()
{
    RAPlayer *player = auxGetPlayerNodeById(playerRound)->pController;
    float healthPercentage = (float)player->healthPoints/(float)player->maxHealthPoints;
    healthBar->removeFromParentAndCleanup(true);
    healthBar = LayerColor::create(Color4B::RED, healthBarBaseSize.width*healthPercentage, healthBarBaseSize.height);
    healthBar->setAnchorPoint(Vec2(0.5,0.5));
    healthBar->setPosition(Vec2(0,0));
    healthBarBase->addChild(healthBar);
}

void RAGameScene::auxUpdateManaBar()
{
    RAPlayer *player = auxGetPlayerNodeById(playerRound)->pController;
    float manaPercentage = (float)player->manaPoints/(float)player->maxManaPoints;
    manaBar->removeFromParentAndCleanup(true);
    manaBar = LayerColor::create(Color4B::BLUE, healthBarBaseSize.width*manaPercentage, healthBarBaseSize.height);
    manaBar->setAnchorPoint(Vec2(0.5,0.5));
    manaBar->setPosition(Vec2(0,0));
    manaBarBase->addChild(manaBar);
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

void RAGameScene::auxUpdatePlayerItensSlots()
{
    for(auto btn :varItensSlotButtons)
    {
        btn->setColor(Color3B::RED);
    }
    auto playerNode = auxGetPlayerNodeById(playerRound);
    for(auto iNode : playerNode->items)
    {
        varItensSlotButtons.at(iNode->slot)->setColor(Color3B::MAGENTA);
    }
}

RAGameScene::PlayerNode* RAGameScene::auxGetPlayerNodeById(int playerID)
{
    if (player1Node != nullptr &&  player1Node->pController != nullptr && player1Node->pController->playerID == playerID)
    {
        return player1Node;
    }
    else if (player2Node != nullptr && player2Node->pController != nullptr && player2Node->pController->playerID == playerID)
    {
        return player2Node;
    }
    else
    {
        CCASSERT(1, "ERROR - PLAYER NOT FOUND");
        return player1Node;
    }
}

int RAGameScene::auxGetTileIndex(int row, int col)
{
    return MAP_MAX_ROW*row + col;
}


//
//  MARK: RASceneProtocol Methods
//
void RAGameScene::loadMap (RAMap* map)
{
    printf("RAGameScene: Rendering Map\n");
    
    tileSize.width = varScreenSize.width/MAP_MAX_ROW;
    tileSize.height = tileSize.width;
    if(mapNode == nullptr)
    {
        mapNode = new MapNode();
        int xPos;
        int yPos = varScreenSize.height*0.3;
        
        for(int i = 0; i < MAP_MAX_ROW; i++)
        {
            xPos = tileSize.width/2.0f;
            for(int j = 0; j < MAP_MAX_COL; j++)
            {
                RATile* tile = map->getTile(i, j);
                TileNode *t = new TileNode();
                t->row = tile->getRow();
                t->col = tile->getCol();
                t->walkable = tile->isWakable();
                
                //temp
                t->sprite = Sprite::create("cave_ground.png");
                t->sprite->setScale(tileSize.width/t->sprite->getContentSize().width);
                t->sprite->setAnchorPoint(Vec2(0.5,0.5));
                t->sprite->setPosition(xPos,yPos);
                if(tile->getType() == Fire)
                {
                    t->sprite->setColor(Color3B::RED);
                }
                else if (tile->getType() == Poison)
                {
                    t->sprite->setColor(Color3B::GREEN);
                }
                else if (tile->getType() == Stairs)
                {
                    t->sprite->setColor(Color3B::GRAY);
                }
                
                //render creature of tile
                if(tile->entity != nullptr)
                {
                    if (RACreature * tileCreature = dynamic_cast<RACreature*>(tile->entity))
                    {
                        CreatureNode * creature = new CreatureNode();
                        creature->size = tileSize;
                        creature->isDead = tileCreature->isDead();
                        creature->creatureID = tileCreature->id;
                        switch(creature->creatureID)
                        {
                            case Rat:
                                creature->cSprite = Sprite::create("creature_example.png");
                                break;
                            case Cave_Rat:
                                creature->cSprite = Sprite::create("creature_example.png");
                                break;
                        }
                        
                        creature->cSprite->setScale(creature->size.width/creature->cSprite->getContentSize().width);
                        creature->cSprite->setAnchorPoint(Vec2(0.5,0.5));
                        creature->cSprite->setPosition(xPos,yPos);
                        varBackLayer->addChild(creature->cSprite,zORDER_CREATURE);
                        varCreaturesMap.insert(std::make_pair(creature->creatureID, creature));
                    }
                }
                
                //render item
                if(tile->droppedItem != nullptr)
                {
                    ItemNode *item = new ItemNode();
                    item->itemType = tile->droppedItem->getItemType();
                    item->charges = tile->droppedItem->getCharges();
                    
                    //TODO: sprites of itens
                    //temporary "sprite"
                    Color4B color = Color4B::MAGENTA;
                    item->iSprite = LayerColor::create(color, tileSize.width*0.6, tileSize.height*0.6);
                    item->iSprite->setAnchorPoint(Vec2(0.5, 0.5));
                    t->sprite->addChild(item->iSprite, zORDER_ITEM);
                    
                    t->droppedItem = item;
                    item->iSprite = item->iSprite;
                }
                
                mapNode->tiles.push_back(t);
                
                varBackLayer->addChild(t->sprite,zORDER_TILE);
                xPos += tileSize.width;
            }
            yPos += tileSize.height;
        }
    }
}

void RAGameScene::loadPlayer (RAPlayer* player)
{
    PlayerNode * playerNode = nullptr;
    if (player->playerID == PLAYER1_TURN && player1Node != nullptr)
    {
        playerNode = player1Node;
    }
    else if (player->playerID == PLAYER2_TURN && player2Node != nullptr)
    {
         playerNode = player2Node;
    }
    if(playerNode == nullptr)
    {
        playerNode = new PlayerNode();
        
        if (player->playerID == PLAYER1_TURN)
            player1Node = playerNode;
        else if (player->playerID == PLAYER2_TURN)
            player2Node = playerNode;

        
        Size playerSize;
        playerSize.width = varScreenSize.width/MAP_MAX_ROW;
        playerSize.height = playerSize.width;
        
        playerNode->node = Node::create();
        playerNode->node->setContentSize(playerSize);
        
        playerNode->playerSize = playerSize;
        
        playerNode->pSprite = Sprite::create("hero3.png");
        
        playerNode->pSprite->setScale(playerSize.width/playerNode->pSprite->getContentSize().width);
        playerNode->pSprite->setAnchorPoint(Vec2(0.5,0.5));
        varBackLayer->addChild(playerNode->node,zORDER_PLAYER);
        playerNode->node->addChild(playerNode->pSprite);
        playerNode->occupiedSlots = 0;
        playerNode->maxSlots = player->getMaxSlots();
        
        
    }
    playerNode->level = 0;
    playerNode->pController = player;
   // playerNode->pSprite->setPosition(mapNode->tiles.at(MAP_MAX_ROW*player->tile->getRow() + player->tile->getCol())->sprite->getPosition());
    playerNode->node->setPosition(mapNode->tiles.at(MAP_MAX_ROW*player->row + player->col)->sprite->getPosition());
    
    auxUpdateScoreLabelText();
    auxUpdateHealthBar();
    auxUpdateManaBar();
    
    auxUpdatePlayerItensSlots();
}

void RAGameScene::playerMoved(int playerID, int row, int col)
{
    auto player = auxGetPlayerNodeById(playerID);
    
    Vec2 destination = mapNode->tiles.at(MAP_MAX_ROW*row + col)->sprite->getPosition();
    
    auto moveAction = MoveTo::create(0.3, destination);
    
    moveAction->setTag(MOVE_ACTION_TAG);
    player->node->runAction(moveAction);
}

void RAGameScene::playerMovedAndCaughtItem (int playerID, int row, int col, int atSlot, ItemID itemType, int charges)
{
    playerMoved(playerID, row, col);
    
    TileNode *tNode = mapNode->tiles.at(auxGetTileIndex(row, col));
    PlayerNode *playerNode = auxGetPlayerNodeById(playerID);
    
    InventaryItemNode *iNode = new InventaryItemNode();
    iNode->itemType = itemType;
    iNode->charges = charges;
    iNode->slot = atSlot;
    //TODO: add iventary item sprite
    //iNode->iSprite = Sprite::create
    
    playerNode->items.push_back(iNode);
    
    //removing item from the floor
    tNode->droppedItem->iSprite->removeFromParentAndCleanup(true);
    tNode->droppedItem = nullptr;
    delete tNode->droppedItem;
    
    auxUpdatePlayerItensSlots();
}

void RAGameScene::playerAttackedCreature (int playerID, int creatureID, int damage, bool died, int score, bool leveledUp)
{
    auto blinkAction = Blink::create(0.5, 3);
    blinkAction->setTag(HURT_ACTION_TAG);
    
    Sprite *cSprite = varCreaturesMap.find(creatureID)->second->cSprite;
    
    cSprite->stopActionByTag(HURT_ACTION_TAG);
    cSprite->setVisible(true);
    cSprite->runAction(blinkAction);
    
    //Damage Feedback
    auxCreateDamageLabel(damage,Color4B::YELLOW, cSprite->getPosition());

    if (died)
    {
        //creature died, do something
        auxUpdateScoreLabelText();
        //cSprite->removeFromParentAndCleanup(true);
    }
    if(leveledUp)
    {
        auto playerNode = auxGetPlayerNodeById(playerID);
        playerNode->level++;
        Sprite *levelUpSprite = Sprite::create("levelUp.png");
        levelUpSprite->setScale(playerNode->playerSize.width/levelUpSprite->getBoundingBox().size.width,
                                playerNode->playerSize.height*0.4/levelUpSprite->getBoundingBox().size.height);
        
        levelUpSprite->setAnchorPoint(Vec2(0.5, 0.5));
        levelUpSprite->setPosition(Vec2(0,0));
        auto fadeout = FadeOut::create(1.5);
        auto moveby = MoveBy::create(1.5, Vec2(0,playerNode->playerSize.height/2.0f));
        
        levelUpSprite->runAction(moveby);
        levelUpSprite->runAction(fadeout);
        //FIXME: memory leak levelupSprite
        playerNode->node->addChild(levelUpSprite);
        
    }
    
}

void RAGameScene::creatureMoved(int creatureID, int row, int col)
{
    Sprite *cSprite = varCreaturesMap.find(creatureID)->second->cSprite;
    Vec2 destination = mapNode->tiles[auxGetTileIndex(row, col)]->sprite->getPosition();
    
    auto moveAction = MoveTo::create(0.3, destination);
    
    moveAction->setTag(MOVE_ACTION_TAG);
    cSprite->runAction(moveAction);
}

void RAGameScene::creatureAttackedPlayer(int creatureID, int playerID, int damage)
{
    auto playerNode = auxGetPlayerNodeById(playerID);
    auto rt = RotateBy::create(0.5, 0.8);
    auto rt2 = rt->reverse();
    auto seq = Sequence::create(rt,rt2, NULL);
    
    Sprite *cSprite = varCreaturesMap.find(creatureID)->second->cSprite;
    cSprite->runAction(seq);
    
    auxCreateDamageLabel(damage, Color4B::RED, playerNode->node->getPosition());
    
    auto blinkAction = Blink::create(0.5, 3);
    blinkAction->setTag(HURT_ACTION_TAG);
    playerNode->pSprite->stopActionByTag(HURT_ACTION_TAG);
    playerNode->pSprite->setVisible(true);
    
    playerNode->pSprite->runAction(blinkAction);
    
    auxUpdateHealthBar();
}

void RAGameScene::playerBadStatus(int playerID, Status_ID statusID, int damage)
{
    auto playerNode = auxGetPlayerNodeById(playerID);
    Sprite* statusSpr;
    
    switch(statusID)
    {
        case BURNING:
            statusSpr = Sprite::create("burn_1.png");
            auxCreateDamageLabel(damage, Color4B::RED, playerNode->node->getPosition());
            break;
        case POISONED:
            statusSpr = Sprite::create("poison_1.png");
            auxCreateDamageLabel(damage, Color4B::GREEN, playerNode->node->getPosition());
            break;
    }
    
    statusSpr->setScale(playerNode->playerSize.width/statusSpr->getBoundingBox().size.width);
    statusSpr->setPosition(Vec2(0,0
                        ));

    playerNode->node->addChild(statusSpr,9999333);
    //FIXME: memory leak burnSpr
    statusSpr->runAction(FadeOut::create(1.5));

    auxUpdateHealthBar();
}

void RAGameScene::switchRound(int playerID)
{
    prevPlayerRound = playerRound;
    playerRound = playerID;
    
    if(prevPlayerRound != playerRound)
    {
        auxUpdateHealthBar();
        auxUpdateManaBar();
        auxUpdatePlayerItensSlots();
    }
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
        
        if(isTurnHappening())
            return;
        
        
        if (initialTouchPos[0] - currentTouchPos[0] > varScreenSize.width * 0.05)
        {
            CCLOG("SWIPED LEFT");
            isTouchDown = false;
            
            gameController->doPlayerAction(playerRound, LEFT);
        }
        else if (initialTouchPos[0] - currentTouchPos[0] < - varScreenSize.width * 0.05)
        {
            CCLOG("SWIPED RIGHT");
            isTouchDown = false;
            
            gameController->doPlayerAction(playerRound, RIGHT);
            
        }
        else if (initialTouchPos[1] - currentTouchPos[1] > varScreenSize.width * 0.05)
        {
            CCLOG("SWIPED DOWN");
            isTouchDown = false;
            
            gameController->doPlayerAction(playerRound, DOWN);
            
        }
        else if (initialTouchPos[1] - currentTouchPos[1] < - varScreenSize.width * 0.05)
        {
            CCLOG("SWIPED UP");
            isTouchDown = false;
            
            gameController->doPlayerAction(playerRound, UP);
            
        }
    }
}

void RAGameScene::useItemSlotButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    int slot = (int) pSender->_ID;
    if(isTurnHappening())
        return;
        
    switch(type)
    {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            gameController->doPlayerUseItem(playerRound, slot);
            break;
        default:
            break;
    }
}

void RAGameScene::passTurnButtonCallback(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    switch (type)
    {
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            if(!isTurnHappening())
            {
                gameController->playerPassTurn(playerRound);
            }
        default:
            break;
    }
}

bool RAGameScene::isTurnHappening()
{
    if(player1Node != nullptr)
    {
        if(player1Node->node->getActionByTag(MOVE_ACTION_TAG) != nullptr)
            return true;
        if(player1Node->pSprite->getActionByTag(ATK_ACTION_TAG) != nullptr)
            return true;
    }
    if(player2Node != nullptr)
    {
        if(player2Node->node->getActionByTag(MOVE_ACTION_TAG) != nullptr)
            return true;
        if(player2Node->pSprite->getActionByTag(ATK_ACTION_TAG) != nullptr)
            return true;
    }
    for (auto cr : varCreaturesMap)
    {
        auto creatureSprite = cr.second->cSprite;
        if( creatureSprite->getActionByTag(MOVE_ACTION_TAG) != nullptr)
            return true;
        if(creatureSprite->getActionByTag(ATK_ACTION_TAG) != nullptr)
            return true;
    }
    
        return false;
}
