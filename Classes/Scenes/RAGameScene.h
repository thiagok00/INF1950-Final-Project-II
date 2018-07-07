#ifndef __RAGameScene_SCENE_H__
#define __RAGameScene_SCENE_H__

#include "cocos2d.h"

#include "RAUtil.h"
#include "RASceneProtocol.h"

//Game Controllers
#include "RAGameController.hpp"
#include "RASinglePlayerGameController.hpp"
#include "ui/CocosGUI.h"


class RAGameScene : public cocos2d::Scene, public RASceneProtocol
{
protected:
    //HUD
    cocos2d::Label *varExperienceLabel;
    void auxUpdateExperienceLabelText(int experiencePoints);
    
    cocos2d::Size healthBarBaseSize;
    cocos2d::LayerColor *healthBarBase;
    cocos2d::LayerColor *healthBar;

    
    //0.0 to 1.0
    void auxUpdateHealthBar(float healthPercentage);
    
    cocos2d::Label* auxCreateDamageLabel(int damage, cocos2d::Color4B textColor, cocos2d::Vec2 pos);
    
    cocos2d::Size tileSize;
public:
    static cocos2d::Scene* createScene(int gameMode);

    virtual bool init(int gameMode);
    
    RAGameController *gameController;
    
    /* RASceneProtocol Methods */
    void renderMap (RAMap* map);
    void loadPlayer (RAPlayer *player);
    void playerMoved (RAPlayer* player, RATile * tile);
    void playerMovedAndCaughtItem (RAPlayer* player, RATile * tile, RAItem *item);
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
    
    //itens slots
    cocos2d::ui::Button *varItemSlot1Button;
    cocos2d::ui::Button *varItemSlot2Button;
    cocos2d::ui::Button *varItemSlot3Button;
    cocos2d::ui::Button *varItemSlot4Button;
    cocos2d::ui::Button *varItemSlot5Button;
    cocos2d::ui::Button *varItemSlot6Button;
    
    void useItemSlotButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    
    
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
    
    struct ItemNode
    {
        RAItem *iController;
        cocos2d::LayerColor* iSprite;
    };
    
    ItemNode itemExample;
};

#endif // __RAGameScene_SCENE_H__
