#include "ProcessWatcher.h"
#include <sstream>

void ProcessWatcher::addProcess(const int& pid, const std::wstring& exeName, const std::wstring& path, const std::wstring& cmdArgs)
{
	runningProcesses.emplace_back(ProcessInfo(pid, exeName, path, cmdArgs));
}

std::wstring ProcessWatcher::JSONProcessesString() const
{
    std::wstringstream oss;
    oss << "{\"" << processes << "\":[";
    for (auto i = 0; i < runningProcesses.size(); i++)
    {
        oss << "{\"" << pid << "\":" << runningProcesses[i].GetPid() << ","
            << "\"" << pathToExe << "\":" << "\"" << runningProcesses[i].GetPath() << "\","
            << "\"" << cmdLineArgs << "\":" << "\"" << runningProcesses[i].GetCmdLineArgs() << "\"}";
        if (i < runningProcesses.size() - 1)
            oss << ",";
    }
    oss << "]}";
    return oss.str();
}