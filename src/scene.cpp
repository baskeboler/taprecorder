#include "scene.h"
#include "state.h"

#include "tapbutton.h"
#include "ofxColorPalette.h"
#include <sstream>
#include "fontmanager.h"
#include "taprecorderevent.h"
#include "animatedtext.h"
#include "tweenmanager.h"
#include "tapdisplay.h"
Scene::Scene():
    bg1{ofColor::darkMagenta},
    bg2{ofColor::black}
//    state{nullptr},
//    enable_shared_from_this{},
//    font{},
//    elements{}
{
    ofSetCircleResolution(50);
//    ofTrueTypeFont::setGlobalDpi(72);
   // font.load("verdana.ttf", 14, true, true);


   // titleFont.load("verdana.ttf", 48, true, true);
    startTimer();
}

void Scene::init_state() {
    auto self = this->shared_from_this();
//    state = State::defaultState(self);


    ofxColorPalette::RandomPalette p;
    auto btn = std::make_shared<TapButton>(this->shared_from_this());
    btn->position = 0.5 * ofGetWindowSize();
    btn->buttonRadius = 500;
    btn->buttonColor = *p.nextColor();
    btn->activeColor = *p.nextColor();
    btn->borderColor = *p.nextColor();
    btn->initState();
    elements.push_back(btn);

    auto t = std::make_shared<AnimatedText>(shared_from_this(), "TAP RECORDER");
    auto textX = ofGetWindowWidth()/2 - 0.5*t->getBBox().getWidth();
    t->setPos( glm::vec2{textX, 100.0});
    t->setColor(ofColor::white);
    elements.push_back(t);

    auto builder = TweenManager::getInstance()->newTween();

            builder->withAnimationLength(3000)
            ->withCallback([](){})
            ->withGetter([t](){
                return t->getPos().y;
            })
            ->withSetter([t](float y) {
                auto p = t->getPos();
                p.y = y;
                t->setPos(p);
            })
            ->withToValue(400)
            ->withEasing(ofxeasing::elastic::easeOut)
            ->withYoyo(true)
            ->build();

     auto displ = std::make_shared<TapDisplay>(shared_from_this());
     displ->init();
     auto w_size = ofGetWindowSize();
     auto plot_width = 0.9 * w_size.x;
     auto h_gap = w_size.x * 0.05;
     auto y = w_size.y - 100;

     displ->setPosition({h_gap, y});
     displ->setSize({plot_width, 80});
     elements.push_back(displ);
}
void Scene::startTimer() {
    TapRecorderEvent::getInstance()->startRecording();
    recording = true;
    time = ofGetCurrentTime().getAsMilliseconds();
}

void Scene::resetTaps() {
    taps.clear();

    TapRecorderEvent::getInstance()->resetRecording();
    startTimer();
}

void Scene::addTap() {
    taps.push_back(getElapsedTime());
}
double  Scene::getElapsedTime() {
    uint64_t now = ofGetCurrentTime().getAsMilliseconds();
    return 0.001 * (now - time);
}
void Scene::drawTimeLabel() {
    std::string label;
    if (recording) {
        std::stringstream ss;
        ss << "Time: " << std::fixed << getElapsedTime() << " s";
        label = ss.str();
    } else {
        label = "Not recording";
    }
    auto f = FontManager::get_instance()->getFont("verdana", 14);
    auto b = f->getStringBoundingBox(label, 0, 0);
    f->drawString(label, 16, 16 + b.height);
}

void Scene::draw() {
    ofBackgroundGradient(bg1, bg2);

//    drawButton();
    for (auto &e: elements) {
       e->draw();
    }

    drawTimeLabel();
//    plotTaps();
}


void Scene::update() {
//    state = state->update(State::Event::UPDATE, this->shared_from_this());
    for (auto &e : elements) {
        e->update();
    }
}



void Scene::onMousePressed(int x, int y) {

//    if (buttonHitTest(x, y)) {
//        state = state->update(State::Event::PUSH, this->shared_from_this());
//    }
}

void Scene::onMouseReleased(int x, int y) {

//    state = state->update(State::Event::RELEASE, this->shared_from_this());
}

void Scene::onKeyTapped() {
    if (recording) {
        addTap();
    }
}
void Scene::stopRecording() {
    TapRecorderEvent::getInstance()->pauseRecording();

    end = ofGetCurrentTime().getAsMilliseconds();
    recording = false;

}

void Scene::play() {

    TapRecorderEvent::getInstance()->startPlaying();
    playing= true;
    play_start = ofGetCurrentTime().getAsMilliseconds();
}

void Scene::stopPlaying(){

    TapRecorderEvent::getInstance()->pausePlaying();
    playing=false;
    play_end = ofGetCurrentTime().getAsMilliseconds();
}

void Scene::togglePause() {
    TapRecorderEvent::getInstance()->togglePause();
}

vector<double> Scene::getTaps() const
{
    return taps;
}


void Scene::plotTaps() {
    auto now = ofGetCurrentTime().getAsMilliseconds();
    auto totalTime = getElapsedTime();
    if (!recording) {
        totalTime = 0.001 * (end - time);
    }
    auto w_size = ofGetWindowSize();
    auto plot_width = 0.9 * w_size.x;
    auto screen_height = ofGetWindowHeight();
    vector<double> result;

    std::transform(taps.begin(),taps.end(),std::back_inserter(result), [plot_width, totalTime](double  d) {
        return d / totalTime * plot_width;
    });

    auto h_gap = w_size.x * 0.05;
    auto y = w_size.y - 100;
    gx.setColor(0xffffffff);
    gx.line( h_gap, y, h_gap + plot_width,y);
    std::for_each(result.begin(), result.end(), [y, h_gap, this](double x) {
       gx.line(h_gap + x, y, h_gap+ x, y - 50);
    });

    if (playing) {
        gx.setColor(ofColor::green.getHex());
        auto play_x = (now - play_start) / totalTime;
        gx.line(h_gap + play_x, y, h_gap + play_x, y + 50);
    }
}
