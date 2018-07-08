//
//  RAItem.cpp
//  Radius-mobile
//
//  Created by Thiago De Angelis on 06/07/2018.
//

#include "RAItem.hpp"


RAItem::RAItem(ItemID id, int charge)
{
    this->id = id;
    this->charges = charge;
}


int RAItem::getCharges()
{
    return this->charges;
}

ItemID RAItem::getItemID()
{
    return this->id;
}

