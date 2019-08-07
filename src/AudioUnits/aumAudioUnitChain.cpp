#include "aumAudioUnitChain.h"

void aumAudioUnitChain::setup(string _chainName, ofxAudioUnitMixer* _mixer, aumManagedAudioUnit* _compressor, int _mixerChannel, ofColor _waveColor){
    chainName = _chainName;
    mixer = _mixer;
    compressor = _compressor;
    mixerChannel = _mixerChannel;
    waveColor = _waveColor;
    className = "aumAudioUnitChain";
    selected = false;
}

void aumAudioUnitChain::loadPresets(){
    presetsHandler.setup(chainName, mixer, compressor);
}

void aumAudioUnitChain::exit() {
    midiHandler.exit();
}

aumAudioUnitChain& aumAudioUnitChain::toMixer(ofxAudioUnit* chainEndpoint) {
    chainEndpoint->connectTo(tapUnit).connectTo(*mixer, mixerChannel);
    return *this;
}

aumAudioUnitChain& aumAudioUnitChain::toMixer() {
    ofxAudioUnit* unitEndpoint = units.at(0)->getUnit();

    for(int i = 1; i < units.size(); i++) {
        unitEndpoint->connectTo(*units.at(i)->getUnit());
        unitEndpoint = units.at(i)->getUnit();
    }

    toMixer(unitEndpoint);
    loadPresets();
    return *this;
}

aumAudioUnitChain& aumAudioUnitChain::link(aumManagedAudioUnit* unit) {
    unit->getType() == AU_TYPE_SYNTH ?
        loadSynth(unit) : loadUnit(unit);
    return *this;
}

aumAudioUnitChain& aumAudioUnitChain::to(aumManagedAudioUnit* unit) {
    return link(unit);
}

void aumAudioUnitChain::showUI(int chainIndex, int numChains){
    for(int i = 0; i < units.size(); i++) {
        units.at(i)->showUI(chainName, chainIndex, numChains, i, units.size());
    }
}

void aumAudioUnitChain::showSynthUI(int chainIndex, int numChains){
    for(int i = 0; i < units.size(); i++) {
        if(units.at(i)->isSynth()){
            units.at(i)->showUI(chainName, chainIndex, numChains, i, units.size());
        }
    }
}

bool aumAudioUnitChain::isSelected() {
    return selected;
}

void aumAudioUnitChain::select() {
    selected = true;
    presetsHandler.select();
}

void aumAudioUnitChain::deselect() {
    selected = false;
    presetsHandler.deselect();
}

void aumAudioUnitChain::sendMidiOn(int note) {
    midi.sendNoteOn(1, note);
    midiEvents.push_back("[ON: " + ofToString(note) + "]");
}

void aumAudioUnitChain::sendMidiOff(int note) {
    midi.sendNoteOff(1, note);
    midiEvents.push_back("[OFF: " + ofToString(note) + "]");
}

ofxAudioUnitTap* aumAudioUnitChain::tap() {
    return &tapUnit;
}

aumPresets* aumAudioUnitChain::presets() {
    return &presetsHandler;
}

string aumAudioUnitChain::getUnitReport() {
    report = "";
    for(int i = 0; i < units.size(); i++) {
        report += (i > 0 ? "" : "") + ("\"" + units.at(i)->getUnitName() + "\" ->\n");
    }
    return report + " Compressor/Mixer";
}

string aumAudioUnitChain::getMidiReport() {
    report = "";
    for(int i = 0; i < midiEvents.size(); i++) {
        report += midiEvents.at(i) + " ";
    }
    midiEvents.clear();
    return report;
}

string aumAudioUnitChain::getClassName() {
    return className;
}

string aumAudioUnitChain::getName() {
    return chainName;
}

ofColor aumAudioUnitChain::getColor() {
    return waveColor;
}

void aumAudioUnitChain::loadUnit(aumManagedAudioUnit* unit) {
    presetsHandler.add(unit);
    units.push_back(unit);
}

void aumAudioUnitChain::loadSynth(aumManagedAudioUnit* _synth) {
    loadUnit(_synth);
    midiHandler.setup(_synth->getUnit(), &midi, "openFrameworks: " + chainName);
}
