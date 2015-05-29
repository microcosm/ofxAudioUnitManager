#include "AudioUnitChain.h"

void AudioUnitChain::setup(string _name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor){
    waveColor = _waveColor;
    selected = false;
    name = _name;
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