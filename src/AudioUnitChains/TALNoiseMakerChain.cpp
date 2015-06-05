#include "TALNoiseMakerChain.h"

void TALNoiseMakerChain::setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor){
    AudioUnitChain::setup(name, mixer, mixerChannel, _waveColor);
    className = "TALNoiseMakerChain";
    
    //Load units in order
    load(&noiseMaker);
    load(&filter);
    load(&reverb);
    sendOut();
}

TALNoiseMaker* TALNoiseMakerChain::getSynth() {
    return &noiseMaker;
}

LowPassFilter* TALNoiseMakerChain::getFilter(){
    return &filter;
}

Reverb* TALNoiseMakerChain::getReverb(){
    return &reverb;
}