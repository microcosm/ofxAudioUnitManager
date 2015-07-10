#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxManagedAudioUnit.h"

class Reverb : public ofxManagedAudioUnit {
    
public:
    void setup();
};