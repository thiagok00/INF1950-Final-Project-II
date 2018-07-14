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
public:
   
    struct ItemNode
    {
        ItemID itemType;
        int charges;
        cocos2d::LayerColor* iSprite;
    };
    
    struct InventaryItemNode
    {
        ItemID itemType;
        int slot;
        int charges;
        cocos2d::Sprite* iSprite;
    };
    
    
    struct CreatureNode
    {
        int creatureID;
        bool isDead;
        cocos2d::Sprite* cSprite;
        cocos2d::Size size;
    };

    struct PlayerNode
    {
        RAPlayer* pController;
        cocos2d::Sprite* pSprite;
        std::vector<InventaryItemNode*> items;
        int occupiedSlots = 0;
        int maxSlots;
    };
    
    struct TileNode
    {
        int row;
        int col;
        bool walkable;
        CreatureNode * cr;
        cocos2d::Sprite * sprite;
        ItemNode* droppedItem;
    };
    
    struct MapNode
    {
        std::vector<TileNode*> tiles;
    };
    
protected:
    //HUD
    cocos2d::Label *varExperienceLabel;
    void auxUpdateExperienceLabelText(int experiencePoints);
    
    cocos2d::Size healthBarBaseSize;
    cocos2d::LayerColor *healthBarBase;
    cocos2d::LayerColor *healthBar;

    cocos2d::LayerColor *manaBarBase;
    cocos2d::LayerColor *manaBar;
    
    //0.0 to 1.0
    void auxUpdateHealthBar(float healthPercentage);
    void auxUpdateManaBar(float manaPercentage);

    cocos2d::Label* auxCreateDamageLabel(int damage, cocos2d::Color4B textColor, cocos2d::Vec2 pos);

    void auxUpdatePlayerItensSlots();
    
    PlayerNode* auxGetPlayerNodeById(int playerID);
    
    int auxGetTileIndex(int row, int col);
    
    cocos2d::Size tileSize;
public:
    static cocos2d::Scene* createScene(int gameMode);

    virtual bool init(int gameMode);
    
    RAGameController *gameController;
    
    /* RASceneProtocol Methods */
    void loadMap (RAMap* map);
    void loadPlayer (RAPlayer *player);
    void playerMoved (int playerID, int row, int col);
    void playerMovedAndCaughtItem (int playerID, int row, int col,int atSlot, ItemID itemType, int charges);
    void playerAttackedCreature (int playerID, int creatureID, int damage, bool died, int playerExperience);
    void creatureMoved(int creatureID, int row, int col);
    void creatureAttackedPlayer(int creatureID, int playerID, int damage);
    void playerBadStatus(int playerID, Status_ID statusID, int damage);

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
    std::vector<cocos2d::ui::Button*> varItensSlotButtons;
    
    void useItemSlotButton(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    
    
    
    PlayerNode *player1Node;
    PlayerNode *player2Node;
    
    MapNode *mapNode;
    
    std::map<int, CreatureNode*> varCreaturesMap;
};

#endif // __RAGameScene_SCENE_H__
