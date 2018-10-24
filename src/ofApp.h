#pragma once

#include "ofMain.h"
#include "ofxDatGui.h"
#include "ofxVectorGraphics.h"
#include "scene.h"
#include "soundmanager.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        void setupGui();
private:
        std::shared_ptr<Scene> scene;
        std::shared_ptr<ofxDatGui> gui;

        std::shared_ptr<SoundManager> soundManager;

        // ofBaseApp interface
public:
        void exit();
};
