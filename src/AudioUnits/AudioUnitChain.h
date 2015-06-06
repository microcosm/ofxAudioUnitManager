#pragma once
#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "PresetsHandler.h"
#include "MidiHandler.h"
#include "AudioUnitBase.h"

class AudioUnitChain {
    
public:
    virtual void setup(string _chainName, ofxAudioUnitMixer* _mixer, int _mixerChannel, ofColor _waveColor);
    void loadPresets();
    void update();
    void drawWaveform();
    void exit();
    void toMixer(ofxAudioUnit* chainEndpoint);
    void toMixer();
    AudioUnitChain& link(AudioUnitBase* unit);
    AudioUnitChain& link(AudioUnitBase* unit, string unitName);
    AudioUnitChain& to(AudioUnitBase* unit);
    AudioUnitChain& to(AudioUnitBase* unit, string unitName);
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
    void loadUnit(AudioUnitBase* unit, string unitName);
    void loadSynth(AudioUnitBase* synth, string unitName);
    ofxAudioUnitTap tap;
    ofPolyline waveform;
    vector<AudioUnitBase*> units;
    ofxAudioUnit* unitEndpoint;
    ofxAudioUnitMixer* mixer;
    int mixerChannel;
    
    PresetsHandler presetsHandler;
    MidiHandler midiHandler;
    ofColor waveColor;
    bool selected;
    string chainName, className, unitReport;
};