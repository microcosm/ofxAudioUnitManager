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

protected:
    Compressor compressor;
    ofxAudioUnitMixer mixer;
    ofxAudioUnitOutput output;

    vector<BaseChain*> chains;
};