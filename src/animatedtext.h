#ifndef ANIMATEDTEXT_H
#define ANIMATEDTEXT_H

#include "sceneelement.h"
class AnimatedText: public SceneElement
{
public:
    AnimatedText(ScenePtr scene);
    AnimatedText(ScenePtr scene,std::string text);

    virtual ~AnimatedText()=default;
    // SceneElement interface
public:
    void update();
    void draw();

    glm::vec2 getPos() const;
    void setPos(const glm::vec2 &value);

    ofColor getColor() const;
    void setColor(const ofColor &value);

    ofRectangle getBBox() const {
        return font->getStringBoundingBox(text,0,0);
    }
private:
    std::shared_ptr<ofTrueTypeFont> font;
    std::string text;
//    std::vector<ofPath> paths;
    glm::vec2 pos;
    ofColor color;
    uint64_t startTime, elapsedTime;
};

#endif // ANIMATEDTEXT_H
