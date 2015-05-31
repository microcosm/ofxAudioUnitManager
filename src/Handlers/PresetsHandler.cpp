#include "PresetsHandler.h"

void PresetsHandler::setup(string _chainName){
    chainName = _chainName;
    selected = false;
    currentPreset = -1;
    storageDir = "AudioUnitPresets/";
    anyExtension = "";
    presetExtension = "aupreset";
    ensureDirectories();
    readFromDisk();
    
    if(presets.size() > 0) {
        currentPreset = 0;
        load(currentPreset);
    }
}

void PresetsHandler::load(int presetIndex) {
    string presetPath = path(presetNames.at(presetIndex));
    for(int i = 0; i < units.size(); i++) {
        string presetFilename = filename(i, units.at(i));
        units.at(i)->get()->loadCustomPresetAtPath(presetPath + presetFilename);
    }
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
    if(currentPreset > -1) {
        string newPresetName = ofSystemTextBoxDialog("New name:");
        if(newPresetName.length()) {
            string newPresetPath = path(newPresetName);
            for(int i = 0; i < units.size(); i++) {
                string newPresetFilename = filename(i, units.at(i));
                presets.at(currentPreset).at(i).renameTo(newPresetPath + newPresetFilename);
            }
            string oldPresetPath = path(presetNames.at(currentPreset));
            dir.removeDirectory(oldPresetPath, true);
            presetNames[currentPreset] = newPresetName;
            readFromDisk();
            currentPreset = indexOf(newPresetName);
        }
    }
}

void PresetsHandler::remove() {
    if(currentPreset > -1) {
        dir.removeDirectory(path(presetNames.at(currentPreset)), true);
        presets.erase(presets.begin() + currentPreset);
        presetNames.erase(presetNames.begin() + currentPreset);
        readFromDisk();
        ensureValidIndex();
    }
}

void PresetsHandler::increment() {
    if(currentPreset > -1) {
        readFromDisk();
        currentPreset = currentPreset == presets.size() - 1 ? currentPreset = 0 : currentPreset + 1;
        load(currentPreset);
    }
}

void PresetsHandler::decrement() {
    if(currentPreset > -1) {
        readFromDisk();
        currentPreset = currentPreset == 0 ? presets.size() - 1 : currentPreset - 1;
        load(currentPreset);
    }
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
    string icon = selected ? "[*]" : "[ ]";
    stringstream report;
    report << "PRESETS" << endl << "-------";
    
    for(int i = 0; i < presetNames.size(); i++) {
        report << endl << trim(presetNames.at(i));
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
    dir.listDir(storageDir + path);
    return dir.getFiles();
}

void PresetsHandler::clearPresets() {
    presets.clear();
    presetNames.clear();
}

string PresetsHandler::path(string presetName) {
    ofDirectory dir(storageDir + chainName);
    return dir.getAbsolutePath() + "/" + presetName + "/";
}

string PresetsHandler::filename(int index, AudioUnitBase* unit) {
    return ofToString(index) + "_" + unit->getClassName() + "." + presetExtension;
}

string PresetsHandler::trim(string presetName) {
    return presetName.length() < 22 ? presetName : presetName.substr(0, 18) + "...";
}

void PresetsHandler::ensureDirectories() {
    ofDirectory storage(storageDir);
    if(!storage.exists()) {
        storage.create();
    }
    ofDirectory chain(storageDir + chainName);
    if(!chain.exists()) {
        chain.create();
    }
}