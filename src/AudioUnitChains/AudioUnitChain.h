#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "PresetsHandler.h"
#include "MidiHandler.h"
#include "AudioUnitBase.h"

class AudioUnitChain {
    
public:
    virtual void setup(string _name, ofxAudioUnitMixer* _mixer, int _mixerChannel, ofColor _waveColor);
    virtual void update();
    virtual void drawWaveform();
    virtual void exit();
    void sendOut(ofxAudioUnit* chainEndpoint);
    void load(AudioUnitBase* unit);
    void loadUnit(AudioUnitBase* unit);
    void loadSynth(AudioUnitBase* synth);
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
    string getUnitReport();
    string getClassName();
    string getName();
    ofColor getColor();

protected:
    ofxAudioUnitTap tap;
    ofPolyline waveform;
    vector<AudioUnitBase*> units;
    ofxAudioUnitMixer* mixer;
    int mixerChannel;
    
    PresetsHandler presets;
    MidiHandler midiHandler;
    ofColor waveColor;
    bool selected;
    string name, unitReport, className;
};