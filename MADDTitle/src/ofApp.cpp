#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	//ofSetVerticalSync(true);
	ofBackground(0);

	gui.setup();
	gui.add(particleSize.setup("Particle Size", 1500, 0, 10000));
	gui.add(div.setup("div", 200, 10, 1000));
	gui.add(friction.setup("friction", 0.8, 0.5, 1.0));
	gui.add(speed.setup("speed", 0.05, 0.0, 1.0));
	gui.loadFromFile("settings.xml");

	showGui = false;
	ofHideCursor();

	//cam.setup(ofGetWidth(), ofGetHeight());
	//cam.setScale(1, -1, 1);
	//cam.setViewMode(ofxStereoCameraViewMode::PARALLEL);
	//cam.setOutputMode(ofxStereoCameraOutputMode::CROSS_EYED);
	//cam.setPhysicalEyeSeparation(4.0);
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

	ofToggleFullscreen();
	ofSetWindowPosition(0, 0);
	ofSetWindowShape(1920 * 2, 1080 * 2);
	gui.setPosition(40, 40);
}

//--------------------------------------------------------------
void ofApp::update() {
	float t = (ofGetElapsedTimef()) * speed;
	//float div = 200.0;
	for (int i = 0; i < NUM_BILLBOARDS; i++) {
		ofVec3f vec(ofSignedNoise(t, billboards.getVertex(i).y / div, billboards.getVertex(i).z / div),
			ofSignedNoise(billboards.getVertex(i).x / div, t, billboards.getVertex(i).z / div),
			ofSignedNoise(billboards.getVertex(i).x / div, billboards.getVertex(i).y / div, t));
		vec *= 10.0 * ofGetLastFrameTime();
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
	ofRotateYDeg(ofGetElapsedTimef()*4.0);

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
