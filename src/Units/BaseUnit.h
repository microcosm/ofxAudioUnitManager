#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"

class BaseUnit {
    
public:
    virtual void setup();
    void showUI();
    void setParameter(int param, float value);
    void setParameters(int param1, int param2, ofVec2f value);
    ofxAudioUnit* get();
protected:
    ofxAudioUnit unit;
};