#include "AudioUnitChain.h"

void AudioUnitChain::setup(string _name, ofxAudioUnitMixer* _mixer, int _mixerChannel, ofColor _waveColor){
    name = _name;
    mixer = _mixer;
    mixerChannel = _mixerChannel;
    waveColor = _waveColor;
    selected = false;
}

void AudioUnitChain::update(){
    tap.getLeftWaveform(waveform, ofGetWidth(), ofGetHeight());
}

void AudioUnitChain::drawWaveform(){
    ofSetColor(waveColor);
    ofSetLineWidth(1);
    waveform.draw();
}

void AudioUnitChain::exit() {
    midiHandler.exit();
}

void AudioUnitChain::sendOut(ofxAudioUnit* chainEndpoint) {
    chainEndpoint->connectTo(tap).connectTo(*mixer, mixerChannel);
}

void AudioUnitChain::load(AudioUnitBase* unit) {
    unit->setup();
    units.push_back(unit);
}

void AudioUnitChain::showUI(){
    for(int i = 0; i < units.size(); i++) {
        units.at(i)->showUI();
    }
}

void AudioUnitChain::savePresets() {
    presets.save();
}

void AudioUnitChain::deletePreset() {
    presets.remove();
}

void AudioUnitChain::renamePreset() {
    presets.rename();
}

void AudioUnitChain::incrementPreset() {
    presets.increment();
}

void AudioUnitChain::decrementPreset() {
    presets.decrement();
}

bool AudioUnitChain::isSelected() {
    return selected;
}

void AudioUnitChain::select() {
    selected = true;
    presets.select();
}

void AudioUnitChain::deselect() {
    selected = false;
    presets.deselect();
}

ofxMidiOut* AudioUnitChain::midi() {
    return midiHandler.midi();
}

PresetsHandler* AudioUnitChain::getPresets() {
    return &presets;
}

string AudioUnitChain::getName() {
    return name;
}