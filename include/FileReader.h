#pragma once 


#include <string>


class FileReader
{

     public:
        FileReader();
        ~FileReader();

        std::string readFile(const std::string& filePath ) ;
        
};