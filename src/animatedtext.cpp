#include "animatedtext.h"
#include "fontmanager.h"
#include "ofxEasing.h"

AnimatedText::AnimatedText(ScenePtr scene): SceneElement(scene)
{

}

AnimatedText::AnimatedText(ScenePtr scene, string text): SceneElement (scene), text{text}
{
    font = FontManager::get_instance()->getFont("verdana", 32);

//    paths = f->getStringAsPoints(text);
    startTime = ofGetCurrentTime().getAsMilliseconds();
}

void AnimatedText::update()
{
   auto now = ofGetCurrentTime().getAsMilliseconds();
   elapsedTime = now - startTime;
}

void AnimatedText::draw()
{
//    auto f = FontManager::get_instance()->getFont("verdana", 32);
    ofPushMatrix();
    ofTranslate(pos);
    ofScale(scale);
    int i = 0;
    ofSetColor(color);
    auto bb = font->getStringBoundingBox(text,0,0);
    font->drawString(text, -bb.width/2 , -bb.height/2);
//    for (auto c: text) {
//        auto val = sin(0.001*elapsedTime + i++);
//        auto delta = ofxeasing::map_clamp(val, -1,1, -20, 20, ofxeasing::linear::easeInOut);
//        ofPushMatrix();
//        ofTranslate(pos + glm::vec2{0, delta});
////        p.setColor(color);
////        p.draw();
//        font->drawString(std::string() + (char)c, font->getSize()*i, 0);
//        ofPopMatrix();
//    }
    ofPopMatrix();
}


ofColor AnimatedText::getColor() const
{
    return color;
}

void AnimatedText::setColor(const ofColor &value)
{
    color = value;
}

