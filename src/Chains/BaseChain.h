#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "PresetsHandler.h"
#include "MidiHandler.h"

class BaseChain {
    
public:
    virtual void setup(string name, ofxAudioUnitMixer* mixer, int mixerChannel, ofColor _waveColor);
    virtual void update();
    virtual void draw();
    virtual void exit();
    virtual string report();
    void savePresets();
    void incrementPreset();
    void decrementPreset();
    bool isSelected();
    void select();
    void deselect();
    void toggleSelected();
    void incrementMidiNote();
    void decrementMidiNote();
    void midiNoteOn();
    void midiNoteOff();
    
protected:
    ofxAudioUnitTap tap;
    ofPolyline waveform;
    
    PresetsHandler presets;
    MidiHandler midi;
    ofColor waveColor;
    bool selected;
};