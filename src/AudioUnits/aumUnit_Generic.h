#pragma once
#include "aumManagedAudioUnit.h"

class aumUnit_Generic : public aumManagedAudioUnit
{
protected:
    int unnamedCount;

public:
    void update() {
        //Nothing to do.
    }

    void printParamsAsConstants(string unitPrefix) {
        cout << endl << "============================" << endl << endl;
        cout << "#pragma once" << endl << endl;
        cout << getParamsAsConstants(unitPrefix).str();
    }

    stringstream getParamsAsConstants(string unitPrefix) {
        vector<AudioUnitParameterInfo> paramList = unit.getParameterList();
        unnamedCount = 0;
        stringstream paramStr;

        for(int i = 0; i < paramList.size(); i++) {
            AudioUnitParameterInfo& p = paramList[i];
            string friendlyName = p.name;

            if(friendlyName.size() > 0) {
                friendlyName = formatFriendlyName(friendlyName);
                paramStr << "//" << p.name << endl;
            } else {
                friendlyName = "unnamed" + ofToString(++unnamedCount);
                paramStr << "//No name found" << endl;
            }

            paramStr << "//min: " << p.minValue << ", max: " << p.maxValue << ", default: " << p.defaultValue << endl;
            paramStr << "const static int " << unitPrefix << "_" << friendlyName << " = " << i << ";" << endl << endl;
        }

        paramStr << endl;
        return paramStr;
    }

    string formatFriendlyName(string givenName) {
        string friendlyName = ofToLower(givenName);
        ofStringReplace(friendlyName, " ", "_");
        ofStringReplace(friendlyName, ".", "_");
        ofStringReplace(friendlyName, "-", "_");
        ofStringReplace(friendlyName, ".", "_");
        ofStringReplace(friendlyName, "(", "_");
        ofStringReplace(friendlyName, ")", "_");
        ofStringReplace(friendlyName, "&", "_");
        ofStringReplace(friendlyName, ":", "_");
        ofStringReplace(friendlyName, "/", "_");
        ofStringReplace(friendlyName, "\\", "_");
        ofStringReplace(friendlyName, ">", "GT");
        ofStringReplace(friendlyName, "#", "_sharp");
        ofStringReplace(friendlyName, "<", "LT");
        ofStringReplace(friendlyName, "*", "MULTIPLY");
        ofStringReplace(friendlyName, "____", "_");
        ofStringReplace(friendlyName, "___", "_");
        ofStringReplace(friendlyName, "__", "_");
        return friendlyName;
    }
};
