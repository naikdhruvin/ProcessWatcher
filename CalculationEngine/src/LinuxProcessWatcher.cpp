#include <iostream>
#include "LinuxProcessWatcher.h"

static void StringToWString(std::wstring &ws, const std::string &s)
{
    std::wstring wsTmp(s.begin(), s.end());
    ws = wsTmp;
}
//---------------------------------------------------
LinuxProcessWatcher::LinuxProcessWatcher()
	: ProcessWatcher(OperatingSystem::LINUX)
{

}


std::wstring LinuxProcessWatcher::currentProcesses()
{
    populateProcesses();
	return JSONProcessesString();
}

void LinuxProcessWatcher::populateProcesses()
{
#ifndef WIN32
	std::unique_ptr<PROCTAB, std::function<void(PROCTAB*)>>proc(openproc(PROC_FILLMEM | PROC_FILLSTAT | PROC_FILLSTATUS | PROC_FILLCOM | PROC_EDITCMDLCVT), [](PROCTAB* proc) { closeproc(proc); });
	proc_t proc_info;
	memset(&proc_info, 0, sizeof(proc_info));
	while (readproc(proc.get(), &proc_info) != NULL) {
		std::string process = "/proc/" + std::to_string(proc_info.tid) + +"/exe";
		char buf[1024];
		size_t ret = readlink(process.c_str(), buf, 1024);
		if (ret > 0) {
			buf[ret] = 0;
		}
		else {
			perror("readlink");

		}
		std::string exePath(buf);
		std::wstring wExePath;
	    StringToWString(wExePath, exePath);
		int pid = proc_info.tid;
		std::string cmdLineArgs(*proc_info.cmdline);
		std::wstring wCmdLineArgs;
		StringToWString(wCmdLineArgs, cmdLineArgs);
		std::string cmd(proc_info.cmd);
		std::wstring wCmd;
		StringToWString(wCmd, cmd);
		addProcess(pid, wCmd, wExePath, wCmdLineArgs);
	}
#endif
}
