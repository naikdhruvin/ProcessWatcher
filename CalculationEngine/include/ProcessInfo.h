#pragma once
#include <string>
/*!
* \brief ProcessInfo Class
* this class contains information about the process like id, exe name etc .. .
*/
class ProcessInfo
{
public:
	//! A constructor.
	/*!
	* \param id- process id
	* \param exe- Name of the exe
	* \param path- Path to the exe
	* \param args- command line arguments to the exe.
	*/
	ProcessInfo(const int& id, const std::wstring& exe, const std::wstring& path, const std::wstring& args)
		: pid(id), exeName(exe), pathToExe(path), cmdLineArgs(args) {};
	//! A destructor.
	virtual ~ProcessInfo() {};
	/*!
	* \brief This function returns process ID.
	*/
	int GetPid() const { return pid; }
	/*!
	* \brief This function returns path where executable is located.
	*/
	std::wstring GetPath() const { return pathToExe; }
	/*!
	* \brief This function returns commandLineArguments to exe.
	*/
	std::wstring GetCmdLineArgs() const { return cmdLineArgs; }
	/*!
	* \brief This function returns exe name.
	*/
	std::wstring GetExeName() const { return exeName; }
private:
	const int pid; /*!< an integer to hold process id */
	const std::wstring exeName; /*!< a string to hold exe name */
	const std::wstring pathToExe; /*!< a string to hold path to exe */
	const std::wstring cmdLineArgs; /*!< a string to hold command line args to exe */
};