//
//  TileModel.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 25/04/2018.
//

#ifndef TileModel_hpp
#define TileModel_hpp

#include <stdio.h>

class TileModel
{
public:
    
    TileModel(int row,int col, bool walkable);
    ~TileModel();
    
    int getRow();
    int getCol();
    bool isWakable();
    const char * getDescription();
    
protected:
    int row;
    int col;
    bool walkable;
};

#endif /* TileModel_hpp */
