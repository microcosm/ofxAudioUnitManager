#include "PresetsHandler.h"

void PresetsHandler::setup(string _chainName){
    chainName = _chainName;
    selected = false;
    currentPreset = -1;
    anyExtension = "";
    presetExtension = "aupreset";
    readFromDisk();
    
    if(presets.size() > 0) {
        currentPreset = presets.size()-1;
        load(currentPreset);
    }
}

void PresetsHandler::load(int presetIndex) {
//    string path = presets.at(presetIndex).getAbsolutePath();
//    synth->loadCustomPresetAtPath(path);
}

void PresetsHandler::add(AudioUnitBase* unit) {
    units.push_back(unit);
}

void PresetsHandler::save() {
    string presetName = ofSystemTextBoxDialog("Preset name:");
    if(presetName.length()) {
        string presetPath = path(presetName);
        dir.createDirectory(presetPath);
        for(int i = 0; i < units.size(); i++) {
            string presetFilename = filename(i, units.at(i));
            units.at(i)->get()->saveCustomPresetAtPath(presetPath + presetFilename);
        }
        readFromDisk();
        currentPreset = indexOf(presetName);
    }
}

void PresetsHandler::rename() {
    string presetName = ofSystemTextBoxDialog("New name:");
    if(presetName.length()) {
        ofDirectory dir(chainName);
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
    clearPresets();
    vector<ofFile> chainDirContents = dirContents(chainName, anyExtension);

    for(int i = 0; i < chainDirContents.size(); i++) {
        if(chainDirContents.at(i).isDirectory()) {
            string presetName = chainDirContents.at(i).getFileName();
            presetNames.push_back(presetName);
            presets.push_back(dirContents(chainName + "/" + presetName, presetExtension));
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
        if(presetNames.at(i) == presetName) {
            return i;
        }
    }
    cout << "ERROR: Could not find index of preset" << endl;
    return -1;
}

void PresetsHandler::ensureValidIndex() {
    if(currentPreset > presets.size() - 1) {
        currentPreset = presets.size() - 1;
    }
}

vector<ofFile> PresetsHandler::dirContents(string path, string extensions) {
    dir.allowExt(extensions);
    dir.listDir(path);
    return dir.getFiles();
}

void PresetsHandler::clearPresets() {
    presets.clear();
    presetNames.clear();
}

string PresetsHandler::path(string presetName) {
    ofDirectory dir(chainName);
    return dir.getAbsolutePath() + "/" + presetName + "/";
}

string PresetsHandler::filename(int index, AudioUnitBase* unit) {
    return ofToString(index) + "_" + unit->getName() + "." + presetExtension;
}