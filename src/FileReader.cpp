#include "FileReader.h"

#include <fstream>
#include <iostream>
#include <string>

FileReader::FileReader()
{
    std::cout << "FileReader created\n";
}

std::string FileReader::readFile(const std::string& filePath)
{
    std::ifstream file(filePath);
    std::ofstream outputFile("output.txt");
    std::string content;

    if (!file.is_open())
    {
        std::cerr << "Cannot open file: " << filePath << '\n';
        return "";
    }

    std::string line;
    while (std::getline(file, line))
    {
        content += line + "\n";
        outputFile << content << "\n";

    }

    file.close();
    outputFile.close();
    return content;
}
       
FileReader::~FileReader()
{
    std::cout << "FileReader destroyed\n";
}