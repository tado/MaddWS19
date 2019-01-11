#include "ofApp.h"

void ofApp::setup() {
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);
	
	ofToggleFullscreen();	

	gui.setup();
	gui.add(physicalFocus.setup("Physical Focus Distance", 200, 0, 600));
	gui.add(focusDistance.setup("Focus Distance", 200, 0, 600));
	gui.add(eyeSeparation.setup("Eye Separation", 5, 0, 20));
	gui.loadFromFile("settings.xml");
	
	cam.setup(ofGetWidth(), ofGetHeight());
	cam.setScale(1, -1, 1);
	cam.setViewMode(ofxStereoCameraViewMode::PARALLEL);
	cam.setOutputMode(ofxStereoCameraOutputMode::CROSS_EYED);
	cam.setPhysicalEyeSeparation(4.0);
}

void ofApp::update() {
	cam.setPhysicalFocusDistance(physicalFocus);
	cam.setFocusDistance(focusDistance);
	cam.setPhysicalEyeSeparation(eyeSeparation);
	
	cam.update();
	
	cam.beginLeft();
	drawScene();
	cam.endLeft();
	
	cam.beginRight();
	drawScene();
	cam.endRight();
}

void ofApp::drawScene() {
	ofBoxPrimitive box;
	box.set(400);
	box.setResolution(1);
	ofSetLineWidth(4.0);
	box.drawWireframe();
}

//--------------------------------------------------------------
void ofApp::draw() {
	cam.draw(0, 0, ofGetWidth(), ofGetHeight());
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == '1') {
		cam.setOutputMode(ofxStereoCameraOutputMode::LINE_BY_LINE);
	}
	else if (key == '2') {
		cam.setOutputMode(ofxStereoCameraOutputMode::SUTTER);
	}
	else if (key == '3') {
		cam.setOutputMode(ofxStereoCameraOutputMode::ANAGLYPH);
	}
	else if (key == '4') {
		cam.setOutputMode(ofxStereoCameraOutputMode::CROSS_EYED);
	}
	else if (key == 'q')	{
		cam.setViewMode(ofxStereoCameraViewMode::PARALLEL);
	}
	else if (key == 'w'){
		cam.setViewMode(ofxStereoCameraViewMode::TOE_IN);
	}
}