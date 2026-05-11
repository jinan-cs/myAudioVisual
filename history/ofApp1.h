#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxProcessFFT.h"
#include "ofxCV.h" // addon made by Kyle McDonald, I use this for skeletonization

class ofApp : public ofBaseApp{

	public:
		void setup() override;
		void update() override;
		void draw() override;
		void exit() override;

		void keyPressed(int key) override;
		void keyReleased(int key) override;
		void mouseMoved(int x, int y ) override;
		void mouseDragged(int x, int y, int button) override;
		void mousePressed(int x, int y, int button) override;
		void mouseReleased(int x, int y, int button) override;
		void mouseScrolled(int x, int y, float scrollX, float scrollY) override;
		void mouseEntered(int x, int y) override;
		void mouseExited(int x, int y) override;
		void windowResized(int w, int h) override;
		void dragEvent(ofDragInfo dragInfo) override;
		void gotMessage(ofMessage msg) override;
		
    
    // for vectorise data img (given a png)
    ofImage img;
    ofxCvGrayscaleImage grayImg;
    ofxCvContourFinder contourFinder;
    vector<ofPolyline> outline; // store the scanned line art in vector (polyline)
    
    // for low, mid, high value analysis
    ProcessFFT fft;
    float gain=3.0; // if the val given by fft is too small, use this to scale it(?)
//    vector<float> low_mid_high; // store the val of each field
};
