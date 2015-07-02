#pragma once
#include "ofMain.h"
#include "AudioUnitChain.h"
#include "AudioUnitBase.h"

class UIHandler{

public:
    void setup();
    void addChain();
    void drawControls();
    void drawChains(vector<AudioUnitChain*> chains);
    void drawWaveforms(AudioUnitChain* chain, float positionX);
    void drawChainReport(AudioUnitChain* chain, ofVec2f position, int chainNumber);
    void drawMidiReport(AudioUnitChain* chain, float positionX, int index);
protected:
    void drawDebugBox(int x, int y, int width, int height, ofColor color=ofColor(255, 255, 255, 32));
    ofVec2f getControlsPositions();
    ofColor getBackgroundColor(AudioUnitChain* chain);
    ofColor getTextColor(AudioUnitChain* chain);
    string controlsReport();
    string chainReport(AudioUnitChain* chain, int number);
    string midiReport(AudioUnitChain* chain, int index);

    ofxAudioUnitTap* tap;
    ofPolyline leftWaveform, rightWaveform;
    int padding, lastMidiRecieved, midiReceiptTimeout;
    string tempMidiReport;
    vector<string> reports;
    
    ofVec2f midiInfoPositions, midiInfoDimensions;
    ofVec2f chainInfoPositions, chainInfoDimensions;
    ofVec2f controlsPositions, controlsDimensions;
    ofVec2f waveformsPositions, waveformsDimensions;
};