//
//  RALevelGenerator.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#include "RALevelGenerator.hpp"
#include "RACreature.hpp"

RAMap* RALevelGenerator::generateLevel(int difficulty)
{
    RAMap *map = new RAMap();

    int i = 0, j = 0;
    
    for (i = 0; i < MAP_MAX_ROW; i++)
    {
        for (j = 0; j < MAP_MAX_COL; j++)
        {
            RATile *tile = new RATile(i,j,true);
            tile->creature = nullptr;
            map->setTile(i,j,tile);
        }
    }
    
    RACreature *rat = new RACreature(Rat , 5, 1);
    map->getTile(MAP_MAX_ROW-1, MAP_MAX_COL-1)->creature = rat;
    
    map->player1RespawnTile = map->getTile(1, 1);
    map->player2RespawnTile = map->getTile(1, 2);

    
    return map;
}
