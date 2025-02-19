#pragma once

#include "ofMain.h"
#include "ofxFaceTracker.h"

class testApp : public ofBaseApp {
public:
	void setup();
	void update();
	void draw();
	void keyPressed(int key);
	
	ofVideoGrabber cam;
	ofxFaceTracker tracker;
	ExpressionClassifier classifier;
    
    ofImage myImage;
    ofVideoPlayer face_newtral;
    ofVideoPlayer face_smile;
};
