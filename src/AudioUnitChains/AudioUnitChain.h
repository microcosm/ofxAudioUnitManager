#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "PresetsHandler.h"
#include "MidiHandler.h"
#include "AudioUnitBase.h"

class AudioUnitChain {
    
public:
    virtual void setup(string _name, ofxAudioUnitMixer* _mixer, int _mixerChannel, ofColor _waveColor);
    void loadPresets();
    void update();
    void drawWaveform();
    void exit();
    void sendOut(ofxAudioUnit* chainEndpoint);
    void load(AudioUnitBase* unit);
    void showUI();
    bool isSelected();
    void select();
    void deselect();
    ofxMidiOut* midi();
    PresetsHandler* presets();
    string getUnitReport();
    string getClassName();
    string getName();
    ofColor getColor();

protected:
    void loadUnit(AudioUnitBase* unit);
    void loadSynth(AudioUnitBase* synth);
    ofxAudioUnitTap tap;
    ofPolyline waveform;
    vector<AudioUnitBase*> units;
    ofxAudioUnitMixer* mixer;
    int mixerChannel;
    
    PresetsHandler presetsHandler;
    MidiHandler midiHandler;
    ofColor waveColor;
    bool selected;
    string name, unitReport, className;
};