#pragma once

#include "ofMain.h"
#include "ofxStereoCamera.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
	
	void setup();
	void update();
	void draw();
	void drawScene();
	void keyPressed(int key);
	
	ofxPanel gui;
	ofxFloatSlider physicalFocus;
	ofxFloatSlider focusDistance;
	ofxFloatSlider eyeSeparation;
	ofxStereoCamera cam;
};