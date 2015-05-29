#include "PresetsHandler.h"

void PresetsHandler::setup(string synthName){
    this->synthName = synthName;
    
    selected = false;
    currentPreset = -1;
    this->readFromDisk();
    
    if(presets.size() > 0) {
        currentPreset = presets.size()-1;
        this->load(currentPreset);
    }
}

void PresetsHandler::load(int index) {
//    string path = presets.at(index).getAbsolutePath();
//    synth->loadCustomPresetAtPath(path);
}

void PresetsHandler::add(ofxAudioUnit* unit) {
    units.push_back(unit);
}

void PresetsHandler::save() {
    string presetName = ofSystemTextBoxDialog("Preset name:");
    if(presetName.length()) {
        ofDirectory dir(synthName);
//        synth->saveCustomPresetAtPath(dir.getAbsolutePath() + "/" + presetName + ".aupreset");
        readFromDisk();
        currentPreset = indexOf(presetName);
    }
}

void PresetsHandler::rename() {
    string presetName = ofSystemTextBoxDialog("New name:");
    if(presetName.length()) {
        ofDirectory dir(synthName);
        string newPath = dir.getAbsolutePath() + "/" + presetName + ".aupreset";
//        presets.at(currentPreset).renameTo(newPath);
        readFromDisk();
        currentPreset = indexOf(presetName);
    }
}

void PresetsHandler::remove() {
//    presets.at(currentPreset).remove();
//    presets.erase(presets.begin() + currentPreset);
    ensureValidIndex();
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
    presets.clear();
    dir.listDir(synthName);
    vector<ofFile> chainDirContents = dir.getFiles();

    for(int i = 0; i < chainDirContents.size(); i++) {
        if(chainDirContents.at(i).isDirectory()) {
            string presetName = chainDirContents.at(i).getFileName();
            dir.allowExt("aupreset");
            dir.listDir(synthName + "/" + presetName);
            presetNames.push_back(presetName);
            presets.push_back(dir.getFiles());
        }
    }
    ensureValidIndex();
}

int PresetsHandler::currentIndex(){
    return currentPreset;
}

string PresetsHandler::report() {
    string icon = selected ? "[*]" : " * ";
    stringstream report;
    report << "PRESETS" << endl;
    
    for(int i = 0; i < presetNames.size(); i++) {
        report << endl << i << ": " << presetNames.at(i);
        if(i == currentIndex()) {
            report << " " << icon;
        }
    }
    
    return report.str();
}

int PresetsHandler::indexOf(string presetName) {
    for(int i = 0; i < presets.size(); i++) {
/*        if(presets.at(i).getBaseName() == presetName) {
            return i;
        }*/
    }
    cout << "ERROR: Could not find index of preset" << endl;
    return -1;
}

void PresetsHandler::ensureValidIndex() {
    if(currentPreset > presets.size() - 1) {
        currentPreset = presets.size() - 1;
    }
}