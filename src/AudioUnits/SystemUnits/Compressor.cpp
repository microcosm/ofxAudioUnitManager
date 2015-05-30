#include "Compressor.h"

void Compressor::setup() {
    unit = ofxAudioUnit(kAudioUnitType_Effect,
                        kAudioUnitSubType_DynamicsProcessor);
    type = AU_TYPE_UNIT;
    className = "Compressor";
    AudioUnitBase::setup();
}