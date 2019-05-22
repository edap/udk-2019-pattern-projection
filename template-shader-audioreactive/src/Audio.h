#pragma once

#include "ofMain.h"
#include "ofxGui.h"

class Audio{
public:
    Audio();
    void setup(std::string filename);
    void play();
    void stop();
    void setSpeed(float vel);
    void update();
    void update(const vector<float>& interpolations);
    void draw();

    ofParameterGroup params;
    ofParameter<std::string> currentPosition = {"pos:", "0"};
    ofParameter<float> setPos = {"pos", 0.0, 0.0, 1.0};
    ofParameter<float> speed = {"speed", 1.0f, 0.01f, 1.0f};
    ofParameter<float> smooth = {"smooth", 0.9600f, 0.9600f, 0.9999f};
    ofParameter<float> position = {"positionMS", 0.0, 0.0f, 1.0f};
    ofParameter<void> pauseSong = {"pause song"};

    ofParameterGroup paramsControl;

    ofParameterGroup paramsBandSelection;
    ofParameter<bool> powHighFrew = {"powHighFrew", false};
    ofParameter<int> minLowBand = {"minLowBand", 150, 0, nBandsToGet};
    ofParameter<int> maxLowBand = {"maxLowBand", 180, 0, nBandsToGet};
    ofParameter<float> magLowBand = {"magLowBand", 1, 0.01f, 5.0f};

    ofParameter<int> minMiddleBand = {"minMiddleBand", 244, 0, nBandsToGet};
    ofParameter<int> maxMiddleBand = {"maxMiddleBand", 364, 0, nBandsToGet};
    ofParameter<float> magMiddleBand = {"magMiddleBand", 1, 0.01f, 5.0f};

    ofParameter<int> minHighBand = {"minHighBand", 604, 0, nBandsToGet};
    ofParameter<int> maxHighBand = {"maxHighBand", 744, 0, nBandsToGet};
    ofParameter<float> magHighBand = {"magHighBand", 1, 0.01f, 5.0f};

    float getLow()    const {return lowFreq;};
    float getMiddle() const {return middleFreq;};
    float getHigh()   const {return highFreq;};

    ofEventListener pauseListener;
    ofEventListener speedListener;
    ofEventListener setPosListener;


private:
    void changeSpeed();
    void changePause();
    void changePosition(float p);
    ofSoundPlayer mySound;
    float * fft;
    bool enabled = true;
    bool paused = false;

    float lowFreq;
    float middleFreq;
    float highFreq;
    static constexpr size_t nBandsToGet = 1024;
    std::array<float, nBandsToGet> fftSmoothed{{0}};
};
