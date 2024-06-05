#include "gtest/gtest.h"
#include "OperationFactory.h"
#include <memory>

class CalculationEngineTest: public testing::Test{
	protected:
		virtual void SetUp()
		{
			//
 			OperationFactory::OperationType eOperationType = OperationFactory::OperationType::PROCESS_WATCHER;
			zEngine = OperationFactory::createOperation(eOperationType);		
		}

		virtual void TearDown(){
		}

		std::unique_ptr<ProcessWatcher> zEngine;
};

TEST_F(CalculationEngineTest, testNullptr)
{
	ASSERT_NE(nullptr, zEngine.get());
}

TEST_F(CalculationEngineTest, testGetProcesses)
{
	ASSERT_NE(nullptr, zEngine.get());
	std::ignore = zEngine->currentProcesses();
	auto vecProcesses = zEngine->GetRunningProcesses();
	EXPECT_GT(vecProcesses.size(), 0);
}

TEST_F(CalculationEngineTest, testGetJSONString)
{
	ASSERT_NE(nullptr, zEngine.get());
	auto wJsonString = zEngine->currentProcesses();
	EXPECT_TRUE(wJsonString.size());
}

TEST_F(CalculationEngineTest, testPid)
{
	ASSERT_NE(nullptr, zEngine.get());
	std::ignore = zEngine->currentProcesses();
	auto vecProcesses = zEngine->GetRunningProcesses();
	for (int i = 0; i < vecProcesses.size(); i++)
	{
		EXPECT_GT(vecProcesses[i].GetPid(), -1);
	}
}

TEST_F(CalculationEngineTest, testExeName)
{
	ASSERT_NE(nullptr, zEngine.get());
	std::ignore = zEngine->currentProcesses();
	auto vecProcesses = zEngine->GetRunningProcesses();
	for (int i = 0; i < vecProcesses.size(); i++)
	{
		EXPECT_GT(vecProcesses[i].GetExeName().size(), 0);
	}
}

TEST_F(CalculationEngineTest, testExePath)
{
	ASSERT_NE(nullptr, zEngine.get());
	std::ignore = zEngine->currentProcesses();
	auto vecProcesses = zEngine->GetRunningProcesses();
	for (int i = 0; i < vecProcesses.size(); i++)
	{
		EXPECT_GT(vecProcesses[i].GetPath().size(), 0);
	}
}