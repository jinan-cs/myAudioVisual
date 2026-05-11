#include "ofApp.h"
using namespace ofxCv;// namepsace of Kyle's cv
using namespace cv; // namespace of OpenCV

//--------------------------------------------------------------
void ofApp::setup(){
    // basic display setting
    ofSetFrameRate(60);
    ofBackground(100,100,100);
    
    // Processfft capture
    fft.setup();
    fft.setNumFFTBins(16);  // how many Columns are we analyzing - 16-32, etc
    fft.setNormalize(true); // ow the value will be in range 0 ... -1000
    
    // load img
    img.load("tab.png");
    img.setImageType(OF_IMAGE_GRAYSCALE); // 4 channels (png) -> 1 channels
    
    grayImg.allocate(img.getWidth(), img.getHeight());
    grayImg.setFromPixels(img.getPixels());
    
    grayImg.invert(); // very importnat, otherwise nothing will be caught
    grayImg.threshold(150); // anything brigher than the val becomes white
//
    // threshold to get distinct shapes
    contourFinder.findContours(grayImg, 2, (grayImg.getWidth() * grayImg.getHeight()) /2, 10, true, true); // set the first boolean to true to detect inner shape (hole)
    
    // store as polyline object
    for(int i=0; i<contourFinder.nBlobs; i++){
        //        contourFinder.blobs[i].draw();
        ofPolyline polyline;
        polyline.addVertices(contourFinder.blobs[i].pts);
        polyline = polyline.getResampledBySpacing(2).getSmoothed(2); // smooth the line
        outline.push_back(polyline);
    }
    ofSleepMillis(30);
}

//--------------------------------------------------------------
void ofApp::update(){
    fft.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
//    grayImg.draw(0, 0);
    ofSetColor(255, 255, 255);
    ofDrawBitmapString("Low: "+ofToString(fft.getLowVal()*gain), 20, 20);
    ofDrawBitmapString("Mid: "+ofToString(fft.getLowVal()*gain), 20, 40);
    ofDrawBitmapString("High: "+ofToString(fft.getLowVal()*gain), 20, 60);
    
    // draw reji img ------------
    ofFill();
    ofSetColor(255,0,0); // set to 0,0,0 make the image display as black square
    ofSetLineWidth(1.5);
    
    float spacing = ofGetWidth() / 4.0; // get 3 points
    float centerY = ofGetHeight() / 2.0;
    vector<float> low_mid_high={fft.getLowVal(),fft.getMidVal(),fft.getHighVal()};
    for(int j=0; j<3; j++){
        // reset the drawing origin
        ofPushMatrix();
        ofTranslate(spacing * (j+1), centerY);
        if(j==0)
                ofSetColor(255, 0, 0);
        else if(j==1)
                ofSetColor(0, 255, 0);
        else if(j==2)
                ofSetColor(0, 0, 255);
    
        // scale the icon according to fft (low, mid, high, resp.)
        float fftScale = ofMap(low_mid_high[j]*gain, 0.0, 1.0, 1.0, 2.0);
        ofScale(fftScale, fftScale);
        ofTranslate(-img.getWidth() / 2.0, -img.getHeight() / 2.0);
        
        // draw the reji icon
        for(auto& line: outline){
            line.draw();
        }
    
    ofPopMatrix();
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseScrolled(int x, int y, float scrollX, float scrollY){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
