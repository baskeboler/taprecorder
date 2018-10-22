#include "scene.h"
#include <sstream>
Scene::Scene():
    bg1{ofColor::darkMagenta},
    bg2{ofColor::black},
    buttonColor{ofColor::red},
    state{nullptr},
    enable_shared_from_this{},
    font{}
{
    ofSetCircleResolution(50);
//    ofTrueTypeFont::setGlobalDpi(72);
    font.load("verdana.ttf", 14, true, true);

    titleFont.load("verdana.ttf", 48, true, true);
    startTimer();
}

void Scene::init_state() {
    auto self = this->shared_from_this();
    state = State::defaultState(self);

}
void Scene::startTimer() {
    recording = true;
    time = ofGetCurrentTime().getAsMilliseconds();
}

void Scene::resetTaps() {
    taps.clear();
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
    auto b = font.getStringBoundingBox(label, 0, 0);
    font.drawString(label, 16, 16 + b.height);
}

void Scene::draw() {
    ofBackgroundGradient(bg1, bg2);

    drawButton();
    drawTimeLabel();
    plotTaps();
}

void Scene::drawButton() {
    std::string buttonLabel = "button label";
    std::string title = "tap recorder";
    auto w_size = ofGetWindowSize();
    auto box = font.getStringBoundingBox("button label", 0,0);
    auto titleBox = titleFont.getStringBoundingBox(title, 0, 0);
    ofSetColor(ofColor::white);
    titleFont.drawString(title, w_size.x * 0.5 - titleBox.width * 0.5, 60.0);

    ofPushMatrix();
    ofTranslate(w_size * 0.5);

    gx.setColor(ofColor::white.getHex());
    gx.circle(0, 0, buttonRadius * 1.1);
    gx.setColor(buttonColor.getHex());
    gx.circle(0, 0, buttonRadius);
    ofSetColor(ofColor::white);
    font.drawString(buttonLabel, -box.width * 0.5, -box.height * 0.5);
//    ofDrawBitmapString("Button label", 100, 100);
    ofPopMatrix();
}

void Scene::update() {
    state = state->update(State::Event::UPDATE, this->shared_from_this());
}

bool Scene::buttonHitTest(int x, int y) {
    auto center = ofGetWindowSize() * 0.5;
    auto click_point = glm::vec2{x, y};

    auto dist = glm::length(center - click_point);
    return dist < buttonRadius;
}

void Scene::onMousePressed(int x, int y) {

    if (buttonHitTest(x, y)) {
        state = state->update(State::Event::PUSH, this->shared_from_this());
    }
}

void Scene::onMouseReleased(int x, int y) {

    state = state->update(State::Event::RELEASE, this->shared_from_this());
}

void Scene::onKeyTapped() {
    if (recording) {
        addTap();
    }
}
void Scene::stopRecording() {
    end = ofGetCurrentTime().getAsMilliseconds();
    recording = false;

}

void Scene::play() {
    playing= true;
    play_start = ofGetCurrentTime().getAsMilliseconds();
}

void Scene::stopPlaying(){
    playing=false;
    play_end = ofGetCurrentTime().getAsMilliseconds();
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
