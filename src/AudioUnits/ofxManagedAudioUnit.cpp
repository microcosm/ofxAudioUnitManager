#include "ofxManagedAudioUnit.h"

string ofxManagedAudioUnit::getClassName() {
    return className;
}

void ofxManagedAudioUnit::setup(OSType type, OSType subType, OSType manufacturer,
                                string _className) {
    unit = ofxAudioUnit(type, subType, manufacturer);
    this->type = stringify(type) == "aumu" ? AU_TYPE_SYNTH : AU_TYPE_UNIT;
    className = _className;
    if(className == "") {
        className = stringify(type, subType, manufacturer);
    }
    isSetup = true;
}

void ofxManagedAudioUnit::setup(OSType type, OSType subType, OSType manufacturer,
                                AudioUnitType _type, string _className) {
    this->type = _type;
    setup(type, subType, manufacturer, _className);
}

void ofxManagedAudioUnit::setup() {
    isSetup = true;
}

void ofxManagedAudioUnit::showUI(string chainName, int chainIndex, int numChains, int unitIndex, int numUnits) {
    x = ofMap(chainIndex, 0, numChains - 1, 0, ofGetScreenWidth() * 0.5);
    y = ofMap(unitIndex, 0, numUnits - 1, 0, ofGetScreenHeight() * 0.5);
    unit.showUI(chainName + ": " +
                unitName + (unitName.length() > 0 ? " " : "") +
                className, x, y);
}

void ofxManagedAudioUnit::setUnitName(string name) {
    unitName = name;
}

void ofxManagedAudioUnit::set(int param, float value) {
    AudioUnitSetParameter(unit.getUnit(), param, kAudioUnitScope_Global, 0, value, 0);
}

void ofxManagedAudioUnit::set(int param1, int param2, ofVec2f value) {
    set(param1, value.x);
    set(param2, value.y);
}

void ofxManagedAudioUnit::set(int param1, int param2, int param3, ofVec3f value) {
    set(param1, value.x);
    set(param2, value.y);
    set(param3, value.z);
}

ofxAudioUnit* ofxManagedAudioUnit::getUnit() {
    return &unit;
}

AudioUnitType ofxManagedAudioUnit::getType() {
    return type;
}

bool ofxManagedAudioUnit::isSynth() {
    return type == AU_TYPE_SYNTH;
}

bool ofxManagedAudioUnit::hasBeenSetup() {
    return isSetup;
}

string ofxManagedAudioUnit::stringify(OSType type, OSType subType, OSType manufacturer) {
    return stringify(type) + "-" + stringify(subType) + "-" + stringify(manufacturer);
}

string ofxManagedAudioUnit::stringify(OSType code) {
    char char4 = code&0xFF;
    char char3 = (code>>8)&0xFF;
    char char2 = (code>>16)&0xFF;
    char char1 = (code>>24)&0xFF;
    return ofToString(char1) + ofToString(char2) + ofToString(char3) + ofToString(char4);
}