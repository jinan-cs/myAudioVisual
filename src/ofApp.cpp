#include "ofApp.h"
using namespace ofxCv;// namepsace of Kyle's cv
using namespace cv; // namespace of OpenCV

//--------------------------------------------------------------
void ofApp::setup(){
    // basic display setting
    ofSetFrameRate(60);
    ofBackground(0);
//    ofSetBackgroundAuto(false); // fade-out effect: turn off cleaning up the screen in every new draw loop
    
    // Processfft capture
    fft.setup(512);
    
    // load img
    img.load("tab.png");
    img.setImageType(OF_IMAGE_GRAYSCALE); // 4 channels (png) -> 1 channels
    
    grayImg.allocate(img.getWidth(), img.getHeight());
    grayImg.setFromPixels(img.getPixels());
    
    grayImg.invert(); // very importnat, otherwise nothing will be caught
    grayImg.threshold(150); // anything brigher than the val becomes white

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
    
    // set drawing flag
    draw_raw_fft=true;
    
    // this allow the machine having some time (?) to reach to the microphone
    ofSleepMillis(30);
}

//--------------------------------------------------------------
void ofApp::update(){
    fft.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    // fade-out effect
//    ofSetColor(0,0,0,10); // larger the alpha val, faster the fade out
//    ofFill();
//    ofDrawRectangle(0,0,ofGetWidth(), ofGetHeight());
    ofSetColor(255);
    ofDrawBitmapString("Press 'w' to turn on/off the raw FFT wave.", 0, 20);
    
    vector<float> buffer;
    buffer = fft.getBins();
    
    // draw the img ------------
    ofFill();
    ofSetColor(0,0,255); // set to 0,0,0 make the image display as black square
    ofSetLineWidth(1.5);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    float x_spacing = img.getWidth(); // get 3 points
    float yCenter = ofGetHeight() / 2.0 - img.getHeight()/2.0; // center the imgs
    float xCenter = ofGetWidth() / 2.0 - img.getWidth()/2.0; // center the imgs
    vector<float> rangeMax(ofGetWidth()/2.0/x_spacing + 1,0);
    int range_i=0;
    int range_band = buffer.size()/rangeMax.size(); // the length of a range among the buffer
    float local_max=0.0;
    
    // print normal sound responser on the buttom
    for(int i=0; i<buffer.size(); i++){
        if(draw_raw_fft){ // only draw if the flag is on
            // set color
            ofColor col;
            float hue = ofMap(i, 0, buffer.size(), 0, 255);
            float br = ofMap(buffer[i], 0.0, 1.0, 0, 255);
            col.setHsb(hue, 255, br, 255);
            ofSetColor(col);
            // also print this symmmertically
            float x=ofMap(i, 0, buffer.size(), 0, ofGetWidth()/2.0);
            float y=ofMap(buffer[i], 0.0, 1.0, 0.0, ofGetHeight()/4.0);
            ofDrawLine(ofGetWidth()/2.0 - x, ofGetHeight(), ofGetWidth()/2.0 -x, ofGetHeight() - y); // left
            ofDrawLine(ofGetWidth()/2.0 + x, ofGetHeight(), ofGetWidth()/2.0 + x, ofGetHeight() - y); // right
        }
        // update the range max value
        local_max = buffer[i]>local_max ? buffer[i] : local_max;
        // store range max
        if((i+1) % range_band==0 and range_i<rangeMax.size()) {
            rangeMax[range_i++] = local_max;
            local_max=0.0;
        }
    }
    
    // draw symmertric using rangeMax vector (rather than buffer[i])
    int y_img_n_half = yCenter / img.getHeight(); // can at most put this many img at half
    int count=0;// for counting img print on yCenter axis
    
    for(int i=0; i<rangeMax.size(); i++){
        // set color
        ofColor col;
        float hue = ofMap(i*range_band, 0, buffer.size(), 0, 200);
        float br = ofMap(rangeMax[i], 0.0, 1.0, 100, 255);
        int n_img_verti = int(ofMap(rangeMax[i], 0.0, 1.0, 0, y_img_n_half)); // of the freq is stronger, more img printed on vertical direction
        col.setHsb(hue, 255, br, 255);
        ofSetColor(col);
        
        // draw imgs on the center y axis
        // left
        float lx = xCenter - x_spacing * count;
        ofPushMatrix();
        ofTranslate(lx, yCenter);
        for(auto& line: outline){
            line.draw();
        }
        ofPopMatrix();
        // extra img print on the vertical direction
        for(int k=-n_img_verti; k<n_img_verti; k++){
            ofPushMatrix();
            ofTranslate(lx, yCenter + k * img.getHeight());
            for(auto& line: outline){
                line.draw();
            }
            ofPopMatrix();
        }
        
        // right
        ofPushMatrix();
        float rx = xCenter + x_spacing * count;
        ofTranslate(rx, yCenter);
        for(auto& line: outline){
            line.draw();
        }
        ofPopMatrix();
        
        // extra img print on the vertical direction
        for(int k=-n_img_verti; k<n_img_verti; k++){
            ofPushMatrix();
            ofTranslate(rx, yCenter + k * img.getHeight());
            for(auto& line: outline){
                line.draw();
            }
            ofPopMatrix();
        }
        count++;
        
//        }
    }
}

//--------------------------------------------------------------
void ofApp::exit(){

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key=='w'){
        draw_raw_fft =  !draw_raw_fft;
    }
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
