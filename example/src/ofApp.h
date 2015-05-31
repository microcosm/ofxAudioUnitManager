#pragma once

#include "ofMain.h"
#include "ofxBpm.h"
#include "ofxAudioUnit.h"
#include "SamplerChain.h"
#include "TALNoiseMakerChain.h"
#include "AlchemyChain.h"
#include "ofxAudioUnitManager.h"

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
    AlchemyChain chain1, chain2;
    //SamplerChain chain1, chain2;
    //TALNoiseMakerChain chain1, chain2;
    ofxBpm bpm;
    bool playing;
    int note;
};
