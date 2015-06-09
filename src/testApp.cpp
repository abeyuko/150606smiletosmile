#include "testApp.h"

using namespace ofxCv;
using namespace cv;

void testApp::setup() {
    //画面基本設定
	ofSetVerticalSync(true);
    ofSetFrameRate(60);
    ofBackgroundHex(0x00a8d4);
    
    //カメラを初期化
    cam.setDeviceID(0);
	cam.initGrabber(400, 280);
    //カメラ映像のフェイストラッカーのセットアップ
    tracker.setup();
    // 認識する際の画像をリスケール(小さくするほど高速)
	tracker.setRescale(.5);
    
    //画像ロードしておく
    myImage.loadImage("images/face_title.gif");
    face_newtral.loadMovie("images/face_neutral.gif");
    face_smile.loadMovie("images/face_smile.gif");
    
}

void testApp::update() {
    //カメラ更新
	cam.update();
	if(cam.isFrameNew()) {
		if(tracker.update(toCv(cam))) { //フェイストラッカーの更新
			classifier.classify(tracker);
		}
	}
}

void testApp::draw() {
    ofEnableAlphaBlending();
    //カメラ映像・トラッカー結果を描画
	ofSetColor(255);
	//cam.draw(0, 0);
	//tracker.draw();
    
    if(tracker.getFound())
    {
        myImage.draw(ofGetWidth()/4,ofGetHeight()/15);
        ofSetColor(255,255,255,255);
    }
    else
    {
        myImage.draw(ofGetWidth()/4,ofGetHeight()/15);
        ofSetColor(255,255,255,0);
    }
    
    if(classifier.getPrimaryExpression())
    {
        //ofBackground(248, 248, 48); //pink
        face_smile.draw(ofGetWidth()/4,ofGetHeight()/15);
        //ofTranslate(ofGetWidth()/2, 0);
        face_smile.play();
        face_smile.update();
        face_smile.stop();
    }
    else
    {
        //ofBackground(248, 248, 48); //yellow
        face_newtral.draw(ofGetWidth()/4,ofGetHeight()/15);
        //ofTranslate(400, 0);
        face_newtral.play();
        face_newtral.update();
        face_newtral.stop();
    }
    
    
    
   
	
	int w = 100, h = 12;
	ofPushStyle();
	ofPushMatrix();
	ofTranslate(5, 10);
	int n = classifier.size();
	int primary = classifier.getPrimaryExpression();
	for(int i = 0; i < n; i++){
		//ofSetColor(i == primary ? ofColor::red : ofColor::black);
		//ofRect(0, 0, w * classifier.getProbability(i) + .5, h);
		ofSetColor(255);
		//ofDrawBitmapString(classifier.getDescription(i), 5, 9);
		ofTranslate(0, h + 5);
	}
	ofPopMatrix();
	ofPopStyle();
    
}


void testApp::keyPressed(int key) {
	//トラッカーのリセット
    if(key == 'r') {
		tracker.reset();
		classifier.reset();
	}
    //表情登録
	if(key == 's') {
        classifier.addExpression();
        classifier.addSample(tracker);
		classifier.save("expressions");
	}
    
    //表情読み込み
	if(key == 'l') {
		classifier.load("expressions");
	}
    
    // 'f'でフルスクリーン
    if (key == 'f') {
        ofToggleFullscreen();
    }
    //カーソル隠す
    if (key == 'c') {
        ofHideCursor();
    }

}