#include "AudioUnitBase.h"

string AudioUnitBase::getID() {
    if(ID == "") generateID();
    return ID;
}

string AudioUnitBase::getName() {
    return name;
}

void AudioUnitBase::setID(string _ID) {
    ID = _ID;
}

void AudioUnitBase::setup() {
    ID = "";
}

void AudioUnitBase::showUI() {
    unit.showUI();
}

void AudioUnitBase::setParameter(int param, float value) {
    AudioUnitSetParameter(unit.getUnit(), param, kAudioUnitScope_Global, 0, value, 0);
}

void AudioUnitBase::setParameters(int param1, int param2, ofVec2f value) {
    setParameter(param1, value.x);
    setParameter(param2, value.y);
}

ofxAudioUnit* AudioUnitBase::get() {
    return &unit;
}

AudioUnitType AudioUnitBase::getType() {
    return type;
}

string AudioUnitBase::generateID() {
    return ofGetTimestampString(name + "-%Y-%m-%d-%H-%M-%S-%F");
}