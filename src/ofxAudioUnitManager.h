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
    void incrementSelected();
    void decrementSelected();

protected:
    void drawDebugBox(int x, int y, int width, int height);
    void selectChain(int index);
    
    Compressor compressor;
    Controls controls;
    ofxAudioUnitMixer mixer;
    ofxAudioUnitOutput output;
    vector<BaseChain*> chains;
    bool showDebugUI;
    int reportMargin, reportWidth, reportHeight, selectedChain;
    float x, y;
};