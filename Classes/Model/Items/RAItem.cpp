//
//  RAItem.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 06/07/2018.
//

#include "RAItem.hpp"


RAItem::RAItem(ItemID itemType, int charge)
{
    this->itemType = itemType;
    this->charges = charge;
}


int RAItem::getCharges()
{
    return this->charges;
}

ItemID RAItem::getItemType()
{
    return this->itemType;
}

