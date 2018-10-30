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
    virtual void update();
    virtual void draw();

    ofColor getColor() const;
    void setColor(const ofColor &value);

    ofRectangle getBBox() const {
        return font->getStringBoundingBox(text,0,0);
    }

private:
    std::shared_ptr<ofTrueTypeFont> font;
    std::string text;
    ofColor color;
    uint64_t startTime, elapsedTime;
};

#endif // ANIMATEDTEXT_H
