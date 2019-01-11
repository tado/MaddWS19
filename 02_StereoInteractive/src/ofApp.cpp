#include "ofApp.h"

void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);
	
	ofToggleFullscreen();	

	gui.setup();
	gui.add(physicalFocus.setup("Physical Focus Distance", 200, 0, 600));
	gui.add(focusDistance.setup("Focus Distance", 500, 0, 1000));
	gui.add(eyeSeparation.setup("Eye Separation", 5, 0, 20));
	gui.add(particleSize.setup("particleSize", 1000, 0, 10000));
	gui.loadFromFile("settings.xml");
	
	cam.setup(ofGetWidth(), ofGetHeight());
	cam.setScale(1, 1, 1);
	cam.setViewMode(ofxStereoCameraViewMode::PARALLEL);
	//cam.setOutputMode(ofxStereoCameraOutputMode::CROSS_EYED);
	cam.setPhysicalEyeSeparation(4.0);
	cam.disableMouseInput();
	cam.setDistance(1000);

	mesh.setMode(OF_PRIMITIVE_POINTS);
	pressed = false;
	for (int i = 0; i < num; i++) {
		particles[i].minx = -ofGetWidth() / 2;
		particles[i].miny = -ofGetHeight() / 2;
		particles[i].minz = -ofGetWidth() / 2;
		particles[i].maxx = ofGetWidth() / 2;
		particles[i].maxy = ofGetHeight() / 2;
		particles[i].maxz = ofGetWidth()/2;
		particles[i].position = ofVec3f(
			ofRandom(-ofGetWidth()/4, ofGetWidth()/4), 
			ofRandom(-ofGetHeight()/4, ofGetHeight()/4), 
			ofRandom(-ofGetWidth()/2, ofGetWidth()/2));
	}
}

void ofApp::update() {
	mesh.clear();
	for (int i = 0; i < num; i++) {
		if (pressed) {
			particles[i].addAttractionForce(mouseX - ofGetWidth()/2, mouseY - ofGetHeight() /2, 0, ofGetWidth() * 2, 1.0);
		}
		particles[i].update();
		particles[i].throughOffWalls();
		mesh.addVertex(ofVec3f(particles[i].position.x, particles[i].position.y, particles[i].position.z));
	}

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
	ofSetColor(255);
	ofEnableBlendMode(OF_BLENDMODE_ADD);
	static GLfloat distance[] = { 0.0, 0.0, 1.0 };
	glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
	glPointSize(particleSize);
	mesh.draw();
	ofDisableBlendMode();
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
	else if (key == 'r') {
		for (int i = 0; i < num; i++) {
			particles[i].minx = -ofGetWidth() / 2;
			particles[i].miny = -ofGetHeight() / 2;
			particles[i].minz = -ofGetWidth() / 2;
			particles[i].maxx = ofGetWidth() / 2;
			particles[i].maxy = ofGetHeight() / 2;
			particles[i].maxz = ofGetWidth() / 2;
			particles[i].position = ofVec3f(
				ofRandom(-ofGetWidth() / 4, ofGetWidth() / 4),
				ofRandom(-ofGetHeight() / 4, ofGetHeight() / 4),
				ofRandom(-ofGetWidth() / 2, ofGetWidth() / 2));
		}
	}
}

void ofApp::mousePressed(int x, int y, int button) {
	pressed = true;
}

void ofApp::mouseReleased(int x, int y, int button) {
	pressed = false;
}