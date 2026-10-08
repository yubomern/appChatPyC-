#include "CommandExecutor.h"

#include <array>
#include <cstdio>
#include <memory>

std::string CommandExecutor::execute(const std::string& command)
{
    // IMPORTANT:
    // Never execute arbitrary commands received from the network.
    // Only permit explicit commands.

    std::string realCommand;

    if (command == "date")
    {
        realCommand = "date /T";
    }
    else if (command == "time")
    {
        realCommand = "time /T";
    }
    else if (command == "version")
    {
        realCommand = "ver";
    }
    else
    {
        return "Command not allowed\n";
    }

    std::array<char, 256> buffer{};
    std::string result;

    FILE* pipe = _popen(realCommand.c_str(), "r");

    if (pipe == nullptr)
    {
        return "Cannot start command\n";
    }

    while (fgets(buffer.data(),
                 static_cast<int>(buffer.size()),
                 pipe) != nullptr)
    {
        result += buffer.data();
    }

    const int exitCode = _pclose(pipe);

    if (result.empty())
    {
        result = "Command returned no output\n";
    }

    result += "\nExit code: ";
    result += std::to_string(exitCode);
    result += '\n';

    return result;
}