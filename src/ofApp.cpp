#include "ofApp.h"
using namespace ofxCv;// namepsace of Kyle's cv
using namespace cv; // namespace of OpenCV

//--------------------------------------------------------------
void ofApp::setup(){
    // basic display setting
    ofSetFrameRate(60);
    ofBackground(0);
//    ofSetBackgroundAuto(false); // turn off cleaning up the screen in every new draw loop
    
    // Processfft capture
    fft.setup(512);
    
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
    // fade-out effect
//    ofSetColor(0,0,0,200); // larger the alpha val, faster the fade out
//    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
    
    
    vector<float> buffer;
    buffer = fft.getBins();
    
    // draw reji img ------------
    ofFill();
    ofSetColor(0,0,255); // set to 0,0,0 make the image display as black square
    ofSetLineWidth(1.5);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    float x_spacing = img.getWidth(); // get 3 points
    float yCenter = ofGetHeight() / 2.0;
    int y_img_n_half = yCenter / img.getHeight(); // can at most put this many img at half
    int count=0;// for counting img print on yCenter axis
    for(int i=0; i<buffer.size(); i+=buffer.size()/(ofGetWidth()/x_spacing)){
//        printf("i=%d, buffer[i]=%f\n",i,buffer[i]);
        
        // set color
        ofColor col;
        float hue = ofMap(i, 0, buffer.size(), 0, 255);
        float br = ofMap(buffer[i], 0.0, 1.0, 50, 255);
        int n_img_verti = int(ofMap(buffer[i], 0.0, 1.0, 0, y_img_n_half)); // of the freq is stronger, more img printed on vertical direction
        col.setHsb(hue, 255, br, 255);
        ofSetColor(col);
        
        
        // reset the drawing origin
//        for(int j=0; j<ofGetHeight()/y_spacing; j++){
            ofPushMatrix();
            ofTranslate(x_spacing * count, yCenter);
//            ofTranslate(x_spacing * (i+1), y_spacing * (j+1));
            // draw the reji icon
            for(auto& line: outline){
                line.draw();
            }
            ofPopMatrix();
        
            // extra img print on the vertical direction
            for(int k=-n_img_verti; k<n_img_verti; k++){
                ofPushMatrix();
                ofTranslate(x_spacing * count, yCenter + k * img.getHeight());
                for(auto& line: outline){
                    line.draw();
                }
                ofPopMatrix();
            }
        count++;
            
//        }
    }
    // print normal sound responser on the buttom
    for(int i=0; i<buffer.size(); i++){
        // set color
        ofColor col;
        float hue = ofMap(i, 0, buffer.size(), 0, 255);
        float br = ofMap(buffer[i], 0.0, 1.0, 0, 255);
        col.setHsb(hue, 255, br, 255);
        ofSetColor(col);
        
        // debug
        float x=ofMap(i, 0, buffer.size(), 0, ofGetWidth()/1.0);
        float y=ofMap(buffer[i], 0.0, 1.0, 0.0, ofGetHeight()/4.0);
        ofDrawLine(x, ofGetHeight(), x, ofGetHeight() - y);
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
