#include "AudioUnitChain.h"

void AudioUnitChain::setup(string _chainName, ofxAudioUnitMixer* _mixer, int _mixerChannel, ofColor _waveColor){
    chainName = _chainName;
    mixer = _mixer;
    mixerChannel = _mixerChannel;
    waveColor = _waveColor;
    className = "AudioUnitChain";
    selected = false;
}

void AudioUnitChain::loadPresets(){
    presetsHandler.setup(chainName);
}

void AudioUnitChain::exit() {
    midiHandler.exit();
}

void AudioUnitChain::toMixer(ofxAudioUnit* chainEndpoint) {
    chainEndpoint->connectTo(tapUnit).connectTo(*mixer, mixerChannel);
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
    return link(unit, "");
}

AudioUnitChain& AudioUnitChain::link(AudioUnitBase* unit, string unitName) {
    unit->setup();
    unit->getType() == AU_TYPE_SYNTH ?
        loadSynth(unit, unitName) : loadUnit(unit, unitName);
    return *this;
}

AudioUnitChain& AudioUnitChain::to(AudioUnitBase* unit) {
    return link(unit);
}

AudioUnitChain& AudioUnitChain::to(AudioUnitBase* unit, string unitName) {
    return link(unit, unitName);
}

void AudioUnitChain::showUI(int chainIndex, int numChains){
    for(int i = 0; i < units.size(); i++) {
        units.at(i)->showUI(chainName, chainIndex, numChains, i, units.size());
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

void AudioUnitChain::sendMidiOn(int note) {
    midiHandler.midi()->sendNoteOn(1, note);
    midiEvents.push_back("[ON: " + ofToString(note) + "]");
}

void AudioUnitChain::sendMidiOff(int note) {
    midiHandler.midi()->sendNoteOff(1, note);
    midiEvents.push_back("[OFF: " + ofToString(note) + "]");
}

ofxAudioUnitTap* AudioUnitChain::tap() {
    return &tapUnit;
}

PresetsHandler* AudioUnitChain::presets() {
    return &presetsHandler;
}

string AudioUnitChain::getUnitReport() {
    report = "";
    for(int i = 0; i < units.size(); i++) {
        report += "[" + units.at(i)->getClassName() + "]->\n";
    }
    return report + "[Mixer]";
}

string AudioUnitChain::getMidiReport() {
    report = "";
    for(int i = 0; i < midiEvents.size(); i++) {
        report += midiEvents.at(i) + " ";
    }
    midiEvents.clear();
    return report;
}

string AudioUnitChain::getClassName() {
    return className;
}

string AudioUnitChain::getName() {
    return chainName;
}

ofColor AudioUnitChain::getColor() {
    return waveColor;
}

void AudioUnitChain::loadUnit(AudioUnitBase* unit, string unitName) {
    unit->setUnitName(unitName);
    presetsHandler.add(unit, unitName);
    units.push_back(unit);
}

void AudioUnitChain::loadSynth(AudioUnitBase* _synth, string unitName) {
    loadUnit(_synth, unitName);
    midiHandler.setup(_synth->getUnit(), chainName);
}