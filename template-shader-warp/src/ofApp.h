#pragma once

#include "ofMain.h"
#include "ofxGLWarper.h"
#include "ofxAutoReloadedShader.h"

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
    void mouseReleased();

    ofxGLWarper warper;
    ofxAutoReloadedShader shader;

    ofRectangle rect = ofRectangle(0, 0, 500, 500);
    glm::vec2 rectPos;

};


