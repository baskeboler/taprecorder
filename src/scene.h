#ifndef SCENE_H
#define SCENE_H

#include "ofMain.h"
#include "ofxVectorGraphics.h"
#include <memory>
#include "state.h"
//class State;
#include <glm.hpp>

class Scene: public std::enable_shared_from_this<Scene>
{
public:
    Scene();

    void draw();

    void drawButton();

    void update();

    bool buttonHitTest(int x, int y);

    void onMousePressed(int x, int y);

    void onMouseReleased(int x, int y);

    void init_state();

    void drawTimeLabel();
    double getElapsedTime();
    void startTimer();

    void resetTaps();

    void addTap();
    void onKeyTapped();
    void plotTaps();
    void stopRecording();


    void play();
    void stopPlaying();
private:
    ofColor bg1, bg2, buttonColor;
    double buttonRadius = 100.0;
    ofxVectorGraphics gx;
    ofTrueTypeFont font, titleFont;
    std::shared_ptr<State> state;
    vector<double> taps;
    uint64_t time = 0;
    bool recording = false;
    uint64_t end = 0;

    bool playing = false;
    uint64_t play_start = 0;
    uint64_t play_end = 0;

    friend class State;
    friend class InitState;
    friend class PushedState;

};



#endif // SCENE_H
