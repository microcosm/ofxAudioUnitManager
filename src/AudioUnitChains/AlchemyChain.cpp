#include "AlchemyChain.h"

void AlchemyChain::setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor){
    AudioUnitChain::setup(name, mixer, mixerChannel, _waveColor);
    className = "AlchemyChain";

    //Load units in order
    load(&alchemy);
    load(&filter);
    load(&reverb);
    sendOut();
}

AlchemyPlayer* AlchemyChain::getSynth() {
    return &alchemy;
}

LowPassFilter* AlchemyChain::getFilter(){
    return &filter;
}

Reverb* AlchemyChain::getReverb(){
    return &reverb;
}