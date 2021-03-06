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
            bool walkable = true;
            TileType type = Normal;
            if(i == 4 && j == 2) type = Fire;
            if(i == 7 && j == 5) type = Poison;
            if(i == 6 && j == 6) type = Stairs;
            if (i == 3 && j == 4) {type = Rock;walkable = false;}
            RATile *tile = new RATile(type, i , j, walkable);
            tile->entity = nullptr;
            map->setTile(i,j,tile);
        }
    }
    
    RACreature *greenGhost = RACreature::createCreature(1);
    map->addEntityToTile(greenGhost, MAP_MAX_ROW-1, MAP_MAX_COL-1);
    RACreature *blueGhost = RACreature::createCreature(2);

    map->addEntityToTile(blueGhost, 3, MAP_MAX_COL);

    
    map->player1RespawnTile = map->getTile(1, 1);
    map->player2RespawnTile = map->getTile(1, 2);

    RASelfUseItem * item = RAHealItem::createHealthRune();
    map->addItemToTile(item, 2, 2);
    return map;
}
