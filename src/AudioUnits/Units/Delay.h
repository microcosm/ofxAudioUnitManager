#pragma once
#include "ofMain.h"
#include "ofxManagedAudioUnit.h"

class Delay : public ofxManagedAudioUnit {
    
public:
    void setup();
};

const static int DelayTime = 0; //[0 : 4410 : 0]