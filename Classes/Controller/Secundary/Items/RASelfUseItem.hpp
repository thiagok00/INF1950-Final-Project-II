//
//  RASelfUseItem.hpp
//  Radius
//
//  Created by Thiago De Angelis on 06/07/2018.
//

#ifndef RASelfUseItem_hpp
#define RASelfUseItem_hpp

#include <stdio.h>
#include "RAItem.hpp"
#include "RAPlayer.hpp"

class RASelfUseItem : public RAItem
{
public:

    RASelfUseItem(int charges);
    
    virtual void doAction(RAPlayer *owner){};

};

class RAHealItem : public RASelfUseItem
{
public:
    
    RAHealItem(int charges, int heal);
    
    void doAction(RAPlayer *owner);
    
protected:
    int heal;
};


#endif /* RASelfUseItem_hpp */
