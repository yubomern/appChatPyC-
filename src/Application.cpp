#include "Application.h"

#include <iostream>
#include <memory>

Application::Application()
    : m_fileReader(std::make_unique<FileReader>())
{
    std::cout << "Application created\n";
}

Application& Application::getInstance()
{
    static Application instance;

    return instance;
}

void Application::run()
{
    std::cout << "Application running\n";

    readFile("data/config.txt");
}

void Application::readFile(const std::string& filename)
{
    m_fileReader->readFile(filename);
}