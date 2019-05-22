#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    shader.load("shaders/vert.glsl", "shaders/frag.glsl", "");
    audio.setup("1085.mp3");
    audio.play();
    gui.setup();
    gui.add(audio.params);
}

//--------------------------------------------------------------
void ofApp::update(){
    audio.update();

}

//--------------------------------------------------------------
void ofApp::draw(){
    if(debugAudio){
        audio.draw();
        gui.draw();
    }else{
        shader.begin();
        shader.setUniform2f("uMousePos", mouseX, mouseY);
        shader.setUniform2f("uResolution", ofGetWidth(), ofGetHeight());
        shader.setUniform1f("uTime", ofGetElapsedTimef());
        // audio uniforms!
        shader.setUniform1f("uLowBand", audio.getLow());
        shader.setUniform1f("uMiddleBand", audio.getMiddle());
        shader.setUniform1f("uHighBand", audio.getHigh());

        ofDrawRectangle(0, 0, ofGetWidth(), ofGetHeight());
        shader.end();
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if(key == 'a'){
        debugAudio = !debugAudio;
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
