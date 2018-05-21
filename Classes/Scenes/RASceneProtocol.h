//
//  RASceneProtocol.h
//  Radius
//
//  Created by Thiago De Angelis on 21/05/2018.
//

#ifndef RASceneProtocol_h
#define RASceneProtocol_h
#include "RAMap.hpp"

class RASceneProtocol
{
public:
    virtual void renderMap (RAMap* map) {}
};

#endif /* RASceneProtocol_h */
