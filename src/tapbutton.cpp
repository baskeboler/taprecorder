#include "tapbutton.h"
#include "scene.h"
#include "buttonstate.h"
#include "fontmanager.h"

TapButton::TapButton(ScenePtr scene):  SceneElement (scene)
{
    label = std::make_shared<Label>(scene, "a button");
    label->setColor(borderColor);
    label->setFontSize(18);
//    size = {100, 48};
    buttonRadius = buttonInitRadius = 200;
    buttonColor = primaryColor = ofColor::red;
    activeColor = ofColor::lightSalmon;
    borderColor = ofColor::darkGoldenRod;
}

void TapButton::initState(){
    state = std::make_shared<InitState>(this->shared_from_this());
}

TapButton::~TapButton(){
}

void TapButton::update() {
    state = state->update();
}

void TapButton::draw() {
    ofSetColor(ofColor::white);
    ofColor border = buttonColor;
    border.invert();
    pushMatrix();
    ofSetColor(border);
    ofDrawCircle(0, 0, buttonRadius * 1.1);
    ofSetColor(buttonColor);
    ofDrawCircle(0, 0, buttonRadius);
    label->setColor(border);
    label->draw();
    popMatrix();
}

bool TapButton::hitTest(const glm::vec2 &p) const {
    return hitTest(p.x, p.y);
}

bool TapButton::hitTest(int x, int y) const {
    return glm::distance({x,y}, getPos()) < buttonRadius;

}
