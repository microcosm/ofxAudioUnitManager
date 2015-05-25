#pragma once
#include "ofMain.h"
#include "BaseChain.h"
#include "Compressor.h"
#include "Controls.h"

class ofxAudioUnitManager {
public:
    void setup();
    void add(BaseChain *chain, string name, ofColor color);
    void update();
    void draw();
    void exit();
    void toggleDebugUI();

protected:
    void drawDebugBox(int x, int y, int width, int height);
    
    Compressor compressor;
    Controls controls;
    ofxAudioUnitMixer mixer;
    ofxAudioUnitOutput output;
    vector<BaseChain*> chains;
    bool showDebugUI;
    int reportMargin, reportWidth, reportHeight;
    float x, y;
};