#include "SamplerChain.h"

void SamplerChain::setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor){
    AudioUnitChain::setup(name, mixer, mixerChannel, _waveColor);
    className = "SamplerChain";
    
    //Load units in order
    load(&sampler);
    load(&filter);
    load(&reverb);
    sendOut();
}

Sampler* SamplerChain::getSynth() {
    return &sampler;
}

LowPassFilter* SamplerChain::getFilter(){
    return &filter;
}

Reverb* SamplerChain::getReverb(){
    return &reverb;
}