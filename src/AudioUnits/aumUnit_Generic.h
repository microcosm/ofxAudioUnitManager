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

    void generateClassFileForAudioUnit(string deviceName) {
        string classTemplate = getClassTemplate();
        ofStringReplace(classTemplate, "<DEVICE_NAME>", deviceName);
        writeFile(classTemplate, deviceName);
    }

    void printParamsAsConstants(string deviceName) {
        cout << "============================" << endl;
        cout << "#pragma once" << endl;
        cout << getParamsAsConstants(deviceName);
    }

    string getParamsAsConstants(string deviceName) {
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
            paramStr << "const static int " << deviceName << "_" << friendlyName << " = " << i << ";" << endl;
        }

        paramStr << endl;
        return paramStr.str();
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

    void writeFile(string contents, string deviceName) {
        ofFile file(ofToDataPath("../../../src/AudioUnits/aumUnit_" + deviceName + ".h"), ofFile::WriteOnly);
        file.create();
        file << contents;
    }

    string getClassTemplate() {
        stringstream classTemplate;
        classTemplate << "#pragma once"
        << endl << "#include \"aumMonitorableAudioUnit.h\""
        << endl << ""
        << endl << "class aumUnit_<DEVICE_NAME> : public aumMonitorableAudioUnit"
        << endl << "{"
        << endl << "public:"
        << endl << ""
        << endl << "    <PARAM_CONSTS>"
        << endl << ""
        << endl << "    //These variables store the most recenty recorded values"
        << endl << "    //of each of the parameters, for recording and detection"
        << endl << "    <PARAM_PREVIOUS_VARS>"
        << endl << ""
        << endl << "    void doPrintChanges() {"
        << endl << "        <PARAM_COMPARE_CALLS>"
        << endl << "    }"
        << endl << ""
        << endl << "    void doRecordParams() {"
        << endl << "        <PARAM_RECORD_STATEMENTS>"
        << endl << "    }"
        << endl << "}";
        return classTemplate.str();
    }
};
