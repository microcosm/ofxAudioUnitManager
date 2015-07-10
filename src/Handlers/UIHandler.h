#pragma once
#include "ofMain.h"
#include "ofxAudioUnitChain.h"

class UIHandler{

public:
    void setup();
    void addChain();
    void drawControls();
    void drawChains(vector<ofxAudioUnitChain*> chains);
    void drawWaveforms(ofxAudioUnitChain* chain, float positionX);
    void drawChainReport(ofxAudioUnitChain* chain, ofVec2f position, int chainNumber);
    void drawMidiReport(ofxAudioUnitChain* chain, float positionX, int index);
protected:
    void drawDebugBox(int x, int y, int width, int height, ofColor color=ofColor(255, 255, 255, 32));
    ofVec2f getControlsPositions();
    ofColor getBackgroundColor(ofxAudioUnitChain* chain);
    ofColor getTextColor(ofxAudioUnitChain* chain);
    string controlsReport();
    string chainReport(ofxAudioUnitChain* chain, int number);
    string midiReport(ofxAudioUnitChain* chain, int index);

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