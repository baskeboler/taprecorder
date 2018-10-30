#include "sceneelement.h"
#include "ofMain.h"

SceneElement::SceneElement(ScenePtr scene): scene{scene},
pos{0,0}, scale{1.0}, rotation{0}
{

}

float SceneElement::getScale() const
{
    return scale;
}

void SceneElement::setScale(float value)
{
    scale = value;
}

glm::vec2 SceneElement::getPos() const
{
    return pos;
}

void SceneElement::setPos(const glm::vec2 &value)
{
    pos = value;
}

float SceneElement::getRotation() const
{
    return rotation;
}

void SceneElement::setRotation(float value)
{
    rotation = value;
}

void SceneElement::pushMatrix() {

    ofPushMatrix();
    ofTranslate(pos);
    ofRotateDeg(rotation);
    ofScale(scale);
}

void SceneElement::popMatrix() {
    ofPopMatrix();
}
