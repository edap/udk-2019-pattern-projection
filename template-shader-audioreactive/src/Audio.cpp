#include "Audio.h"

Audio::Audio(){
    params.setName("Audio");
    params.add(smooth);
    paramsControl.setName("controls");
    paramsControl.add(currentPosition);
    //paramsControl.add(setPos); // do not save this in the presets or it skrew
    //paramsControl.add(speed);
    paramsControl.add(pauseSong);
    paramsBandSelection.setName("band selection");
    paramsBandSelection.add(powHighFrew);
    paramsBandSelection.add(minLowBand);
    paramsBandSelection.add(maxLowBand);
    paramsBandSelection.add(magLowBand);
    paramsBandSelection.add(minMiddleBand);
    paramsBandSelection.add(maxMiddleBand);
    paramsBandSelection.add(magMiddleBand);
    paramsBandSelection.add(minHighBand);
    paramsBandSelection.add(maxHighBand);
    paramsBandSelection.add(magHighBand);

    params.add(paramsControl);
    params.add(paramsBandSelection);

    speedListener = speed.newListener([this](float s){setSpeed(s);});
    pauseListener = pauseSong.newListener([this](){changePause();});
    setPosListener = setPos.newListener([this](float p){changePosition(p);});


};

void Audio::setup(std::string filename){
    mySound.load(filename);
    mySound.setLoop(true);
}

void Audio::changePause(){
    paused = !paused;
    mySound.setPaused(paused);
}

void Audio::changePosition(float p){
    mySound.setPosition(p);

}

void Audio::update(){
    currentPosition.set(ofToString(mySound.getPosition()));
    // grab the fft, and put in into a "smoothed" array,
    // by taking maximums, as peaks and then smoothing downward
    float * val = ofSoundGetSpectrum(nBandsToGet);
    float sumLow = 0.0f;
    float sumMiddle = 0.0f;
    float sumHigh = 0.0f;
    for (int i = 0;i < nBandsToGet; i++){
        // let the smoothed value sink to zero:
        fftSmoothed[i] *= smooth.get();

        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];

        if (i>minLowBand.get() & i < maxLowBand.get()) {
            sumLow += fftSmoothed[i];
        } else if(i>minMiddleBand.get() & i < maxMiddleBand.get()) {
            sumMiddle += fftSmoothed[i];
        } else if(i>minHighBand.get() & i < maxHighBand.get()) {
            sumHigh += fftSmoothed[i];
        }
    }

    lowFreq = sumLow / float(maxLowBand.get() - minLowBand.get());
    middleFreq = sumMiddle / float(maxMiddleBand.get() - minMiddleBand.get());
    highFreq = sumHigh / float(maxHighBand.get() - minHighBand.get());

    lowFreq *= magLowBand.get();
    middleFreq *= magMiddleBand.get();
    highFreq *= magHighBand.get();

}

// when recording the video, the min and max for the low band selection
// come from vezer.
void Audio::update(const vector<float>& interpolations){
    currentPosition.set(ofToString(mySound.getPosition()));
    // grab the fft, and put in into a "smoothed" array,
    // by taking maximums, as peaks and then smoothing downward
    if (interpolations.size() > 3) {
        minLowBand.set( int(interpolations.at(3)) );
        maxLowBand.set( int(interpolations.at(4)) );
    }

    float * val = ofSoundGetSpectrum(nBandsToGet);
    float sumLow = 0.0f;
    float sumMiddle = 0.0f;
    float sumHigh = 0.0f;
    for (int i = 0;i < nBandsToGet; i++){
        // let the smoothed value sink to zero:
        fftSmoothed[i] *= smooth.get();

        // take the max, either the smoothed or the incoming:
        if (fftSmoothed[i] < val[i]) fftSmoothed[i] = val[i];

        if (i>minLowBand.get() & i < maxLowBand.get()) {
            sumLow += fftSmoothed[i];
        } else if(i>minMiddleBand.get() & i < maxMiddleBand.get()) {
            sumMiddle += fftSmoothed[i];
        } else if(i>minHighBand.get() & i < maxHighBand.get()) {
            sumHigh += fftSmoothed[i];
        }
    }

    lowFreq = sumLow / float(maxLowBand.get() - minLowBand.get());
    middleFreq = sumMiddle / float(maxMiddleBand.get() - minMiddleBand.get());
    highFreq = sumHigh / float(maxHighBand.get() - minHighBand.get());

    lowFreq *= magLowBand.get();
    middleFreq *= magMiddleBand.get();
    highFreq *= magHighBand.get();
};

void Audio::play(){
    mySound.play();
}

void Audio::stop(){
    mySound.stop();
}

void Audio::setSpeed(float vel = 1.0f){
    mySound.setSpeed(vel);
}

void Audio::draw(){
    ofPushStyle();
    ofBackground(0);
    float width = ((float)(ofGetWidth()) / nBandsToGet);
    for (int i = 0;i < nBandsToGet; i++){
        int b = 255.0f / float(nBandsToGet) * i;
        int g = 30;
        int r = 255 - b;
        ofSetColor(r,g,b);
        // (we use negative height here, because we want to flip them
        // because the top corner is 0,0)
        ofDrawRectangle(i*width,ofGetHeight()-100,width,-(fftSmoothed[i] * 200));
    }


    ofSetColor(255,255,0);
    for (int i = 0; i < nBandsToGet; i++) {
        if (i%100 == 0) {
            float freq = (i * 44100)/nBandsToGet;
            ofDrawBitmapString(ofToString(freq)+" Hz", i* width, ofGetHeight()-10);
        }
    }

    ofNoFill();
    // low
    ofDrawRectangle(minLowBand.get(), 50,
                    maxLowBand.get()-minLowBand.get(), 750);
    ofDrawBitmapString("low", minLowBand.get(), 40);

    // middle
    ofDrawRectangle(minMiddleBand.get(), 50,
                    maxMiddleBand.get()-minMiddleBand.get(), 750);
    ofDrawBitmapString("middle", minMiddleBand.get(), 40);
    // high
    ofDrawRectangle(minHighBand.get(), 50,
                    maxHighBand.get()-minHighBand.get(), 750);
    ofDrawBitmapString("high", minHighBand.get(), 40);

    // average values
    ofFill();
    ofDrawRectangle(minLowBand.get(), 50,
                    maxLowBand.get()-minLowBand.get(), lowFreq*400);
    // middle
    ofDrawRectangle(minMiddleBand.get(), 50,
                    maxMiddleBand.get()-minMiddleBand.get(), middleFreq*400);

    // high
    ofDrawRectangle(minHighBand.get(), 50,
                    maxHighBand.get()-minHighBand.get(), highFreq*400);
    ofPopStyle();

}

void Audio::changeSpeed(){
    mySound.setSpeed(speed.get());
}
