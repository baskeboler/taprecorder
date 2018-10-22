#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include "ofMain.h"
#include "ofxATK.hpp"
#include "scene.h"
#include <memory>


#define TAP_THRESHOLD 125

class SoundManager
{
public:

    SoundManager(ScenePtr scene);

    void init();

    void update();

    void tap();

    void audioOut(ofSoundBuffer& buf);

    ~SoundManager();
private:
    uint64_t last_tap= 0;
    std::mutex env_mutex;
    std::shared_ptr<CTEnvelope> envelope;
    std::shared_ptr<WTSawtooth> wave;
    std::shared_ptr<SmoothValue> frequency;

    ScenePtr scene;

    bool playing = false;
    uint64_t play_start=0;
};


#endif // SOUNDMANAGER_H
