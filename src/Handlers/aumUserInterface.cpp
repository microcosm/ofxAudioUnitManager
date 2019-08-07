#include "aumUserInterface.h"

void aumUserInterface::setup() {
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

    isFocused = true;
}

void aumUserInterface::setFocus(bool _isFocused) {
    isFocused = _isFocused;
}

void aumUserInterface::addChain() {
    reports.push_back("");
    lastMidiRecieved.push_back(midiReceiptTimeout + 1);
}

void aumUserInterface::drawControls() {
    controlsPositions = getControlsPositions();
    drawDebugBox(controlsPositions.x, controlsPositions.y, controlsDimensions.x, controlsDimensions.y);
    ofSetColor(ofColor::white);
    ofDrawBitmapString(controlsReport(), controlsPositions.x + padding, controlsPositions.y + padding*2);
}

void aumUserInterface::drawChains(vector<aumAudioUnitChain*> chains) {
    ofVec2f position;
    for(int i = 0; i < chains.size(); i++) {
        position.x = (chainInfoPositions.x * (i+1)) + (chainInfoDimensions.x * i);
        position.y = chainInfoPositions.y;
        drawWaveforms(chains.at(i), position.x);
        drawChainReport(chains.at(i), position, i+1);
        drawMidiReport(chains.at(i), position.x, i);
    }
}

void aumUserInterface::drawWaveforms(aumAudioUnitChain* chain, float positionX) {
    drawDebugBox(positionX, waveformsPositions.y, waveformsDimensions.x, waveformsDimensions.y, getBackgroundColor(chain));
    chain->tap()->getStereoWaveform(leftWaveform, rightWaveform, waveformsDimensions.x, waveformsDimensions.y);
    ofSetColor(getTextColor(chain));
    ofTranslate(positionX, waveformsPositions.y);
    leftWaveform.draw();
    rightWaveform.draw();
    ofTranslate(-positionX, -waveformsPositions.y);
}

void aumUserInterface::drawChainReport(aumAudioUnitChain* chain, ofVec2f position, int chainNumber) {
    drawDebugBox(position.x, position.y, chainInfoDimensions.x, chainInfoDimensions.y, getBackgroundColor(chain));
    ofSetColor(getTextColor(chain));
    ofDrawBitmapString(chainReport(chain, chainNumber), position.x + padding, position.y + padding*2);
}

void aumUserInterface::drawMidiReport(aumAudioUnitChain* chain, float positionX, int index) {
    drawDebugBox(positionX, midiInfoPositions.y, midiInfoDimensions.x, midiInfoDimensions.y, getBackgroundColor(chain));
    ofDrawBitmapString(midiReport(chain, index), positionX + padding, midiInfoPositions.y + padding*2);
}

void aumUserInterface::drawDebugBox(int x, int y, int width, int height, ofColor color) {
    ofSetLineWidth(1);
    ofSetColor(color);
    ofFill();
    ofDrawRectangle(x, y, width, height);
    ofSetColor(ofColor::white);
    ofNoFill();
    ofDrawRectangle(x, y, width, height);
}

ofVec2f aumUserInterface::getControlsPositions() {
    return ofVec2f(
        ofGetWidth()  - controlsDimensions.x - padding,
        ofGetHeight() - controlsDimensions.y - padding);
}

ofColor aumUserInterface::getBackgroundColor(aumAudioUnitChain* chain) {
    return chain->isSelected() ?
        ofColor(chain->getColor(), 128) :
        ofColor(chain->getColor(), 32);
}

ofColor aumUserInterface::getTextColor(aumAudioUnitChain* chain) {
    return chain->isSelected() ?
        ofColor(ofColor::white, 255) :
        ofColor(ofColor::white, 128);
}

string aumUserInterface::controlsReport() {
    stringstream report;

    if(isFocused) {
        report <<  "            CONTROLS"
        << endl << ""
        << endl << "            MANAGER"
        << endl << "            ----------------------"
        << endl << "         v: Toggle view overlay"
        << endl << " (upper) A: Show all UIs"
        << endl << " (lower) a: Show synth UIs"
        << endl << "         m: Show mixer/compressor"
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
    } else {
        report <<  "Press Command key to set focus";
    }
    return report.str();
}

string aumUserInterface::chainReport(aumAudioUnitChain *chain, int number) {
    string underline(chain->getName().length(), '-');
    stringstream report;
    report  << "CHAIN " << number << " \"" << chain->getName() << "\""
    << endl << "---------" << underline << "-"
    << endl << chain->getUnitReport()
    << endl << ""
    << endl << chain->presets()->report();
    return report.str();
}

string aumUserInterface::midiReport(aumAudioUnitChain *chain, int index) {
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
