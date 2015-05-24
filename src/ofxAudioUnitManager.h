#pragma once
#include "ofMain.h"
#include "BaseChain.h"
#include "Compressor.h"

class ofxAudioUnitManager {
public:
    void setup();
    void add(BaseChain *chain, string name, ofColor color);
    void update();
    void draw();
    void toggleDebugUI();

protected:
    void drawDebugBox(int x, int y, int width, int height);
    
    Compressor compressor;
    ofxAudioUnitMixer mixer;
    ofxAudioUnitOutput output;
    vector<BaseChain*> chains;
    bool showDebugUI;
    int reportMargin, reportWidth, reportHeight;
    float x, y;
};