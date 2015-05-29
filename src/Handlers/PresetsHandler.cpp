#include "PresetsHandler.h"

void PresetsHandler::setup(string synthName, ofxAudioUnit* synth){
    this->synthName = synthName;
    this->synth = synth;
    
    selected = false;
    currentPreset = -1;
    this->readFromDisk();
    
    if(presets.size() > 0) {
        currentPreset = presets.size()-1;
        this->load(currentPreset);
    }
}

void PresetsHandler::load(int index) {
    string path = presets.at(index).getAbsolutePath();
    synth->loadCustomPresetAtPath(path);
}

void PresetsHandler::save() {
    string presetName = ofSystemTextBoxDialog("Preset name:");
    if(presetName.length()) {
        ofDirectory dir(synthName);
        synth->saveCustomPresetAtPath(dir.getAbsolutePath() + "/" + presetName + ".aupreset");
        readFromDisk();
        currentPreset = indexOf(presetName);
    }
}

void PresetsHandler::remove() {
    presets.at(currentPreset).remove();
    presets.erase(presets.begin() + currentPreset);
    if(currentPreset >= presets.size()) {
        currentPreset = presets.size() - 1;
    }
}

void PresetsHandler::increment() {
    readFromDisk();
    if(currentPreset == presets.size()-1) currentPreset = 0;
    else currentPreset += 1;
    load(currentPreset);
}

void PresetsHandler::decrement() {
    readFromDisk();
    if(currentPreset == 0) currentPreset = presets.size()-1;
    else currentPreset -= 1;
    load(currentPreset);
}

void PresetsHandler::select() {
    selected = true;
}

void PresetsHandler::deselect() {
    selected = false;
}

void PresetsHandler::readFromDisk() {
    ofDirectory dir(synthName);
    dir.allowExt("aupreset");
    dir.listDir();
    presets = dir.getFiles();
    if(currentPreset > presets.size()-1) {
        currentPreset = presets.size()-1;
    }
}

int PresetsHandler::currentIndex(){
    return currentPreset;
}

string PresetsHandler::report() {
    string icon = selected ? "[*]" : " * ";
    stringstream report;
    report << "PRESETS" << endl;
    
    for(int i = 0; i < presets.size(); i++) {
        report << endl << i << ": " << presets.at(i).getBaseName();
        if(i == currentIndex()) {
            report << " " << icon;
        }
    }
    
    return report.str();
}

int PresetsHandler::indexOf(string presetName) {
    for(int i = 0; i < presets.size(); i++) {
        if(presets.at(i).getBaseName() == presetName) {
            return i;
        }
    }
    cout << "ERROR: Could not find index of preset" << endl;
    return -1;
}