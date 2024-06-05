#pragma once
#include <vector>
#include "ProcessInfo.h"

constexpr auto processes = L"processes";
constexpr auto pid = L"pid";
constexpr auto pathToExe = L"path";
constexpr auto cmdLineArgs = L"CommandLineArguments";

/** An enum type.
 *  Enum to specify the type of the operating system wanted.
 */
enum class OperatingSystem {
	WINDOWS,
	LINUX
};

/*!
* \brief ProcessWatcher Class
* Inherit this class to add more Operation to the factory.
*/
class ProcessWatcher
{
public:
	//! A constructor.
    /*!
      Input is the type of Operating system.
    */
	ProcessWatcher(const OperatingSystem& opSystem)
		: systemType(opSystem) {};
    //! A destructor.
	virtual ~ProcessWatcher() {};
	//! A pure virtual member.
	/*!
	* \brief This function returns string in JSON format for all running exes, paths to exe, to the console.
	*/
    virtual std::wstring currentProcesses() = 0;
	/*!
	* \brief This function returns vector of the running Processes.
	*/
	const std::vector<ProcessInfo>& GetRunningProcesses() const { return runningProcesses; }
	/*!
	* \brief This function returns operating system type enum.
	*/
	const OperatingSystem& GetCurrentOperatingSystem() const { return systemType; }
	/*!
	* \brief This function adds process to the container.
	*/
	void addProcess(const int& pid, const std::wstring& exeName, const std::wstring& path, const std::wstring& cmdArgs);
	/*!
	* \brief This function returns process structure as JSON string.
	*/
	std::wstring JSONProcessesString() const;
 protected:
	 OperatingSystem systemType;
	 std::vector<ProcessInfo> runningProcesses; /*!< a vector to hold running Processes and Info */
};