#pragma once
#include "ofMain.h"
#include "AudioUnitChain.h"
#include "AudioUnitBase.h"

class UIHandler{

public:
    void setup();
    void drawControls();
    void drawChains(vector<AudioUnitChain*> chains);
    void drawWaveforms(AudioUnitChain* chain, float positionX);
    void drawChainReport(AudioUnitChain* chain, ofVec2f position, int chainNumber);
protected:
    void drawDebugBox(int x, int y, int width, int height, ofColor color=ofColor(255, 255, 255, 32));
    ofVec2f getControlsPositions();
    string controlsReport();
    string chainReport(AudioUnitChain* chain, int number);

    ofxAudioUnitTap* tap;
    ofPolyline leftWaveform, rightWaveform;
    int padding;

    ofVec2f chainInfoPositions, chainInfoDimensions;
    ofVec2f controlsPositions, controlsDimensions;
    ofVec2f waveformsPositions, waveformsDimensions;
};