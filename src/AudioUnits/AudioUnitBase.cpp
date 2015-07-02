#include "AudioUnitBase.h"

string AudioUnitBase::getClassName() {
    return className;
}

void AudioUnitBase::setup() {}

void AudioUnitBase::showUI(string chainName, int chainIndex, int numChains, int unitIndex, int numUnits) {
    x = ofMap(chainIndex, 0, numChains - 1, 0, ofGetScreenWidth() * 0.5);
    y = ofMap(unitIndex, 0, numUnits - 1, 0, ofGetScreenHeight() * 0.5);
    unit.showUI(chainName + ": " +
                unitName + (unitName.length() > 0 ? " " : "") +
                className, x, y);
}

void AudioUnitBase::setUnitName(string name) {
    unitName = name;
}

void AudioUnitBase::set(int param, float value) {
    AudioUnitSetParameter(unit.getUnit(), param, kAudioUnitScope_Global, 0, value, 0);
}

void AudioUnitBase::set(int param1, int param2, ofVec2f value) {
    set(param1, value.x);
    set(param2, value.y);
}

void AudioUnitBase::set(int param1, int param2, int param3, ofVec3f value) {
    set(param1, value.x);
    set(param2, value.y);
    set(param3, value.z);
}

ofxAudioUnit* AudioUnitBase::getUnit() {
    return &unit;
}

AudioUnitType AudioUnitBase::getType() {
    return type;
}

bool AudioUnitBase::isSynth() {
    return type == AU_TYPE_SYNTH;
}