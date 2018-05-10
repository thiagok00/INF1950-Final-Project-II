//
//  MapModel.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 25/04/2018.
//

#ifndef MapModel_hpp
#define MapModel_hpp

#include <stdio.h>
#include "TileModel.hpp"
#define MAP_MAX_ROW 8
#define MAP_MAX_COL 8

class MapModel
{
public:
    MapModel();
    ~MapModel();
    
protected:
    std::vector<TileModel> map;
    
};


#endif /* MapModel_hpp */
