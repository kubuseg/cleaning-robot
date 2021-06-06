#include "CppUnitTest.h"
#include "..\PolLib\Pol.h"
#include <vector>
#include <tuple>
typedef pair<int, int> point_t;
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


namespace PolTest
{
	TEST_CLASS(PolTest)
	{
	public:
		
		TEST_METHOD(GetLenght)
		{
			vector<point_t> root = { {0,0}, {3,4}, {-5,10} };
			Polygonal pol1(root);
			Assert::AreEqual(15.0f, pol1.GetLenght());
		}

		TEST_METHOD(GetPoint)
		{
			vector<point_t> root = { {1,1}, {2,3}, {4,5} };
			Polygonal pol1(root);
			Assert::AreEqual(2, pol1.GetPoint(1).first);
			Assert::AreEqual(3, pol1.GetPoint(1).second);
		}

		TEST_METHOD(GetIndex)
		{
			vector<point_t> root = { {1,1}, {2,3}, {4,5} };
			Polygonal pol1(root);
			Assert::AreEqual(1, pol1.GetIndex({ 2,3 }));
		}

		TEST_METHOD(GetAmountAfterAdd)
		{
			vector<point_t> root = { {1,1}, {2,3}, {4,5} };
			Polygonal pol1(root);
			pol1.AddPoint({6, 7});
			Assert::AreEqual(4, pol1.GetAmountOfPoints());
		}

		TEST_METHOD(AddPoint)
		{
			vector<point_t> root = { {1,1}, {2,3}, {4,5} };
			Polygonal pol1(root);
			pol1.AddPoint({6, 7});
			vector<point_t> pol2 = { {1,1}, {2,3}, {4,5}, {6, 7} };
			Assert::IsTrue(pol1==pol2);
		}

		TEST_METHOD(DeleteLastPoint)
		{
			vector<point_t> root = { {1,1}, {2,3}, {4,5} };
			Polygonal pol1(root);
			pol1.DeleteLastPoint();
			vector<point_t> pol2 = { {1,1}, {2,3} };
			Assert::IsTrue(pol1==pol2);
		}

		TEST_METHOD(AddLine)
		{
			vector<point_t> root = { {1,1}, {2,3} };
			Polygonal pol1(root);
			vector<point_t> pol2 = { {4,5}, {6, 8} };
			pol1.AddLine(pol2);
			vector<point_t> pol3 = { {1,1}, {2,3}, {4,5}, {6, 8} };
			Assert::IsTrue(pol1 == pol3);
		}

		TEST_METHOD(ChangePoint)
		{
			vector<point_t> root = { {1, 1}, {2, 3}, {4, 5} };
			Polygonal pol1(root);
			pol1.ChangePoint({2, 3}, {6, 7});
			vector<point_t> pol2 = { {1, 1}, {6, 7}, {4, 5} };
			Assert::IsTrue(pol1 == pol2);
		}

		TEST_METHOD(GetAmountOfPoints)
		{
			vector<point_t> root = { {1,1}, {2,3}, {4,5} };
			Polygonal pol1(root);
			Assert::AreEqual(3, pol1.GetAmountOfPoints());
		}

		TEST_METHOD(CheckClosed_not_cl)
		{
			vector<point_t> root = { {1,1}, {2,3}, {4,5}};
			Polygonal pol1(root);
			Assert::IsTrue(0 == pol1.CheckClosed());
		}

		TEST_METHOD(CheckClosed_cl)
		{
			vector<point_t> root = { {1,1}, {2,3}, {4,5}, {1,1} };
			Polygonal pol1(root);
			Assert::IsTrue(1 == pol1.CheckClosed());
		}

		TEST_METHOD(SplitLine)
		{
			vector<point_t>a = { {1,2}, {3,4}, {5,6}, {9,11}, {15,19} };
			point_t b = { 5, 6 };

			vector<point_t> firstt, secondd;
			tie(firstt, secondd) = SplitLine(a, b);
			vector<point_t> pol1 = { {1,1}, {2,3} };
			vector<point_t> pol2 = { {6,8}, {10,11} };
			Assert::IsTrue(firstt == pol1);
		}

	};
}
