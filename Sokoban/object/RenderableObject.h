//
// Created by zsyfz on 25-5-28.
//

#ifndef RENDERABLEOBJECT_H
#define RENDERABLEOBJECT_H

#include "../point.h"
#include <string>

class RenderableObject
{
public:
    // virtual RenderableObject(const RenderableObject &other) = delete;
    virtual Position get_position() const = 0;
    virtual char get_icon() const = 0;
    virtual ~RenderableObject() = default;
};



#endif //RENDERABLEOBJECT_H
