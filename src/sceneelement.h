#ifndef SCENEELEMENT_H
#define SCENEELEMENT_H

#include <glm.hpp>
#include "scene.h"

class SceneElement
{
public:
    SceneElement(ScenePtr scene);
    virtual void update() = 0;
    virtual void draw() = 0;

    virtual ~SceneElement() = default;


    float getScale() const;
    void setScale(float value);

    glm::vec2 getPos() const;
    void setPos(const glm::vec2 &value);

    float getRotation() const;
    void setRotation(float value);

protected:
    void pushMatrix();

    void popMatrix();
    ScenePtr scene;
    glm::vec2 pos = {0,0};
    float scale = 1.0;
    float rotation = 0;
};

#endif // SCENEELEMENT_H
