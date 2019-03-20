#include "ofApp.h"

void ofApp::setup() {
	//基本設定
	ofSetFrameRate(60);
	ofSetVerticalSync(true);
	ofBackground(0);
	ofToggleFullscreen();	

	//GUIの初期化
	gui.setup();
	gui.add(physicalFocus.setup("Physical Focus Distance", 200, 0, 600));
	gui.add(focusDistance.setup("Focus Distance", 800, 0, 2000));
	gui.add(eyeSeparation.setup("Eye Separation", 5, 0, 20));
	gui.loadFromFile("settings.xml");
	
	//ステレオカメラの初期化
	cam.setup(ofGetWidth(), ofGetHeight());
	cam.setScale(1, -1, 1);
	cam.setViewMode(ofxStereoCameraViewMode::TOE_IN);
	cam.setPhysicalEyeSeparation(4.0);
}

void ofApp::update() {
	//ステレオカメラの更新
	cam.setPhysicalFocusDistance(physicalFocus);
	cam.setFocusDistance(focusDistance);
	cam.setPhysicalEyeSeparation(eyeSeparation);
	cam.update();
	
	//左目映像レンダリング
	cam.beginLeft();
	drawScene();
	cam.endLeft();
	
	//右目映像レンダリング
	cam.beginRight();
	drawScene();
	cam.endRight();
}

void ofApp::drawScene() {
	//3Dシーンの生成
	ofBoxPrimitive box;
	box.set(400);
	box.setResolution(1);
	ofSetLineWidth(4.0);
	box.drawWireframe();
}

//--------------------------------------------------------------
void ofApp::draw() {
	//最終出力
	cam.draw(0, 0, ofGetWidth(), ofGetHeight());
	
	//GUI表示
	gui.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	//モードの切り替え
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