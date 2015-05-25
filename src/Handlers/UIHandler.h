#pragma once
#include "ofMain.h"
#include "AudioUnitChain.h"

class UIHandler{

public:
    void setup();
    void drawControls();
    void drawChains(vector<AudioUnitChain*> chains);
protected:
    void drawDebugBox(int x, int y, int width, int height);
    string controls();

    ofVec2f chainInfoPositions, controlsPositions;
    ofVec2f chainInfoDimensions, controlsDimensions;
    float x, y;
};