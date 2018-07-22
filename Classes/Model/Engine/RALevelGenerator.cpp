//
//  RALevelGenerator.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#include "RALevelGenerator.hpp"
#include "RACreature.hpp"
#include "RASelfUseItem.hpp"

RAMap* RALevelGenerator::generateLevel(int difficulty)
{
    RAMap *map = new RAMap();

    int i = 0, j = 0;
    
    for (i = 0; i < MAP_MAX_ROW; i++)
    {
        for (j = 0; j < MAP_MAX_COL; j++)
        {
            TileType type = Normal;
            if(i == 4 && j == 2) type = Fire;
            if(i == 7 && j == 5) type = Poison;
            if(i == 6 && j == 6) type = Stairs;
            RATile *tile = new RATile(type, i , j, true);
            tile->entity = nullptr;
            map->setTile(i,j,tile);
        }
    }
    
    RACreature *rat = new RACreature(Rat , 5, 62, 100, 0);
    map->addEntityToTile(rat, MAP_MAX_ROW-1, MAP_MAX_COL-1);
    RACreature *caveRat = new RACreature(Cave_Rat , 5, 6, 100, 0);

    map->addEntityToTile(caveRat, 3, MAP_MAX_COL);

    
    map->player1RespawnTile = map->getTile(1, 1);
    map->player2RespawnTile = map->getTile(1, 2);

    RASelfUseItem * item = RAHealItem::createHealthRune();
    map->addItemToTile(item, 2, 2);
    return map;
}
