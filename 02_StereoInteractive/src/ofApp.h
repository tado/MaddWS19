#pragma once

#include "ofMain.h"
#include "ParticleVec3.h"
#include "ofxStereoCamera.h"
#include "ofxGui.h"

class ofApp : public ofBaseApp {
public:
	
	void setup();
	void update();
	void draw();
	void drawScene();
	void keyPressed(int key);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	
	ofxPanel gui;
	ofxFloatSlider physicalFocus;
	ofxFloatSlider focusDistance;
	ofxFloatSlider eyeSeparation;
	ofxFloatSlider particleSize;
	ofxStereoCamera cam;

	static const int num = 80000;
	ParticleVec3 particles[num];
	ofVboMesh mesh;
	bool pressed;
};