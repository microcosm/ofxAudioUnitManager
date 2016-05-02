#include "ofxManagedAudioUnitMixer.h"

void ofxManagedAudioUnitMixer::setup(string _name){
    name = _name;
}

string ofxManagedAudioUnitMixer::getName(){
    return name;
}

ofxAudioUnitMixer* ofxManagedAudioUnitMixer::getUnit(){
    return &unit;
}