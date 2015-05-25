#include "AlchemyChain.h"

void AlchemyChain::setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor){
    AudioUnitChain::setup(name, mixer, mixerChannel, _waveColor);
    
    load(&alchemy);
    load(&filter);
    load(&reverb);
    load(&delay);
    
    ofxAudioUnit* synth = alchemy.get();
    presets.setup(name, synth);
    midiHandler.setup(synth, name);
    
    synth->connectTo(*filter.get())
      //.connectTo(*reverb.get())
      //.connectTo(*delay.get())
      .connectTo(tap)
      .connectTo(*mixer, mixerChannel);
}

void AlchemyChain::delayTime(float val) {
    reverb.setParameter(DelayTime, val);
}

void AlchemyChain::reverbDryWet(float val) {
    reverb.setParameter(kReverbParam_DryWetMix, val);
}

void AlchemyChain::filterCutoff(float val) {
    filter.setParameter(kLowPassParam_CutoffFrequency, val);
}

void AlchemyChain::alchemyRemixX(float val) {
    alchemy.setParameter(RemixX, val);
}

void AlchemyChain::alchemyRemixY(float val) {
    alchemy.setParameter(RemixY, val);
}

void AlchemyChain::showAlchemyUI() {
    alchemy.showUI();
}

void AlchemyChain::showFilterUI() {
    filter.showUI();
}

void AlchemyChain::showReverbUI() {
    reverb.showUI();
}