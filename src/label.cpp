#include "label.h"
#include "fontmanager.h"

Label::Label(ScenePtr scene): SceneElement{scene} {}

Label::Label(ScenePtr scene, string text): Label(scene)
{
    this->text = text;
}

void Label::update() {}

void Label::draw() {
    auto fm = FontManager::get_instance();
    auto f = fm->getFont(fontName, fontSize);
    auto bb = f->getStringBoundingBox(text,0,0);
    pushMatrix();
    ofSetColor(getColor());
    f->drawString(text, -bb.getWidth()*0.5, bb.getHeight()*0.5);
    popMatrix();
}

ofColor Label::getColor() const
{
    return color;
}

void Label::setColor(const ofColor &value)
{
    color = value;
}

unsigned int Label::getFontSize() const
{
    return fontSize;
}

void Label::setFontSize(unsigned int value)
{
    fontSize = value;
}
