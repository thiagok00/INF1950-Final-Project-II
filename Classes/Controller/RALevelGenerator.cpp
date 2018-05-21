//
//  RALevelGenerator.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 20/05/2018.
//

#include "RALevelGenerator.hpp"

RAMap* RALevelGenerator::generateLevel(int difficulty)
{
    RAMap *map = new RAMap();

    int i = 0, j = 0;
    
    for (j = 0; j < MAP_MAX_COL; j++)
    {
        for (i = 0; i < MAP_MAX_ROW; i++)
        {
            RATile *tile = new RATile(i,j,true);
            
            map->setTile(i,j,tile);
        }
    }
    
    return map;
}
