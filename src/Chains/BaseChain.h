#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "PresetsHandler.h"
#include "MidiHandler.h"
#include "BaseUnit.h"

class BaseChain {
    
public:
    virtual void setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor);
    virtual void update();
    virtual void draw();
    virtual void exit();
    virtual string report();
    void load(BaseUnit* unit);
    void showUI();
    void savePresets();
    void incrementPreset();
    void decrementPreset();
    bool isSelected();
    void select();
    void deselect();
    void toggleSelected();
    ofxMidiOut* midi();
    
protected:
    ofxAudioUnitTap tap;
    ofPolyline waveform;
    vector<BaseUnit*> units;
    
    PresetsHandler presets;
    MidiHandler midiHandler;
    ofColor waveColor;
    bool selected;
};