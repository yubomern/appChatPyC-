#ifndef APPLICATION_H
#define APPLICATION_H

#include "FileReader.h"

#include <memory>
#include <string>

class Application
{
public:
    static Application& getInstance();

    Application(const Application&) = delete;
    Application& operator=(const Application&) = delete;

    void run();
    void readFile(const std::string& filename);

private:
    Application();

private:
    std::unique_ptr<FileReader> m_fileReader;
};

#endif