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
    void loadPlayer (RAPlayer *player);
    void playerMoved (RAPlayer* player, RATile * tile);
    void playerAttackedCreature (RAPlayer* player, RACreature *creature, int damage, bool died);
    void creatureMoved(RACreature *creature, int row, int col);
    void creatureAttackedPlayer(RACreature *creature, RAPlayer * player, int damage);


    std::vector<cocos2d::Sprite*> mapSprites;
    
    cocos2d::LayerColor *varBackLayer;
    cocos2d::Size varScreenSize;
    
    //touch events
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
    
    bool isTouchDown;
    
    float initialTouchPos[2];
    float currentTouchPos[2];
    
    void update(float dt);

    // implement the "static create()" method manually
    //CREATE_FUNC(RAGameScene);
    
    struct PlayerNode
    {
        RAPlayer* pController;
        cocos2d::Sprite* pSprite;
    };
    
    PlayerNode player1Node;
    PlayerNode player2Node;
    
    struct CreatureNode
    {
        RACreature* cController;
        cocos2d::Sprite* cSprite;
    };
    
    CreatureNode creatureExample;
    
};

#endif // __RAGameScene_SCENE_H__
