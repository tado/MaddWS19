#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	//ofSetVerticalSync(true);
	ofBackground(0);

	gui.setup();
	gui.add(particleSize.setup("Particle Size", 1500, 0, 10000));
	gui.add(div.setup("div", 200, 10, 1000));
	gui.add(friction.setup("friction", 0.99, 0.95, 1.0));
	gui.add(speed.setup("speed", 0.05, 0.0, 100.0));
	gui.loadFromFile("settings.xml");

	showGui = false;
	ofHideCursor();
	cam.setDistance(800);

	billboards.getVertices().resize(NUM_BILLBOARDS);
	billboards.getColors().resize(NUM_BILLBOARDS);
	billboards.getNormals().resize(NUM_BILLBOARDS, ofVec3f(0));

	float range = 100;
	for (int i = 0; i < NUM_BILLBOARDS; i++) {
		billboardVels[i].set(ofRandomf(), -1.0, ofRandomf());
		billboards.getVertices()[i] = { ofRandom(-range, range),ofRandom(-range, range),ofRandom(-range, range) };
		//billboards.getColors()[i].set(ofColor::fromHsb(ofRandom(80, 160), 180, 255));
		billboards.getColors()[i].set(255);
	}

	billboards.setUsage(GL_DYNAMIC_DRAW);
	billboards.setMode(OF_PRIMITIVE_POINTS);
	ofDisableBlendMode();

	ofToggleFullscreen();
	ofSetWindowPosition(0, 0);
	ofSetWindowShape(1920 * 2, 1080 * 2);
	gui.setPosition(40, 40);
}

//--------------------------------------------------------------
void ofApp::update() {
	float t = (ofGetElapsedTimef()) * 10.0;
	//float div = 200.0;
	for (int i = 0; i < NUM_BILLBOARDS; i++) {
		ofVec3f vec(ofSignedNoise(t, billboards.getVertex(i).y / div, billboards.getVertex(i).z / div),
			ofSignedNoise(billboards.getVertex(i).x / div, t, billboards.getVertex(i).z / div),
			ofSignedNoise(billboards.getVertex(i).x / div, billboards.getVertex(i).y / div, t));
		vec *= speed * ofGetLastFrameTime();
		billboardVels[i] += vec;
		billboards.getVertices()[i] += billboardVels[i];
		billboardVels[i] *= friction;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	cam.begin();
	ofSetColor(255);
	ofPushMatrix();
	ofRotateXDeg(ofGetElapsedTimef()*5.0);
	//ofRotateYDeg(ofGetElapsedTimef()*7.0);
	ofRotateZDeg(ofGetElapsedTimef()*9.0);

	//ofEnableBlendMode(OF_BLENDMODE_ADD);
	static GLfloat distance[] = { 0.0, 0.0, 1.0 };
	glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
	glPointSize(particleSize);
	billboards.draw();
	//ofDisableBlendMode();
	ofPopMatrix();
	cam.end();

	if (showGui) {
		gui.draw();
		ofDrawBitmapString(ofToString(ofGetFrameRate()), 20, 200);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'r') {
		float range = 100;
		for (int i = 0; i < NUM_BILLBOARDS; i++) {
			billboardVels[i].set(ofRandomf(), -1.0, ofRandomf());
			billboards.getVertices()[i] = { ofRandom(-range, range),ofRandom(-range, range),ofRandom(-range, range) };
		}
	}
	else if (key == 'g') {
		if (showGui == true) {
			showGui = false;
			ofHideCursor();
		}
		else {
			showGui = true;
			ofShowCursor();
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}
