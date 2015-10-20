#ifndef _pathconfig_h
#define _pathconfig_h

#include <string>

class filePathBuilder
{
public:
    filePathBuilder(): dataPath("/home/igor/graphics/v02_template/data"){}
    std::string filePath(const std::string& f_name)
    { return dataPath+"/" + f_name;    }
private: 
    const std::string dataPath;
};

#endif
