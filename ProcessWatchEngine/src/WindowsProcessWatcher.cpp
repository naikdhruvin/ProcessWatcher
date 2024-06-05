#include <iostream>
#include "WindowsProcessWatcher.h"
#include <numeric>
#include <functional>
#include<algorithm>
#include <regex>

//---------------------------------------------------
WindowsProcessWatcher::WindowsProcessWatcher()
	: ProcessWatcher(OperatingSystem::WINDOWS)
{

}


std::wstring WindowsProcessWatcher::currentProcesses()
{
    populateProcesses();
	return JSONProcessesString();
}

void WindowsProcessWatcher::populateProcesses()
{
#ifdef WIN32
    HINSTANCE hNtDll = GetModuleHandleW(L"ntdll.dll");
    if (!hNtDll)
        return;
    NtQueryInformationProcessPtr NtQueryInformationProcess = (NtQueryInformationProcessPtr)GetProcAddress(hNtDll, "NtQueryInformationProcess");
    RtlNtStatusToDosErrorPtr RtlNtStatusToDosError = (RtlNtStatusToDosErrorPtr)GetProcAddress(hNtDll, "RtlNtStatusToDosError");
    runningProcesses.clear();
    std::unique_ptr<void, std::function<void(HANDLE)>> hProcessSnap(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0), [](HANDLE handle) { CloseHandle(handle); });
    if (hProcessSnap.get() == INVALID_HANDLE_VALUE)
    {
        return;
    }

    PROCESSENTRY32W pe32;
    pe32.dwSize = sizeof(PROCESSENTRY32W);

    if (!Process32FirstW(hProcessSnap.get(), &pe32))
    {
        return;
    }

    do
    {
        std::unique_ptr<void, std::function<void(HANDLE)>> hProcess(OpenProcess(PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID), [](HANDLE handle) { CloseHandle(handle); });
        if (hProcess.get())
        {
            auto pid = pe32.th32ProcessID;
            wchar_t filename[MAX_PATH] = { 0 };
            if (GetModuleFileNameExW(hProcess.get(), NULL, filename, MAX_PATH) == 0)
            {
                std::cout << "Failed to get module filename. Process Id = " << pid << std::endl;
            }

            PROCESS_BASIC_INFORMATION pbi;
            ULONG len;
            NTSTATUS status = NtQueryInformationProcess(hProcess.get(), ProcessBasicInformation, &pbi, sizeof(pbi), &len);
            if (NT_ERROR(status) || !pbi.PebBaseAddress)
            {
                std::cout << "NtQueryInformationProcess (ProcessBasicInformation) failed. Process Id = " << pid << std::endl;
                return;
            }

            // Read PEB memory block 
            SIZE_T bytesRead = 0;
            PEB_INTERNAL peb;
            if (!ReadProcessMemory(hProcess.get(), pbi.PebBaseAddress, &peb, sizeof(peb), &bytesRead))
            {
                std::cout << "Reading PEB failed. Process Id = " << pid << std::endl;
                return;
            }

            // Obtain size of commandline string
            RTL_USER_PROCESS_PARAMETERS_I upp;
            if (!ReadProcessMemory(hProcess.get(), peb.ProcessParameters, &upp, sizeof(upp), &bytesRead))
            {
                std::cout << "Reading USER_PROCESS_PARAMETERS failed. Process Id = " << pid << std::endl;
                return;
            }

            if (!upp.CommandLine.Length)
            {
                std::cout << "Command line length is 0. Process Id = " << pid << std::endl;
                return;
            }

            // Check the buffer size 
            DWORD dwNeedLength = (upp.CommandLine.Length + 1) / sizeof(wchar_t) + 1;
            std::unique_ptr<wchar_t[]> buf(new wchar_t[dwNeedLength]);
            // Get the actual command line 
            buf[dwNeedLength - 1] = L'\0';
            if (!ReadProcessMemory(hProcess.get(), upp.CommandLine.Buffer, buf.get(), upp.CommandLine.Length, &bytesRead))
            {
                printf("Reading command line failed.");
                return;
            }
            std::wstring pathToExe = std::wstring(filename);
            std::replace(pathToExe.begin(), pathToExe.end(), L'\\', L'/');
            std::wstring cmdLineArgs = std::wstring(buf.get());
            std::replace(cmdLineArgs.begin(), cmdLineArgs.end(), L'\\', L'/');
            cmdLineArgs.erase(remove(cmdLineArgs.begin(), cmdLineArgs.end(), L'"'), cmdLineArgs.end()); //remove A from string
            addProcess(pid, std::wstring(pe32.szExeFile), pathToExe, cmdLineArgs);
        }
        else
        {
            //std::cout << "Could not open process to read the information: PID= " << pe32.th32ProcessID << std::endl;
        }
    } while (Process32NextW(hProcessSnap.get(), &pe32));
#endif
}