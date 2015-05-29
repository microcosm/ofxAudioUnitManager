#include "LowPassFilter.h"

void LowPassFilter::setup() {
    unit = ofxAudioUnit(kAudioUnitType_Effect,
                          kAudioUnitSubType_LowPassFilter);
    AudioUnitSetParameter(unit.getUnit(), kLowPassParam_Resonance,
                          kAudioUnitScope_Global, 0, 20, 0);
    type = AU_TYPE_UNIT;
    name = "LowPassFilter";
    AudioUnitBase::setup();
}