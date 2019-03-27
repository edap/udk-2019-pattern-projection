#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(100);

    gui.setup();
    gui.add(radius.set("circle",10,1,30));
    gui.add(freq.set("frequency",0.1,0.01,1));
    gui.add(amp.set("amplitude",200,1,600));
    gui.add(col.set("color",0.01,0.001,0.1));
    gui.add(alpha.set("alpha",125,0,255));

    ofEnableAlphaBlending();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground(0);
    float time = ofGetElapsedTimef();
    
    for (int i = 0; i <900; i++){
        ofSetColor(2000 * col,               //red channel
                   127+30 * cos(i*col+time), //blue channel
                   127+100 * sin(i*col+time),//green channel
                   alpha);                   // alpha

        ofDrawCircle(50+i,sin(i*freq + time) * amp +400,radius);

    }

    if(drawGui){
        gui.draw();
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'g'){
        drawGui = !drawGui;
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
