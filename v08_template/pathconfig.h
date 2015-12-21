#ifndef _pathconfig_h
#define _pathconfig_h

#include <string>


class filePathBuilder
{
public:
    filePathBuilder(): dataPath("/home/igor/graphics/v08_template/data/"){}
    const char* filePath(const std::string& f_name)
    {
    fileFullPath = dataPath+f_name;
    return fileFullPath.c_str();
    }
private: 
    const std::string dataPath;
    std::string fileFullPath;
};

#endif
