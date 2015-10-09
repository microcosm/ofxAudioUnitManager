#pragma once
#include "TALNoiseMaker_Params.h"
#include "Massive_Params.h"

enum ofxAudioUnitDevice {
    AUDIOUNIT_TALNOISEMAKER,
    AUDIOUNIT_MASSIVE
};

class ofxAudioUnitParams {
    
public:
    vector<OSType> getAudioUnitOSTypes(ofxAudioUnitDevice device) {
        vector<OSType> osTypes;
        switch(device){
            case AUDIOUNIT_TALNOISEMAKER:
                osTypes.push_back('aumu');
                osTypes.push_back('ncut');
                osTypes.push_back('TOGU');
                break;
            case AUDIOUNIT_MASSIVE:
                osTypes.push_back('aumu');
                osTypes.push_back('NiMa');
                osTypes.push_back('-NI-');
                break;
            default:
                osTypes.push_back('aumu');
                osTypes.push_back('ncut');
                osTypes.push_back('TOGU');
                break;
        }
        return osTypes;
    }
};