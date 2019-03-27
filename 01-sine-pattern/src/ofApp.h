#pragma once

#include "ofMain.h"
#include "ofxgui.h"

class ofApp : public ofBaseApp{

public:
    void setup();
    void update();
    void draw();

    void keyPressed(int key);

    ofxPanel gui;
    ofParameter <int> radius;
    ofParameter <float> freq;
    ofParameter <int> amp;
    ofParameter <float> col;
    ofParameter <float> alpha;

    bool drawGui = true;
};
