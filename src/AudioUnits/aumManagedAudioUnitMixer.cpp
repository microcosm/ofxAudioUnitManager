#include "aumManagedAudioUnitMixer.h"

void aumManagedAudioUnitMixer::setup(string _name){
    name = _name;
}

string aumManagedAudioUnitMixer::getName(){
    return name;
}

ofxAudioUnitMixer* aumManagedAudioUnitMixer::getUnit(){
    return &unit;
}
