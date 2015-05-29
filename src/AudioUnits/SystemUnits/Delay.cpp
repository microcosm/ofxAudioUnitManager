#include "Delay.h"

void Delay::setup() {
    unit = ofxAudioUnit(kAudioUnitType_Effect,
                        kAudioUnitSubType_SampleDelay);
    
    type = AU_TYPE_UNIT;
    name = "Delay";
    AudioUnitBase::setup();
}