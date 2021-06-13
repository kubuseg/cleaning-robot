#include "CppUnitTest.h"
#include "..\DrawingMap\Map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace MapTest
{
	TEST_CLASS(MapTest)
	{
	public:

		TEST_METHOD(ConstructorAndGet)
		{
			vector<vector<int>> m2 = { {1,1,1,1}, {1,0,0,0}, {1,0,0,0} };
			int size_r = m2.size();
			int size_c = m2[0].size();
			Map m1(m2);
			Assert::IsTrue(m1.getMap() == m2);
			Assert::IsTrue(m1.getRows() == size_r);
			Assert::IsTrue(m1.getColumns() == size_c);
		}

		TEST_METHOD(SetMap)
		{
			vector<vector<int>> m2 = { {0,0,1,0}, {0,1,0,0}, {0,1,0,1} };
			Map m1(m2);
			vector<vector<int>> m3 = { {1,1,1,1}, {0,1,1,0}, {0,0,1,0} };
			m1.setMap(m3);
			Assert::IsTrue(m1.getMap() == m3);
		}

		TEST_METHOD(SetValue)
		{
			vector<vector<int>> m2 = { {0,0,1,0}, {0,1,0,0}, {0,1,0,1} };
			Map m1(m2);
			m1.setValue(1, 0, 5);
			vector<vector<int>> m3 = { {0,0,1,0}, {5,1,0,0}, {0,1,0,1} };
			Assert::IsTrue(m1.getMap() == m3);
		}

		TEST_METHOD(AddWalls)
		{
			vector<vector<int>> m2 = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
			Map m1(m2);
			m1.addWalls();
			vector<vector<int>> m3 = { 
				{1,1,1,1}, 
				{1,0,0,1}, 
				{1,1,1,1} };
			Assert::IsTrue(m1.getMap() == m3);
		}

		TEST_METHOD(AddObstacle)
		{
			vector<vector<int>> m2 = { {0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0} };
			Map m1(m2);
			m1.addObstacle(1, 1, 2, 3);
			vector<vector<int>> m3 = {
				{0,0,0,0},
				{0,1,1,0}, 
				{0,1,1,0}, 
				{0,1,1,0} };
			Assert::IsTrue(m1.getMap() == m3);
		}

		TEST_METHOD(CheckIfAllCleaned)
		{
			vector<vector<int>> m2 = { {1,1,1,1}, {0,0,0,0}, {1,1,1,1}, {0,1,0,1} };
			Map m1(m2);
			Assert::IsTrue(m1.checkIfAllCleaned() == 0);
		}
	};
}
