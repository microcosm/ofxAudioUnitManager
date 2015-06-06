#pragma once
#include "ofMain.h"
#include "AudioUnitChain.h"
#include "AudioUnitBase.h"

class UIHandler{

public:
    void setup();
    void drawControls();
    void drawChains(vector<AudioUnitChain*> chains);
protected:
    void drawDebugBox(int x, int y, int width, int height, ofColor color=ofColor(255, 255, 255, 32));
    ofVec2f getControlsPositions();
    string controlsReport();
    string chainReport(AudioUnitChain* chain, int number);

    ofxAudioUnitTap* tap;
    ofPolyline leftWaveform, rightWaveform;

    ofVec2f chainInfoPositions, chainInfoDimensions;
    ofVec2f controlsPositions, controlsDimensions;
    float x, y;
};