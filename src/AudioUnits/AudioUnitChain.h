#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "PresetsHandler.h"
#include "MidiHandler.h"
#include "AudioUnitBase.h"

class AudioUnitChain {
    
public:
    virtual void setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor);
    virtual void update();
    virtual void draw();
    virtual void exit();
    virtual string report();
    void load(AudioUnitBase* unit);
    void showUI();
    void savePresets();
    void incrementPreset();
    void decrementPreset();
    bool isSelected();
    void select();
    void deselect();
    ofxMidiOut* midi();
    
protected:
    ofxAudioUnitTap tap;
    ofPolyline waveform;
    vector<AudioUnitBase*> units;
    
    PresetsHandler presets;
    MidiHandler midiHandler;
    ofColor waveColor;
    bool selected;
};