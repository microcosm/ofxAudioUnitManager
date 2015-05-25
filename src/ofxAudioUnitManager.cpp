#include "ofxAudioUnitManager.h"

void ofxAudioUnitManager::setup() {
    showDebugUI = false;
    reportMargin = 25;
    reportWidth = 200;
    reportHeight = 170;
    compressor.setup();
    mixer.connectTo(*compressor.get()).connectTo(output);
    output.start();
}

void ofxAudioUnitManager::add(BaseChain *chain, string name, ofColor color) {
    chains.push_back(chain);
    mixer.setInputBusCount(chains.size());
    chain->setup(name, &mixer, chains.size() - 1, color);
    chain->select();
}

void ofxAudioUnitManager::update() {
    for(int i = 0; i < chains.size(); i++) {
        chains.at(i)->update();
    }
}

void ofxAudioUnitManager::draw() {
    if(showDebugUI) {
        
        //Draw MIDI
        for(int i = 0; i < chains.size(); i++) {
            x = (reportMargin * (i + 1)) + (reportWidth * i);
            y = reportMargin + 10;
            drawDebugBox(x-10, y-20, reportWidth+20, reportHeight);
            ofSetColor(ofColor::white);
            ofDrawBitmapString(chains.at(i)->report(), x, y);
        }
        
        //Draw controls
        x = reportMargin - 10;
        y = reportHeight + reportMargin;
        drawDebugBox(x, y, 300, 240);
        
        x = reportMargin;
        y = reportHeight + reportMargin * 2;
        ofDrawBitmapString(controls.report(), x, y);
    }
    
    //Draw chain polylines
    for(int i = 0; i < chains.size(); i++) {
        chains.at(i)->draw();
    }
}

void ofxAudioUnitManager::exit() {
    for(int i = 0; i < chains.size(); i++) {
        chains.at(i)->exit();
    }
}

void ofxAudioUnitManager::toggleDebugUI() {
    showDebugUI = !showDebugUI;
}

void ofxAudioUnitManager::drawDebugBox(int x, int y, int width, int height) {
    ofSetColor(ofColor::white, 32);
    ofFill();
    ofRect(x, y, width, height);
    ofSetColor(ofColor::white);
    ofNoFill();
    ofRect(x, y, width, height);
}