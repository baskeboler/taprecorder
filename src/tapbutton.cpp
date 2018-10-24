#include "tapbutton.h"
#include "scene.h"
#include "buttonstate.h"
#include "fontmanager.h"

TapButton::TapButton(ScenePtr scene):  SceneElement (scene)
{
    label = "a button";
    position = {0, 0};
    size = {100, 48};
    buttonRadius = 200;
    buttonColor = primaryColor = ofColor::red;
    activeColor = ofColor::lightSalmon;
    borderColor = ofColor::darkGoldenRod;
//    font.load("verdana.ttf", 14, true, true);
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
    auto f = FontManager::get_instance()->getFont("verdana", 14);
    auto box = f->getStringBoundingBox(label, 0,0);
    ofSetColor(ofColor::white);
    ofColor border = buttonColor;
    border.invert();
    ofPushMatrix();
    ofTranslate(position);
    ofSetColor(border);
    ofDrawCircle(0, 0, buttonRadius * 1.1);
    ofSetColor(buttonColor);
    ofDrawCircle(0, 0, buttonRadius);
    ofSetColor(border);
    f->drawString(label, -box.width * 0.5, -box.height * 0.5);
    ofPopMatrix();
}

bool TapButton::hitTest(const glm::vec2 &pos) const {
    return hitTest(pos.x, pos.y);
}

bool TapButton::hitTest(int x, int y) const {
    return glm::distance({x,y}, position) < buttonRadius;

}
