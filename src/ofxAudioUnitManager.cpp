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

}

void ofxAudioUnitManager::draw() {
    if(showDebugUI) {
        //drawDebugBox(10, 10, 420, 300);
        //drawDebugBox(ofGetWidth() - 370, 10, 300, 230);
        //drawDebugBox(10, ofGetHeight() - 160, 210, 150);
        
        for(int i = 0; i < chains.size(); i++) {
            x = (reportMargin * (i + 1)) + (reportWidth * i);
            y = reportMargin + 10;
            drawDebugBox(x-10, y-20, reportWidth+20, reportHeight);
            ofSetColor(ofColor::white);
            ofDrawBitmapString(chains.at(i)->report(), x, y);
        }
        
        drawDebugBox(reportMargin-10, reportHeight + reportMargin, 300, 240);
        ofDrawBitmapString(controls.report(), reportMargin, reportHeight + reportMargin * 2);
        //largeFont.drawString("fps:\n" + ofToString(ofGetFrameRate()), 20, ofGetHeight() - 100);
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