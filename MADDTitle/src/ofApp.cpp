#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(60);
	ofBackground(0);

	gui.setup();
	gui.add(particleSize.setup("Particle Size", 1500, 0, 80000));
	gui.add(div.setup("div", 200, 10, 1000));
	gui.add(friction.setup("friction", 0.99, 0.95, 1.0));
	gui.add(speed.setup("speed", 0.05, 0.0, 100.0));
	gui.loadFromFile("settings.xml");

	mode = 0;
	brightness = 0;
	showGui = false;
	ofHideCursor();
	cam.setDistance(3400);

	ofToggleFullscreen();
	ofSetWindowPosition(0, 0);
	ofSetWindowShape(1920 * 2, 1080 * 2);
	gui.setPosition(40, 140);

	initParticle();
}

//--------------------------------------------------------------
void ofApp::update() {
	if (mode == 0) {
		for (int i = 0; i < NUM_BILLBOARDS; i++) {
			billboards.getColors()[i].set(brightness);
		}
		brightness += 0.01;
		if (brightness > 2.0) {
			mode = 1;
		}
	}
	else if (mode == 1) {
		float t = (ofGetElapsedTimef()) * 10.0;
		for (int i = 0; i < NUM_BILLBOARDS; i++) {
			ofVec3f vec(ofSignedNoise(t, billboards.getVertex(i).y / div, billboards.getVertex(i).z / div),
				ofSignedNoise(billboards.getVertex(i).x / div, t, billboards.getVertex(i).z / div),
				ofSignedNoise(billboards.getVertex(i).x / div, billboards.getVertex(i).y / div, t));
			vec *= speed * ofGetLastFrameTime();
			billboardVels[i] += vec;
			billboards.getVertices()[i] += billboardVels[i];
			billboardVels[i] *= friction;
			billboards.getColors()[i].set(brightness);
		}
		brightness -= 0.003;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	cam.begin();
	if (mode == 0) {
		ofSetColor(brightness * 255);
		img.draw(-img.getWidth() / 2, -img.getHeight() / 2);
	}
	else {
		ofPushMatrix();
		ofRotateXDeg(-180);
		static GLfloat distance[] = { 0.0, 0.0, 1.0 };
		glPointParameterfv(GL_POINT_DISTANCE_ATTENUATION, distance);
		glPointSize(particleSize);
		billboards.draw();
		//ofDisableBlendMode();
		ofPopMatrix();
	}
	cam.end();

	if (showGui) {
		ofSetColor(255);
		gui.draw();
		ofDrawBitmapString(ofToString(ofGetFrameRate()), 40, 100);
	}
}

void ofApp::initParticle() {
	mode = 0;
	brightness = 0;

	billboards.getVertices().resize(NUM_BILLBOARDS);
	billboards.getColors().resize(NUM_BILLBOARDS);
	billboards.getNormals().resize(NUM_BILLBOARDS, ofVec3f(0));
	billboards.setMode(OF_PRIMITIVE_POINTS);
	ofDisableBlendMode();

	img.loadImage("logo.png");

	for (int i = 0; i < NUM_BILLBOARDS; i++) {
		while (1) {
			glm::vec3 pos = glm::vec3(ofRandom(img.getWidth()), ofRandom(img.getHeight()), 0);
			ofColor col = img.getColor(pos.x, pos.y);
			if (col.getBrightness() > 200) {
				billboardVels[i].set(ofRandomf(), ofRandomf(), ofRandomf() * 6);
				billboards.getVertices()[i] = { pos.x - img.getWidth() / 2, pos.y - img.getHeight() / 2, 0 };
				billboards.getColors()[i].set(0);
				//billboards.getColors()[i].set(ofColor::fromHsb(ofRandom(80, 160), 180, 255));
				break;
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'r') {
		initParticle();
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
