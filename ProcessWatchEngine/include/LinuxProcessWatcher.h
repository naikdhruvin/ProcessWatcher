#pragma once
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <memory>
#include <functional>
#ifndef WIN32
#include <proc/readproc.h>
#endif // !WIN32
#include "ProcessWatcher.h"

/*!
* \brief LinuxProcessWatcher Class
*/

class LinuxProcessWatcher : public ProcessWatcher  {
public:
    //! A constructor.
	LinuxProcessWatcher();

	//! A virtual member.
	/*!
	 \brief This function returns string in JSON format for all running exes on windows platform, paths to exe, to the console.
	*/
	virtual std::wstring currentProcesses();
private:
	//! A private member.
	/*!
	\brief This function gets all the running processes on the system and populates the runningProcesses structure.
	*/
	void populateProcesses();
};
