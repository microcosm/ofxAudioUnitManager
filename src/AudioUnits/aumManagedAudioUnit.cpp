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
}

void aumManagedAudioUnit::showUI(string chainName, int chainIndex, int numChains, int unitIndex, int numUnits) {
    x = ofMap(chainIndex, 0, numChains - 1, 0, ofGetScreenWidth() * 0.5);
    y = ofMap(unitIndex, 0, numUnits - 1, 0, ofGetScreenHeight() * 0.5);
    unit.showUI(chainName + ": " +
                unitName + (unitName.length() > 0 ? " " : "") +
                className, x, y);
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

void aumManagedAudioUnit::printParamsAsConstants(string unitPrefix) {
    vector<AudioUnitParameterInfo> paramList = unit.getParameterList();
    unnamedCount = 0;

    cout << endl << "============================" << endl << endl;
    cout << "#pragma once" << endl << endl;

    for(int i = 0; i < paramList.size(); i++) {
        AudioUnitParameterInfo& p = paramList[i];
        string freindlyName = p.name;
        if(freindlyName.size() > 0) {
            freindlyName = ofToLower(freindlyName);
            ofStringReplace(freindlyName, " ", "_");
            ofStringReplace(freindlyName, ".", "_");
            ofStringReplace(freindlyName, "-", "_");
            ofStringReplace(freindlyName, ".", "_");
            ofStringReplace(freindlyName, "(", "_");
            ofStringReplace(freindlyName, ")", "_");
            ofStringReplace(freindlyName, "&", "_");
            ofStringReplace(freindlyName, ":", "_");
            ofStringReplace(freindlyName, "/", "_");
            ofStringReplace(freindlyName, "\\", "_");
            ofStringReplace(freindlyName, ">", "GT");
            ofStringReplace(freindlyName, "#", "_sharp");
            ofStringReplace(freindlyName, "<", "LT");
            ofStringReplace(freindlyName, "*", "MULTIPLY");
            ofStringReplace(freindlyName, "____", "_");
            ofStringReplace(freindlyName, "___", "_");
            ofStringReplace(freindlyName, "__", "_");

            cout << "//" << p.name << endl;
        } else {
            freindlyName = "unnamed" + ofToString(++unnamedCount);
            cout << "//No name found" << endl;
        }

        cout << "//min: " << p.minValue << ", max: " << p.maxValue << ", default: " << p.defaultValue << endl;
        cout << "const static int " << unitPrefix << "_" << freindlyName << " = " << i << ";" << endl << endl;
    }

    cout << endl;
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
