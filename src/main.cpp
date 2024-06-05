// 
//
#include <iostream>
#include <vector>
#include <string>  
#include <sstream>
#include <fstream>
#include "OperationFactory.h"

int main(int argc, char* argv[])
{
	//
	// Engine test 
	//
	OperationFactory::OperationType eOperationType = OperationFactory::OperationType::PROCESS_WATCHER;
	auto zEngine = OperationFactory::createOperation(eOperationType);

	if(!zEngine.get())
		return 0;

	auto jsonString = zEngine->currentProcesses();
	std::wcout << jsonString << std::endl;
	// Write json to file.
	std::string fileToSave = "processwatcher.json";
	std::wofstream f(fileToSave);
	f << jsonString;
	f.close();
 
    return 0;
}