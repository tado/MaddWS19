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
	ofxFloatSlider particleSize;
	ofxFloatSlider div;
	ofxFloatSlider friction;
	ofxFloatSlider speed;
	ofxStereoCamera cam;
	
	static const int NUM_BILLBOARDS = 30000;
	ofVboMesh billboards;
	ofVec3f billboardVels[NUM_BILLBOARDS];
	bool showGui;
};