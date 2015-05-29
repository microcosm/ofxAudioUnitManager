#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "PresetsHandler.h"
#include "MidiHandler.h"
#include "AudioUnitBase.h"

class AudioUnitChain {
    
public:
    virtual void setup(string _name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor);
    virtual void update();
    virtual void drawWaveform();
    virtual void exit();
    void load(AudioUnitBase* unit);
    void showUI();
    void savePresets();
    void deletePreset();
    void renamePreset();
    void incrementPreset();
    void decrementPreset();
    bool isSelected();
    void select();
    void deselect();
    ofxMidiOut* midi();
    PresetsHandler* getPresets();
    string getName();

protected:
    ofxAudioUnitTap tap;
    ofPolyline waveform;
    vector<AudioUnitBase*> units;
    
    PresetsHandler presets;
    MidiHandler midiHandler;
    ofColor waveColor;
    bool selected;
    string name;
};