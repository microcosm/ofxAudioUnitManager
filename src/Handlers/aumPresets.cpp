#include "aumPresets.h"

void aumPresets::setup(string _chainName, ofxAudioUnitMixer* _mixer, aumManagedAudioUnit* _compressor){
    chainName = _chainName;
    selected = false;
    currentPreset = -1;
    lastSaved = -1;
    lastSaveTimer = 0;
    lastSaveTimeout = 60;
    storageDir = "AudioUnitPresets/";
    trashDir = ".trash/";
    mixerName = "Mixer";
    anyExtension = "";
    presetExtension = "aupreset";
    mixer = _mixer;
    compressor = _compressor;
    ensureDirectories();
    readFromDisk();

    ofDirectory dir(storageDir);
    storagePath = dir.getAbsolutePath() + "/";

    if(presets.size() > 0) {
        currentPreset = 0;
        load(currentPreset);
    }

    loadMasterUnits();
}

void aumPresets::load(int presetIndex) {
    string presetPath = path(presetNames.at(presetIndex));
    for(int i = 0; i < units.size(); i++) {
        string presetFullPath = presetPath + filename(unitSlugs.at(i));
        if(!ofFile(presetFullPath).exists()) {
            units.at(i)->getUnit()->saveCustomPresetAtPath(presetFullPath);
        }
        units.at(i)->getUnit()->loadCustomPresetAtPath(presetFullPath);
    }
}

void aumPresets::add(aumManagedAudioUnit* unit) {
    units.push_back(unit);
    unitSlugs.push_back(unit->getUnitSlug());
}

void aumPresets::saveNew() {
    string presetName = ofSystemTextBoxDialog("Preset name:");
    if(validateName(presetName)) {
        save(presetName);
    }
}

void aumPresets::saveOverwrite() {
    if(currentPreset > -1 && presetNames.size() >= currentPreset + 1) {
        string presetName = presetNames.at(currentPreset);
        trash();
        save(presetName);
    }
}

void aumPresets::rename() {
    if(currentPreset > -1) {
        string newPresetName = ofSystemTextBoxDialog("New name:", presetNames.at(currentPreset));
        if(validateName(newPresetName, currentPreset)) {
            string newPresetPath = path(newPresetName);
            for(int i = 0; i < units.size(); i++) {
                string newPresetFilename = filename(unitSlugs.at(i));
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

void aumPresets::trash() {
    if(currentPreset > -1) {
        ofDirectory presetDir(path(presetNames.at(currentPreset)));
        presetDir.renameTo(newTrashPath(presetNames.at(currentPreset)));
        presets.erase(presets.begin() + currentPreset);
        presetNames.erase(presetNames.begin() + currentPreset);
        readFromDisk();
        ensureValidIndex();
    }
}

void aumPresets::increment() {
    if(currentPreset > -1) {
        readFromDisk();
        currentPreset = currentPreset == presets.size() - 1 ? currentPreset = 0 : currentPreset + 1;
        load(currentPreset);
    }
}

void aumPresets::decrement() {
    if(currentPreset > -1) {
        readFromDisk();
        currentPreset = currentPreset == 0 ? presets.size() - 1 : currentPreset - 1;
        load(currentPreset);
    }
}

void aumPresets::select() {
    selected = true;
}

void aumPresets::deselect() {
    selected = false;
}

void aumPresets::readFromDisk() {
    clearPresets();
    vector<ofFile> chainDirContents = dirContents(chainName, anyExtension);
    
    for(int i = 0; i < chainDirContents.size(); i++) {
        if(chainDirContents.at(i).isDirectory()) {
            string presetName = chainDirContents.at(i).getFileName();
            presetNames.push_back(presetName);
            loadPresetsInChainOrder(presetName);
        }
    }
    ensureValidIndex();
}

void aumPresets::loadPresetsInChainOrder(string presetName) {
    vector<ofFile> files;
    for(int i = 0; i < units.size(); i++) {
        files.push_back(ofFile(path(presetName) + filename(unitSlugs.at(i))));
    }
    presets.push_back(files);
}

int aumPresets::currentIndex(){
    return currentPreset;
}

string aumPresets::report() {
    string icon = selected ? "[*]" : "[ ]";
    stringstream report;
    report << "PRESETS" << endl << "-------";
    
    for(int i = 0; i < presetNames.size(); i++) {
        report << endl << trim(presetNames.at(i));
        if(i == currentIndex()) {
            report << " " << icon;
        }
        if(i == lastSaved) {
            report << " <- saved";
            lastSaveTimer++;
            if(lastSaveTimer >= lastSaveTimeout) {
                lastSaveTimer = 0;
                lastSaved = -1;
            }
        }
    }
    
    return report.str();
}

int aumPresets::indexOf(string presetName) {
    for(int i = 0; i < presets.size(); i++) {
        if(presetNames.at(i) == presetName) {
            return i;
        }
    }
    cout << "ERROR: Could not find index of preset" << endl;
    return -1;
}

void aumPresets::ensureValidIndex() {
    if(currentPreset > presets.size() - 1) {
        currentPreset = presets.size() - 1;
    }
}

vector<ofFile> aumPresets::dirContents(string path, string extensions) {
    dir.allowExt(extensions);
    dir.listDir(storageDir + path);
    return dir.getFiles();
}

void aumPresets::clearPresets() {
    presets.clear();
    presetNames.clear();
}

string aumPresets::path(string presetName) {
    ofDirectory dir(storageDir + chainName);
    return dir.getAbsolutePath() + "/" + presetName + "/";
}

string aumPresets::newTrashPath(string presetName) {
    string timeIndexedTrashDir = storageDir + trashDir + ofGetTimestampString() + "/";
    ofDirectory timedTrashDir(timeIndexedTrashDir);
    timedTrashDir.create();
    ofDirectory trashChainDir(timeIndexedTrashDir + chainName);
    trashChainDir.create();
    return trashChainDir.getAbsolutePath() + "/" + presetName + "/";
}

string aumPresets::filename(string unitSlug) {
    return unitSlug + "." + presetExtension;
}

string aumPresets::trim(string presetName) {
    return presetName.length() < 22 ? presetName : presetName.substr(0, 18) + "...";
}

void aumPresets::ensureDirectories() {
    ofDirectory storage(storageDir);
    if(!storage.exists()) {
        storage.create();
    }
    ofDirectory trash(storageDir + trashDir);
    if(!trash.exists()) {
        trash.create();
    }
    ofDirectory chain(storageDir + chainName);
    if(!chain.exists()) {
        chain.create();
    }
}

string allowableCharacters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789-";
bool aumPresets::validateName(string newPresetName, int alertDialogException) {
    bool nameIsUnique = true;
    for(int i = 0; i < presetNames.size(); i++) {
        if(ofToUpper(newPresetName) == ofToUpper(presetNames.at(i))) {
            nameIsUnique = false;
            if(i != alertDialogException) {
                ofSystemAlertDialog("Name '" + newPresetName + "' already in use on this chain");
            }
        }
    }
    bool nameIsValid = true;
    if(!(newPresetName.length() > 0 && newPresetName.find_first_not_of(allowableCharacters) == std::string::npos)) {
        nameIsValid = false;
        ofSystemAlertDialog("Name '" + newPresetName + "' is not valid");
    }
    return nameIsValid && nameIsUnique;
}

void aumPresets::save(string presetName) {
    string presetPath = path(presetName);
    dir.createDirectory(presetPath);
    for(int i = 0; i < units.size(); i++) {
        string presetFilename = filename(unitSlugs.at(i));
        units.at(i)->getUnit()->saveCustomPresetAtPath(presetPath + presetFilename);
    }
    saveMasterUnits();
    readFromDisk();
    currentPreset = indexOf(presetName);
    lastSaved = currentPreset;
}

void aumPresets::saveMasterUnits(){
    mixer->saveCustomPresetAtPath(storagePath + filename(mixerName));
    compressor->getUnit()->saveCustomPresetAtPath(storagePath + filename(compressor->getUnitSlug()));
}

void aumPresets::loadMasterUnits(){
    mixer->loadCustomPresetAtPath(storagePath + filename(mixerName));
    compressor->getUnit()->loadCustomPresetAtPath(storagePath + filename(compressor->getUnitSlug()));
}
