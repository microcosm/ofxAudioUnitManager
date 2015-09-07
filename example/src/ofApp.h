#pragma once

#include "ofMain.h"
#include "ofxAudioUnit.h"
#include "ofxAudioUnitManager.h"
#include "ofxBpm.h"

class ofApp : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void play();
    void togglePlaying();
    void exit();

    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);

    ofxAudioUnitManager manager;
    ofxAudioUnitChain myChain, chain2;
    ofxManagedAudioUnit mySynth, noiseMaker2;
    ofxManagedAudioUnit myFilter, filter2, filter3;
    ofxManagedAudioUnit myReverb, reverb2;

    bool playing, on;
    int note;
};