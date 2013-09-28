#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxPostProcessing.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
	
	ofEasyCam cam;
	vector<ofVec3f> landscape;
	vector<float> matricesData;
	ofMesh landscapeMesh;
	void generateLandscape();
	
	float zincr;
	float noiseZ;
	
	ofxPanel gui;
	ofxSlider<float> guiZIncr;
	bool guiVisible;
	
	ofLight light;
	ofShader shader;
	
	GLuint vboid;
	ofVboMesh vboMesh;

	ofxPostProcessing postFx;
};

