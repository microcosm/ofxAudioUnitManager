#pragma once
#include "ofMain.h"
#include "aumAudioUnitChain.h"

class aumUserInterface{

public:
    void setup();
    void setFocus(bool _isFocused);
    void addChain();
    void drawControls();
    void drawChains(vector<aumAudioUnitChain*> chains);
    void drawWaveforms(aumAudioUnitChain* chain, float positionX);
    void drawChainReport(aumAudioUnitChain* chain, ofVec2f position, int chainNumber);
    void drawMidiReport(aumAudioUnitChain* chain, float positionX, int index);
protected:
    void drawDebugBox(int x, int y, int width, int height, ofColor color=ofColor(255, 255, 255, 32));
    ofVec2f getControlsPositions();
    ofColor getBackgroundColor(aumAudioUnitChain* chain);
    ofColor getTextColor(aumAudioUnitChain* chain);
    string controlsReport();
    string chainReport(aumAudioUnitChain* chain, int number);
    string midiReport(aumAudioUnitChain* chain, int index);

    ofxAudioUnitTap* tap;
    bool isFocused;
    ofPolyline leftWaveform, rightWaveform;
    int padding, midiReceiptTimeout;
    string tempMidiReport;
    vector<string> reports;
    vector<int> lastMidiRecieved;
    
    ofVec2f midiInfoPositions, midiInfoDimensions;
    ofVec2f chainInfoPositions, chainInfoDimensions;
    ofVec2f controlsPositions, controlsDimensions;
    ofVec2f waveformsPositions, waveformsDimensions;
};
