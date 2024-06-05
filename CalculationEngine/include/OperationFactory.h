#pragma once

#include "WindowsProcessWatcher.h"
#include "LinuxProcessWatcher.h"

#include <memory>
/*!
* \brief OperationFactory Class
*/
class OperationFactory {
public:
    /** An enum type. 
     *  Enum to specify the type of the operation wanted.
     */
	enum class OperationType {
		PROCESS_WATCHER = 0,		/**< 0 */
		PROCESS_KILLER=1,     	/**< 1 */
	};
	
 	/*!
	* \brief This function returns the unique pointer of the Operation
	* \param OperationType- Desired Operation type
	*/ 
	static std::unique_ptr<ProcessWatcher> createOperation(OperationType OperationType)
	{
		switch (OperationType) {
		case OperationType::PROCESS_WATCHER:
		{
#ifdef WIN32
			return std::make_unique<WindowsProcessWatcher>();
#else
			return std::make_unique<LinuxProcessWatcher>();
#endif
		}
		}
		throw "invalid Operation type.";
	}
};
