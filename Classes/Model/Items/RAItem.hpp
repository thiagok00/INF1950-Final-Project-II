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
    ItemID itemType;
    RAItem(ItemID itemType, int charges);
    
public:
    int getCharges();
    ItemID getItemType();
    virtual ~RAItem() {}
};
#endif /* RAItem_hpp */
