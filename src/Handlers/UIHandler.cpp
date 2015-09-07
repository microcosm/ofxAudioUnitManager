#include "UIHandler.h"

void UIHandler::setup() {
    midiReceiptTimeout = 15;
    padding = 10;
    controlsDimensions = ofVec2f(300, 340);
    chainInfoDimensions = ofVec2f(220, 340);
    waveformsDimensions = ofVec2f(220, 80);
    midiInfoDimensions = ofVec2f(220, 32);

    controlsPositions = getControlsPositions();
    chainInfoPositions = ofVec2f(padding, padding);
    waveformsPositions = ofVec2f(padding, chainInfoPositions.y + chainInfoDimensions.y + 5);
    midiInfoPositions = ofVec2f(padding, waveformsPositions.y + waveformsDimensions.y + 5);
}

void UIHandler::addChain() {
    reports.push_back("");
    lastMidiRecieved.push_back(midiReceiptTimeout + 1);
}

void UIHandler::drawControls() {
    controlsPositions = getControlsPositions();
    drawDebugBox(controlsPositions.x, controlsPositions.y, controlsDimensions.x, controlsDimensions.y);
    ofSetColor(ofColor::white);
    ofDrawBitmapString(controlsReport(), controlsPositions.x + padding, controlsPositions.y + padding*2);
}

void UIHandler::drawChains(vector<ofxAudioUnitChain*> chains) {
    ofVec2f position;
    for(int i = 0; i < chains.size(); i++) {
        position.x = (chainInfoPositions.x * (i+1)) + (chainInfoDimensions.x * i);
        position.y = chainInfoPositions.y;
        drawWaveforms(chains.at(i), position.x);
        drawChainReport(chains.at(i), position, i+1);
        drawMidiReport(chains.at(i), position.x, i);
    }
}

void UIHandler::drawWaveforms(ofxAudioUnitChain* chain, float positionX) {
    drawDebugBox(positionX, waveformsPositions.y, waveformsDimensions.x, waveformsDimensions.y, getBackgroundColor(chain));
    chain->tap()->getStereoWaveform(leftWaveform, rightWaveform, waveformsDimensions.x, waveformsDimensions.y);
    ofSetColor(getTextColor(chain));
    ofTranslate(positionX, waveformsPositions.y);
    leftWaveform.draw();
    rightWaveform.draw();
    ofTranslate(-positionX, -waveformsPositions.y);
}

void UIHandler::drawChainReport(ofxAudioUnitChain* chain, ofVec2f position, int chainNumber) {
    drawDebugBox(position.x, position.y, chainInfoDimensions.x, chainInfoDimensions.y, getBackgroundColor(chain));
    ofSetColor(getTextColor(chain));
    ofDrawBitmapString(chainReport(chain, chainNumber), position.x + padding, position.y + padding*2);
}

void UIHandler::drawMidiReport(ofxAudioUnitChain* chain, float positionX, int index) {
    drawDebugBox(positionX, midiInfoPositions.y, midiInfoDimensions.x, midiInfoDimensions.y, getBackgroundColor(chain));
    ofDrawBitmapString(midiReport(chain, index), positionX + padding, midiInfoPositions.y + padding*2);
}

void UIHandler::drawDebugBox(int x, int y, int width, int height, ofColor color) {
    ofSetLineWidth(1);
    ofSetColor(color);
    ofFill();
    ofRect(x, y, width, height);
    ofSetColor(ofColor::white);
    ofNoFill();
    ofRect(x, y, width, height);
}

ofVec2f UIHandler::getControlsPositions() {
    return ofVec2f(
        ofGetWidth()  - controlsDimensions.x - padding,
        ofGetHeight() - controlsDimensions.y - padding);
}

ofColor UIHandler::getBackgroundColor(ofxAudioUnitChain* chain) {
    return chain->isSelected() ?
        ofColor(chain->getColor(), 128) :
        ofColor(chain->getColor(), 32);
}

ofColor UIHandler::getTextColor(ofxAudioUnitChain* chain) {
    return chain->isSelected() ?
        ofColor(ofColor::white, 255) :
        ofColor(ofColor::white, 128);
}

string UIHandler::controlsReport() {
    stringstream report;
    report <<  "            CONTROLS"
    << endl << ""
    << endl << "            MANAGER"
    << endl << "            ----------------------"
    << endl << "         v: Toggle view overlay"
    << endl << " (upper) A: Show all UIs"
    << endl << " (lower) a: Show synth UIs"
    << endl << "         m: Show mixer UI"
    << endl << "Left/right: Select chain"
    << endl << ""
    << endl << "            SELECTED CHAIN [*]"
    << endl << "            ----------------------"
    << endl << "         u: Show audio unit UIs"
    << endl << "   Up/down: Select preset"
    << endl << " (upper) S: Save current preset"
    << endl << " (lower) s: Save as new preset"
    << endl << "         r: Rename current preset"
    << endl << "         t: Send preset to trash"
    << endl << ""
    << endl << "            EXAMPLE APP"
    << endl << "            ----------------------"
    << endl << "     SPACE: Start/stop playing"
    << endl << "     [ / ]: Current note up / down";
    return report.str();
}

string UIHandler::chainReport(ofxAudioUnitChain *chain, int number) {
    string underline(chain->getName().length(), '-');
    stringstream report;
    report  << "CHAIN " << number << " \"" << chain->getName() << "\""
    << endl << "---------" << underline << "-"
    << endl << chain->getUnitReport()
    << endl << ""
    << endl << chain->presets()->report();
    return report.str();
}

string UIHandler::midiReport(ofxAudioUnitChain *chain, int index) {
    tempMidiReport = chain->getMidiReport();
    if(tempMidiReport.length() > 0) {
        reports[index] = tempMidiReport;
        lastMidiRecieved[index] = 0;
    } else {
        lastMidiRecieved[index]++;
    }
    ofSetColor(ofMap(lastMidiRecieved[index], 0, midiReceiptTimeout, 255, 0));
    return reports[index];
}