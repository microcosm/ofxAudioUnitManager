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
        ofStringReplace(classTemplate, "<PARAM_CONSTS>", getParamsAsConstants());
        ofStringReplace(classTemplate, "<PARAM_PREVIOUS_VARS>", getParamsAsVars());
        ofStringReplace(classTemplate, "<PARAM_COMPARE_CALLS>", getCompareCalls());
        ofStringReplace(classTemplate, "<PARAM_RECORD_STATEMENTS>", getRecordStatements());
        writeFile(classTemplate, deviceName);
    }

    void printParamsAsConstants() {
        cout << "============================" << endl;
        cout << "#pragma once" << endl;
        cout << getParamsAsConstants();
    }
    
    string getParamsAsConstants() {
        vector<AudioUnitParameterInfo> paramList = unit.getParameterList();
        unnamedCount = 0;
        stringstream paramStr;
        
        for(int i = 0; i < paramList.size(); i++) {
            AudioUnitParameterInfo& p = paramList[i];
            string friendlyName = p.name;
            
            if(friendlyName.size() > 0) {
                friendlyName = formatFriendlyName(friendlyName);
                paramStr << "    //" << p.name << endl;
            } else {
                friendlyName = "unnamed" + ofToString(++unnamedCount);
                paramStr << "    //No name found" << endl;
            }
            
            paramStr << "    //min: " << p.minValue << ", max: " << p.maxValue << ", default: " << p.defaultValue << endl;
            paramStr << "    const static int " << friendlyName << " = " << i << ";";

            if(i != paramList.size() - 1) paramStr << endl << endl;
        }

        return paramStr.str();
    }
    
    string getParamsAsVars() {
        vector<AudioUnitParameterInfo> paramList = unit.getParameterList();
        unnamedCount = 0;
        stringstream paramStr;
        
        for(int i = 0; i < paramList.size(); i++) {
            AudioUnitParameterInfo& p = paramList[i];
            string friendlyName = p.name;

            if(friendlyName.size() > 0) {
                friendlyName = formatFriendlyName(friendlyName);
            } else {
                friendlyName = "unnamed" + ofToString(++unnamedCount);
            }

            paramStr << "    AudioUnitParameterValue " << "previous_" << friendlyName << ";";

            if(i != paramList.size() - 1) paramStr << endl;
        }

        return paramStr.str();
    }
    
    string getCompareCalls() {
        vector<AudioUnitParameterInfo> paramList = unit.getParameterList();
        unnamedCount = 0;
        stringstream paramStr;
        
        for(int i = 0; i < paramList.size(); i++) {
            AudioUnitParameterInfo& p = paramList[i];
            string friendlyName = p.name;
            
            if(friendlyName.size() > 0) {
                friendlyName = formatFriendlyName(friendlyName);
            } else {
                friendlyName = "unnamed" + ofToString(++unnamedCount);
            }
            
            paramStr << "        compareAndPrint(\"" + friendlyName + "\", previous_" + friendlyName + ", get(" + friendlyName + "));";

            if(i != paramList.size() - 1) paramStr << endl;
        }

        return paramStr.str();
    }

    string getRecordStatements() {
        vector<AudioUnitParameterInfo> paramList = unit.getParameterList();
        unnamedCount = 0;
        stringstream paramStr;
        
        for(int i = 0; i < paramList.size(); i++) {
            AudioUnitParameterInfo& p = paramList[i];
            string friendlyName = p.name;
            
            if(friendlyName.size() > 0) {
                friendlyName = formatFriendlyName(friendlyName);
            } else {
                friendlyName = "unnamed" + ofToString(++unnamedCount);
            }
            
            paramStr << "        previous_" + friendlyName + " = get(" + friendlyName + ");";

            if(i != paramList.size() - 1) paramStr << endl;
        }

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
        << endl << "/******************************************************************************/"
        << endl << "/* WARNING: THIS CLASS WAS GENERATED BY THE FOLLOWING FUNCTION:               */"
        << endl << "/*                                                                            */"
        << endl << "/*     aumUnit_Generic::generateClassFileForAudioUnit(string deviceName);     */"
        << endl << "/*                                                                            */"
        << endl << "/* IF YOU EDIT THIS FILE, YOU RISK HAVING YOUR CHANGES OVERWRITTEN THE NEXT   */"
        << endl << "/* TIME THE FILE IS RE-WRITTEN BY THIS FUNCTION. TO EDIT THIS FILE, PLEASE    */"
        << endl << "/* COPY IT TO ANY OTHER FOLDER, RENAME THE CLASS, AND THEN MAKE EDITS.        */"
        << endl << "/******************************************************************************/"
        << endl << ""
        << endl << "class aumUnit_<DEVICE_NAME> : public aumMonitorableAudioUnit"
        << endl << "{"
        << endl << "public:"
        << endl << "<PARAM_CONSTS>"
        << endl << ""
        << endl << "    //These variables store the most recenty recorded values"
        << endl << "    //of each of the parameters, for recording and detection"
        << endl << "<PARAM_PREVIOUS_VARS>"
        << endl << ""
        << endl << "    void setup(string _unitName) {"
        << endl << "        aumManagedAudioUnit::setup(_unitName, '" << stringify(osType) << "', '" << stringify(osSubType) << "', '" << stringify(osManufacturer) << "', \"aumUnit_<DEVICE_NAME>\");"
        << endl << "    }"
        << endl << ""
        << endl << "    void doPrintChanges() {"
        << endl << "<PARAM_COMPARE_CALLS>"
        << endl << "    }"
        << endl << ""
        << endl << "    void doRecordParams() {"
        << endl << "<PARAM_RECORD_STATEMENTS>"
        << endl << "    }"
        << endl << "};";
        return classTemplate.str();
    }
};
