#include "ofxAudioUnitChain.h"

void ofxAudioUnitChain::setup(string _chainName, ofxAudioUnitMixer* _mixer, int _mixerChannel, ofColor _waveColor){
    chainName = _chainName;
    mixer = _mixer;
    mixerChannel = _mixerChannel;
    waveColor = _waveColor;
    className = "ofxAudioUnitChain";
    selected = false;
}

void ofxAudioUnitChain::loadPresets(){
    presetsHandler.setup(chainName);
}

void ofxAudioUnitChain::exit() {
    midiHandler.exit();
}

ofxAudioUnitChain& ofxAudioUnitChain::toMixer(ofxAudioUnit* chainEndpoint) {
    chainEndpoint->connectTo(tapUnit).connectTo(*mixer, mixerChannel);
    return *this;
}

ofxAudioUnitChain& ofxAudioUnitChain::toMixer() {
    ofxAudioUnit* unitEndpoint = units.at(0)->getUnit();

    for(int i = 1; i < units.size(); i++) {
        unitEndpoint->connectTo(*units.at(i)->getUnit());
        unitEndpoint = units.at(i)->getUnit();
    }

    toMixer(unitEndpoint);
    loadPresets();
    return *this;
}

ofxAudioUnitChain& ofxAudioUnitChain::link(ofxManagedAudioUnit* unit) {
    return link(unit, "");
}

ofxAudioUnitChain& ofxAudioUnitChain::link(ofxManagedAudioUnit* unit, string unitName) {
    if(!unit->hasBeenSetup()) {
        unit->setup();
    }
    unit->getType() == AU_TYPE_SYNTH ?
        loadSynth(unit, unitName) : loadUnit(unit, unitName);
    return *this;
}

ofxAudioUnitChain& ofxAudioUnitChain::to(ofxManagedAudioUnit* unit) {
    return link(unit);
}

ofxAudioUnitChain& ofxAudioUnitChain::to(ofxManagedAudioUnit* unit, string unitName) {
    return link(unit, unitName);
}

void ofxAudioUnitChain::showUI(int chainIndex, int numChains){
    for(int i = 0; i < units.size(); i++) {
        units.at(i)->showUI(chainName, chainIndex, numChains, i, units.size());
    }
}

void ofxAudioUnitChain::showSynthUI(int chainIndex, int numChains){
    for(int i = 0; i < units.size(); i++) {
        if(units.at(i)->isSynth()){
            units.at(i)->showUI(chainName, chainIndex, numChains, i, units.size());
        }
    }
}

bool ofxAudioUnitChain::isSelected() {
    return selected;
}

void ofxAudioUnitChain::select() {
    selected = true;
    presetsHandler.select();
}

void ofxAudioUnitChain::deselect() {
    selected = false;
    presetsHandler.deselect();
}

ofxMidiOut* ofxAudioUnitChain::midi() {
    return midiHandler.midi();
}

void ofxAudioUnitChain::sendMidiOn(int note) {
    midiHandler.midi()->sendNoteOn(1, note);
    midiEvents.push_back("[ON: " + ofToString(note) + "]");
}

void ofxAudioUnitChain::sendMidiOff(int note) {
    midiHandler.midi()->sendNoteOff(1, note);
    midiEvents.push_back("[OFF: " + ofToString(note) + "]");
}

ofxAudioUnitTap* ofxAudioUnitChain::tap() {
    return &tapUnit;
}

PresetsHandler* ofxAudioUnitChain::presets() {
    return &presetsHandler;
}

string ofxAudioUnitChain::getUnitReport() {
    report = "";
    for(int i = 0; i < units.size(); i++) {
        report += "[" + units.at(i)->getClassName() + "]->\n";
    }
    return report + "[Mixer]";
}

string ofxAudioUnitChain::getMidiReport() {
    report = "";
    for(int i = 0; i < midiEvents.size(); i++) {
        report += midiEvents.at(i) + " ";
    }
    midiEvents.clear();
    return report;
}

string ofxAudioUnitChain::getClassName() {
    return className;
}

string ofxAudioUnitChain::getName() {
    return chainName;
}

ofColor ofxAudioUnitChain::getColor() {
    return waveColor;
}

void ofxAudioUnitChain::loadUnit(ofxManagedAudioUnit* unit, string unitName) {
    unit->setUnitName(unitName);
    presetsHandler.add(unit, unitName);
    units.push_back(unit);
}

void ofxAudioUnitChain::loadSynth(ofxManagedAudioUnit* _synth, string unitName) {
    loadUnit(_synth, unitName);
    midiHandler.setup(_synth->getUnit(), chainName);
}