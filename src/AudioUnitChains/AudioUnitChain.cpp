#include "AudioUnitChain.h"

void AudioUnitChain::setup(string _name, ofxAudioUnitMixer* _mixer, int _mixerChannel, ofColor _waveColor){
    name = _name;
    mixer = _mixer;
    mixerChannel = _mixerChannel;
    waveColor = _waveColor;
    selected = false;
    presets.setup(name);
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
    unit->getType() == AU_TYPE_SYNTH ?
        loadSynth(unit) : loadUnit(unit);
}

void AudioUnitChain::loadUnit(AudioUnitBase* unit) {
    unit->setup();
    presets.add(unit);
    units.push_back(unit);
}

void AudioUnitChain::loadSynth(AudioUnitBase* _synth) {
    loadUnit(_synth);
    midiHandler.setup(_synth->get(), name);
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

string AudioUnitChain::getUnitReport() {
    unitReport = "";
    for(int i = 0; i < units.size(); i++) {
        unitReport += "[" + units.at(units.size() - i - 1)->getClassName() + "]->\n";
    }
    return unitReport + "[Mixer]";
}

string AudioUnitChain::getClassName() {
    return className;
}

string AudioUnitChain::getName() {
    return name;
}

ofColor AudioUnitChain::getColor() {
    return waveColor;
}