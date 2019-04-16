#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetCircleResolution(20);
    ofDisableArbTex();

    shader.load("shaders/vert.glsl", "shaders/frag.glsl", "");

    plane.set(ofGetWidth(), ofGetHeight(), 2, 2, OF_PRIMITIVE_TRIANGLES);
    plane.setPosition(ofGetWidth()/2, ofGetHeight()/2, 0);
    plane.rotateDeg(180, glm::vec3(0.0f,0.0f,1.0f));

    fbo.allocate(ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
    // draw something inside the FBO.
    fbo.begin();
    ofClear(0);
    ofBackground(ofFloatColor::lightPink);
    float time = ofGetElapsedTimef();

    ofSetColor(ofFloatColor::seaGreen);
    for(int x = 0; x< ofGetWidth(); x++){

        float y = ofMap(sin(time*0.6+x), -1.0f,1.0f, 0, ofGetHeight());
        ofDrawCircle(x,y, 5);
    }

    fbo.end();


    if(applyShaderEffect){
        shader.begin();
        shader.setUniformTexture("tex0", fbo.getTexture(), 0);
        shader.setUniform2f("uMousePos", mouseX, mouseY);
        shader.setUniform2f("uResolution", ofGetWidth(), ofGetHeight());
        shader.setUniform1f("uTime", ofGetElapsedTimef());
        plane.draw();
        shader.end();
    } else{
        fbo.draw(0,0);
    }

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 's') {
        applyShaderEffect = !applyShaderEffect;
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
