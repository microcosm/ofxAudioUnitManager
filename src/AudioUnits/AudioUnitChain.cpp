#include "AudioUnitChain.h"

void AudioUnitChain::setup(string _name, ofxAudioUnitMixer* _mixer, int _mixerChannel, ofColor _waveColor){
    name = _name;
    mixer = _mixer;
    mixerChannel = _mixerChannel;
    waveColor = _waveColor;
    className = "AudioUnitChain";
    selected = false;
}

void AudioUnitChain::loadPresets(){
    presetsHandler.setup(name);
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

void AudioUnitChain::toMixer(ofxAudioUnit* chainEndpoint) {
    chainEndpoint->connectTo(tap).connectTo(*mixer, mixerChannel);
}

void AudioUnitChain::toMixer() {
    ofxAudioUnit* unitEndpoint = units.at(0)->getUnit();

    for(int i = 1; i < units.size(); i++) {
        unitEndpoint->connectTo(*units.at(i)->getUnit());
        unitEndpoint = units.at(i)->getUnit();
    }

    toMixer(unitEndpoint);
}

AudioUnitChain& AudioUnitChain::link(AudioUnitBase* unit) {
    unit->setup();
    unit->getType() == AU_TYPE_SYNTH ?
        loadSynth(unit) : loadUnit(unit);
    return *this;
}

AudioUnitChain& AudioUnitChain::to(AudioUnitBase* unit) {
    return link(unit);
}

void AudioUnitChain::showUI(){
    for(int i = 0; i < units.size(); i++) {
        units.at(i)->showUI();
    }
}

bool AudioUnitChain::isSelected() {
    return selected;
}

void AudioUnitChain::select() {
    selected = true;
    presetsHandler.select();
}

void AudioUnitChain::deselect() {
    selected = false;
    presetsHandler.deselect();
}

ofxMidiOut* AudioUnitChain::midi() {
    return midiHandler.midi();
}

PresetsHandler* AudioUnitChain::presets() {
    return &presetsHandler;
}

string AudioUnitChain::getUnitReport() {
    unitReport = "";
    for(int i = 0; i < units.size(); i++) {
        unitReport += "[" + units.at(i)->getClassName() + "]->\n";
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

void AudioUnitChain::loadUnit(AudioUnitBase* unit) {
    presetsHandler.add(unit);
    units.push_back(unit);
}

void AudioUnitChain::loadSynth(AudioUnitBase* _synth) {
    loadUnit(_synth);
    midiHandler.setup(_synth->getUnit(), name);
}