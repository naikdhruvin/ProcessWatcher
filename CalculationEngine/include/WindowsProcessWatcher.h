#pragma once

#ifdef WIN32
#include <windows.h>
#include <winternl.h>
#include <tlhelp32.h>
#include <tchar.h>
#include <psapi.h> // For access to GetModuleFileNameEx
#endif

#include <functional>
#include <memory>
#include <locale.h> 
#include "ProcessWatcher.h"

#ifdef WIN32

typedef NTSTATUS(NTAPI* NtQueryInformationProcessPtr) (
    IN HANDLE ProcessHandle,
    IN PROCESSINFOCLASS ProcessInformationClass,
    OUT PVOID ProcessInformation,
    IN ULONG ProcessInformationLength,
    OUT PULONG ReturnLength OPTIONAL);

typedef ULONG(NTAPI* RtlNtStatusToDosErrorPtr) (NTSTATUS Status);

struct RTL_USER_PROCESS_PARAMETERS_I
{
    BYTE Reserved1[16];
    PVOID Reserved2[10];
    UNICODE_STRING ImagePathName;
    UNICODE_STRING CommandLine;
};

struct PEB_INTERNAL
{
    BYTE Reserved1[2];
    BYTE Debugged;
    BYTE Reserved2[1];
    PVOID Reserved3[2];
    struct PEB_LDR_DATA* Ldr;
    RTL_USER_PROCESS_PARAMETERS_I* ProcessParameters;
    BYTE Reserved4[104];
    PVOID Reserved5[52];
    struct PS_POST_PROCESS_INIT_ROUTINE* PostProcessInitRoutine;
    BYTE Reserved6[128];
    PVOID Reserved7[1];
    ULONG SessionId;
};

#endif

/*!
* \brief WindowsProcessWatcher Class
*/

class WindowsProcessWatcher : public ProcessWatcher {
public:
    //! A constructor.
    WindowsProcessWatcher();

    //! A virtual member.
    /*!
     \brief This function returns string in JSON format for all running exes on windows platform, paths to exe, to the console.
    */
    virtual std::wstring currentProcesses();
private:
    void populateProcesses();
};