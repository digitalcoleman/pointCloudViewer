#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxDOF.h"

class ofApp : public ofBaseApp{

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
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
        void loadPoints(string fileName);
    
    ofEasyCam cam;
    ofMesh mesh;
    ofLight	light;
    
    ofxPanel gui;
    ofxFloatSlider scaler;
    ofxFloatSlider pointSize;
    ofxFloatSlider focusDist;
    ofxFloatSlider focalLength;
    ofxFloatSlider blur;
    ofxToggle meshOn;
    
	ofxDOF depthOfField;
		
};
