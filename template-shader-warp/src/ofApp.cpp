#include "ofApp.h"


void ofApp::setup(){
    rect.setPosition(100, 100);
    rectPos = glm::vec2(rect.getPosition());

    shader.load("shaders/vert.glsl", "shaders/frag.glsl", "");

    warper.setup(rectPos.x, rectPos.y, rect.getWidth(), rect.getHeight());
    //initializates ofxGLWarper
	warper.activate();
    // this allows ofxGLWarper to automatically listen to the mouse and keyboard input and updates automatically it's matrixes.

    ofBackground(20, 20, 20);
	warper.drawSettings.bDrawRectangle = true;
    // default: true. Check drawSettings options for customization.
}


void ofApp::update(){

	
}

void ofApp::draw(){

    warper.begin();
    ///all the things that are drawn AFTER ofxGLWarper's begin method are afected by it.
	
    shader.begin();
    shader.setUniform2f("uMousePos", mouseX, mouseY);
    shader.setUniform2f("uResolution", rect.getWidth(), rect.getHeight());
    ofDrawRectangle(rectPos.x, rectPos.y, rect.getWidth(), rect.getHeight());
    shader.end();

	warper.end();
	
}
//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            if (warper.isActive()) {
                warper.deactivate();
            }else {
                warper.activate();
            }

            break;
        default:
            break;
    }
}
//--------------------------------------------------------------
void ofApp::keyReleased(int key){}
//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){}
//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){}
//--------------------------------------------------------------
void ofApp::mouseReleased(){}
