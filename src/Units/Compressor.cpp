#include "Compressor.h"

void Compressor::setup() {
    unit = ofxAudioUnit(kAudioUnitType_Effect,
                        kAudioUnitSubType_DynamicsProcessor);
    BaseUnit::setup();
}