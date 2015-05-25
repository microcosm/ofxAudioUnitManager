#include "BaseChain.h"

void BaseChain::setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor){
    waveColor = _waveColor;
    selected = false;
}

void BaseChain::update(){
    tap.getLeftWaveform(waveform, ofGetWidth(), ofGetHeight());
}

void BaseChain::draw(){
    ofSetColor(waveColor);
    ofSetLineWidth(1);
    waveform.draw();
}

void BaseChain::exit() {
    midiHandler.exit();
}

string BaseChain::report() {
    string report = "";
    report.append(midiHandler.report());
    report.append("\n\n");
    report.append(presets.report());
    return report;
}

void BaseChain::load(BaseUnit* unit) {
    unit->setup();
    units.push_back(unit);
}

void BaseChain::showUI(){
    for(int i = 0; i < units.size(); i++) {
        units.at(i)->showUI();
    }
}

void BaseChain::savePresets() {
    presets.save();
}

void BaseChain::incrementPreset() {
    presets.increment();
}

void BaseChain::decrementPreset() {
    presets.decrement();
}

bool BaseChain::isSelected() {
    return selected;
}

void BaseChain::select() {
    selected = true;
    presets.select();
}

void BaseChain::deselect() {
    selected = false;
    presets.deselect();
}

void BaseChain::toggleSelected() {
    selected = !selected;
    selected ? presets.select() : presets.deselect();
}

ofxMidiOut* BaseChain::midi() {
    return midiHandler.midi();
}