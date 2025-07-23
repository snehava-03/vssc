/*
#ifndef PROFILEGENERATOR_H
#define PROFILEGENERATOR_H
#include <string>
#include <vector>
#include <map>
#include <algorithm>

#include <QFile>
#include <QTextStream>
#include <iostream>

using namespace std;

struct timeValueStruct
{
    float flightTime;
    float parameterValue;
};

class ProfileGenerator
{
    //members
    public:

    private:
       vector<string>txtFilePaths;
        vector<struct timeValueStruct> profileData;//fn()
        map <string, vector<struct timeValueStruct> > parameterProfile;

        bool myFlag;

    protected:

    //funtions
    public:
        void readTxtFiles(const string& directory,float offset);
        vector<timeValueStruct>readParameterFile(const string& filePath,float offset);
        float getLegendValue(string legend, float timeInstance)const;
        float getProfileValue(vector<struct timeValueStruct> profileValue, float timeInstance)const;
        void display() const;

        void testFileWrite();
        void testIoDisplay(bool checked);
        bool isFlagSet();
   
    private:
       void searchDirectory(const  string& path,float offset);
    protected:


};

#endif // PROFILEGENERATOR_H

*/
