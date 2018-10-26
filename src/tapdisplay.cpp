#include "tapdisplay.h"
#include "tapdisplaystate.h"
#include "fontmanager.h"

TapDisplay::TapDisplay(ScenePtr scene): SceneElement{scene} {

    ofAddListener(TapRecorderEvent::START_PLAYER, this, &TapDisplay::onPlayerStart);
    ofAddListener(TapRecorderEvent::PAUSE_PLAYER, this, &TapDisplay::onPlayerPause);
    ofAddListener(TapRecorderEvent::RESET_PLAYER, this, &TapDisplay::onPlayerReset);

}

void TapDisplay::init() {
    state = std::make_shared<TapDisplayInitState>(shared_from_this());

}

TapDisplay::~TapDisplay() {
    ofRemoveListener(TapRecorderEvent::START_PLAYER, this, &TapDisplay::onPlayerStart);
    ofRemoveListener(TapRecorderEvent::PAUSE_PLAYER, this, &TapDisplay::onPlayerPause);
    ofRemoveListener(TapRecorderEvent::RESET_PLAYER, this, &TapDisplay::onPlayerReset);

}

void TapDisplay::update() {
    state= state->update();
}

void TapDisplay::draw() {
    auto f = FontManager::get_instance()->getFont("verdana", 9);
    auto f2 = FontManager::get_instance()->getFont("verdana", 12);
    auto rightLabelBB = f->getStringBoundingBox(rightLabel, 0,0);
    auto statusBB = f->getStringBoundingBox(statusLabel, 0,0);
    ofPushMatrix();
    ofTranslate(position);

    ofSetColor(ofColor::yellow);
    ofDrawLine({0,0}, {size.x, 0});
    f->drawString(leftLabel, 0, -15);
    f->drawString(rightLabel, size.x - rightLabelBB.getWidth(), -15 );

    for (auto t: getTaps()) {
        auto tap_x = ofMap(t, 0, 0.001*timeElapsed, 0, size.x);

        ofDrawTriangle({tap_x, 0}, {tap_x - 5, 70}, {tap_x + 5, 70});
    }
    f2->drawString(statusLabel, size.x/2 - statusBB.getWidth()/2, -18);
    ofPopMatrix();
}

glm::vec2 TapDisplay::getSize() const
{
    return size;
}

void TapDisplay::setSize(const glm::vec2 &value)
{
    size = value;
}

glm::vec2 TapDisplay::getPosition() const
{
    return position;
}

void TapDisplay::setPosition(const glm::vec2 &value)
{
    position = value;
}

std::vector<double> TapDisplay::getTaps() const{
    return scene->getTaps();
}

std::string TapDisplay::getStatusLabel() const
{
    return statusLabel;
}

void TapDisplay::setStatusLabel(const std::string &value)
{
    statusLabel = value;
}

uint64_t TapDisplay::getTimeElapsed() const
{
    return timeElapsed;
}

void TapDisplay::setTimeElapsed(const uint64_t &value)
{
    timeElapsed = value;
}

uint64_t TapDisplay::getTimeRecordingStop() const
{
    return timeRecordingStop;
}

void TapDisplay::setTimeRecordingStop(const uint64_t &value)
{
    timeRecordingStop = value;
}

uint64_t TapDisplay::getTimeRecordingStart() const
{
    return timeRecordingStart;
}

void TapDisplay::setTimeRecordingStart(const uint64_t &value)
{
    timeRecordingStart = value;
}

uint64_t TapDisplay::getTimePlayerStart() const
{
    return timePlayerStart;
}

void TapDisplay::setTimePlayerStart(const uint64_t &value)
{
    timePlayerStart = value;
}

std::string TapDisplay::getLeftLabel() const
{
    return leftLabel;
}

void TapDisplay::setLeftLabel(const std::string &value)
{
    leftLabel = value;
}

std::string TapDisplay::getRightLabel() const
{
    return rightLabel;
}

void TapDisplay::setRightLabel(const std::string &value)
{
    rightLabel = value;
}
