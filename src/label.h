#ifndef LABEL_H
#define LABEL_H

#include "sceneelement.h"

class Label: public SceneElement
{
public:
    Label(ScenePtr scene);
    Label(ScenePtr scene, std::string text);

    virtual void update();
    virtual void draw();

    ofColor getColor() const;
    void setColor(const ofColor &value);

    unsigned int getFontSize() const;
    void setFontSize(unsigned int value);

    virtual ~Label()=default;
private:
    std::string text;
    std::string fontName = "verdana";
    ofColor color = ofColor::black;
    unsigned int fontSize = 12;
};

#endif // LABEL_H
