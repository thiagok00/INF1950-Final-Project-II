//
//  RAItem.hpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 06/07/2018.
//

#ifndef RAItem_hpp
#define RAItem_hpp

#include <stdio.h>
enum ItemID
{
    idItemTarget,
    idItemSelfUse,
    idItemAreaItem
};

class RAItem
{
    
protected:
    int charges;
public:
    RAItem(ItemID id, int charges);
    
    int getCharges();
};
#endif /* RAItem_hpp */
