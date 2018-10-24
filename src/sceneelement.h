#ifndef SCENEELEMENT_H
#define SCENEELEMENT_H

#include "scene.h"

class SceneElement
{
public:
    SceneElement(ScenePtr scene): scene{scene} {}
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual ~SceneElement() = default;

    ScenePtr scene;
};

#endif // SCENEELEMENT_H
