#include "aumManagedAudioUnit.h"

void aumManagedAudioUnit::setup(string _unitName, aumAudioUnitDevice device, string _className) {
    vector<OSType> osTypes = audioUnitParams.getAudioUnitOSTypes(device);
    setup(_unitName, osTypes.at(0), osTypes.at(1), osTypes.at(2), _className);
}

void aumManagedAudioUnit::setup(string _unitName, OSType type, OSType subType, OSType manufacturer,
                                string _className) {
    unitName = _unitName;
    unitSlug = _unitName;
    ofStringReplace(unitSlug, " ", "_");
    unit = ofxAudioUnit(type, subType, manufacturer);
    this->type = stringify(type) == "aumu" ? AU_TYPE_SYNTH : AU_TYPE_UNIT;
    className = _className;
    if(className == "") {
        className = stringify(type, subType, manufacturer);
    }

    ofAddListener(ofEvents().update, this, &aumManagedAudioUnit::update);
}

void aumManagedAudioUnit::update(ofEventArgs& args){
    update();
}

void aumManagedAudioUnit::showUI(string chainName, int chainIndex, int numChains, int unitIndex, int numUnits) {
    x = ofMap(chainIndex, 0, numChains - 1, 0, ofGetScreenWidth() * 0.5);
    y = ofMap(unitIndex, 0, numUnits - 1, 0, ofGetScreenHeight() * 0.5);
    unit.showUI(chainName + ": " +
                unitName + (unitName.length() > 0 ? " " : "") +
                className, x, y);
}

AudioUnitParameterValue aumManagedAudioUnit::get(int param) {
    AudioUnitParameterValue value = 0;
    AudioUnitGetParameter(unit.getUnit(), param, kAudioUnitScope_Global, 0, &value);
    return value;
}

void aumManagedAudioUnit::set(int param, float value) {
    AudioUnitSetParameter(unit.getUnit(), param, kAudioUnitScope_Global, 0, value, 0);
}

void aumManagedAudioUnit::set(int param1, int param2, ofVec2f value) {
    set(param1, value.x);
    set(param2, value.y);
}

void aumManagedAudioUnit::set(int param1, int param2, int param3, ofVec3f value) {
    set(param1, value.x);
    set(param2, value.y);
    set(param3, value.z);
}

ofxAudioUnit* aumManagedAudioUnit::getUnit() {
    return &unit;
}

AudioUnitType aumManagedAudioUnit::getType() {
    return type;
}

string aumManagedAudioUnit::getUnitName() {
    return unitName;
}

string aumManagedAudioUnit::getUnitSlug() {
    return unitSlug;
}

string aumManagedAudioUnit::getClassName() {
    return className;
}

bool aumManagedAudioUnit::isSynth() {
    return type == AU_TYPE_SYNTH;
}

string aumManagedAudioUnit::stringify(OSType type, OSType subType, OSType manufacturer) {
    return stringify(type) + "-" + stringify(subType) + "-" + stringify(manufacturer);
}

string aumManagedAudioUnit::stringify(OSType code) {
    char char4 = code&0xFF;
    char char3 = (code>>8)&0xFF;
    char char2 = (code>>16)&0xFF;
    char char1 = (code>>24)&0xFF;
    return ofToString(char1) + ofToString(char2) + ofToString(char3) + ofToString(char4);
}
