/*
#include "profilegenerator.h"
#include<iostream>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<sys/stat.h>
#include<vector>
#include<cstring>
#include<dirent.h>

void ProfileGenerator::readTxtFiles(const std:: string& directory,float offset)
{   parameterProfile.clear();
   // txtFilePaths.clear();
    searchDirectory(directory,offset);
}

void ProfileGenerator::searchDirectory(const std::string& path,float offset)
{
    DIR* dir=opendir(path.c_str());
    if(!dir){
        std::cerr<<"Cannot open directory:"<<path<<std::endl;
        return;
    }
    struct dirent*entry;
    while((entry=readdir(dir))!=NULL)
    {
        std::string name=entry->d_name;
        if(name=="."||name=="..")continue;
        std::string fullPath=path+"/"+name;
        struct stat statbuf;
        if(stat(fullPath.c_str(),&statbuf)!=0){
            std::cerr<<"Cannot access:"<<fullPath<<std::endl;
            continue;
        }
       if(S_ISDIR(statbuf.st_mode))
       {
          // std::cout<<"Checking:"<<fullPath<<std::endl;
           searchDirectory(fullPath,offset);
       }
       else if(S_ISREG(statbuf.st_mode)){
           if(name.size()>=4&&name.substr(name.size()-4)==".txt"){
               //txtFilePaths.push_back(fullPath);
                //std::cout<<"Found file:"<<fullPath<<std::endl;
               std::vector<struct timeValueStruct> finalProfileData=readParameterFile(fullPath,offset);
               size_t slashPos=fullPath.find_last_of("/\\");
               std::string fileNameWithExt=(slashPos!=std::string::npos)?fullPath.substr(slashPos+1):fullPath;
               size_t dotPos=fileNameWithExt.find_last_of('.');
               std::string fileName=(dotPos!=std::string::npos)?fileNameWithExt.substr(0,dotPos):fileNameWithExt;
              // parameterProfile[fileName]=finalProfileData;
                // std::cout<<"fILE FOUND"<<fileName<<std::endl;
               for(size_t i=0;i<finalProfileData.size();++i)
               {
                   parameterProfile[fileName].push_back(finalProfileData[i]);
               }

           }
       }
    }
    closedir(dir);
}
std::vector<timeValueStruct> ProfileGenerator::readParameterFile(const std::string &filePath1,float offset)
{
    profileData.clear();
    //std::cout<<"Reading file:"<<filePath1<<std::endl;
    std::ifstream file(filePath1.c_str());
    if(!file){
    std::cerr<<"Cannot open file:"<<filePath1<<std::endl;
    //return;
    }
   std::string line;

   while(std::getline(file,line)){

        if(line.empty()|| line[0] == '*'){

            continue;
        }
   //std::cout"Line:["<<line<<"]\n";
    std:: istringstream iss(line);
    float time,value;
    if(iss>>time>>value){
        timeValueStruct tv;
        tv.flightTime=time+offset;
        tv.parameterValue=value;
        profileData.push_back(tv);
    }
   }

   //Note: Temporarily commented

  std::sort(profileData.begin(),profileData.end(),[](const timeValueStruct& a,const timeValueStruct& b){
    return a.flightTime<b.flightTime;
  });


  return profileData;
}

float ProfileGenerator::getLegendValue(string legend, float timeInstance) const{
    std::map<std::string,std::vector<timeValueStruct> >::const_iterator it=parameterProfile.find(legend);
   std::cout<<"Searching legend"<<legend<<std::endl;
     std::cout<<"\nAvailable legends:\n";
     for(std::map<std::string,std::vector<timeValueStruct> >::const_iterator it=parameterProfile.begin();it != parameterProfile.end();++it){
       std::cout<<" "<<it->first<<std::endl;
     }

    if(it != parameterProfile.end()){
        return getProfileValue(it->second,timeInstance);
    }


    else{
        std::cerr<<"Legend not found:"<<legend<<std::endl;
        return -1.0f;
    }
}

float ProfileGenerator::getProfileValue(vector<struct timeValueStruct> profileValue,float timeInstance) const{
    if(profileValue.empty()) return -1;
    if(timeInstance<=profileValue.front().flightTime){

        return profileValue.front().parameterValue;
    }
    if(timeInstance>=profileValue.back().flightTime){

        return profileValue.back().parameterValue;
    }
    for(size_t i=0;i<profileValue.size();++i)
    {
        if(profileValue[i].flightTime==timeInstance)
        {
            return profileValue[i].parameterValue;
        }
        else if(profileValue[i].flightTime>timeInstance && i>0)
        {
            float t1=profileValue[i-1].flightTime;
            float t2=profileValue[i].flightTime;
            float v1=profileValue[i-1].parameterValue;
            float v2=profileValue[i].parameterValue;
            return v1+(v2-v1)*(timeInstance-t1)/(t2-t1);

            std::cout<<"Interpolating between:\n";
            std::cout<<""<<t1<<"->"<<v1<<"\n";
             std::cout<<""<<t2<<"->"<<v2<<"\n";
             return interpolated;


        }
    }
    std::cerr<<"Time is out of range.\n";
    return -1.0f;
}

void ProfileGenerator::display() const{
     std::cout<<"Map is empty:\n";
    for(std::map<std::string,std::vector<timeValueStruct> >::const_iterator it=parameterProfile.begin();it != parameterProfile.end();++it){

        std::cout<<"File:"<<it->first<<"\n";
        const std::vector<timeValueStruct>& profile=it->second;
        for(size_t i=0;i<profile.size();++i){
            std::cout<<"Time:"<<profile[i].flightTime<<",Value"<<profile[i].parameterValue<<"\n";
        }
     }


   for(const auto& path:txtFilePaths){
        std::cout<<path<<std::endl;
   }



}

void ProfileGenerator::testFileWrite()
{
    QFile myFile("sample.txt");

    if(myFile.open(QFile::WriteOnly))
    {
         QTextStream myStrm(&myFile) ;

          myStrm << "The details are saved" <<endl;

          myStrm.flush();
     }

    return;

}

void ProfileGenerator::testIoDisplay(bool checked)
{
    if(checked)
    {
        cout<<"Successfully done"<<endl;
    }
    else
    {
        cout<<" Not Successfully done"<<endl;
    }

    myFlag = checked;

    return;
}

bool ProfileGenerator::isFlagSet()
{
    return myFlag;
}
*/
