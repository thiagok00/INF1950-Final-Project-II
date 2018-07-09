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
    ItemID id;
    RAItem(ItemID id, int charges);
    
public:
    int getCharges();
    ItemID getItemID();
    virtual ~RAItem() {}
};
#endif /* RAItem_hpp */
