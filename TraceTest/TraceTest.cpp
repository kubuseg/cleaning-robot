#include "CppUnitTest.h"
#include "..\DrawingMap\Trace.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TraceTest
{
	TEST_CLASS(TraceTest)
	{
	public:
		
		TEST_METHOD(getLenght)
		{
			vector<point_t> root = { {0,0}, {3,4}, {-5,10} };
			Trace tr1(root);
			Assert::AreEqual(15.0f, tr1.getLenght());
		}

		TEST_METHOD(getPoints)
		{
			vector<point_t> root = { {1,1}, {2,2}, {4,4} };
			Trace tr1(root);
			Assert::IsTrue(root == tr1.getPoints());
		}

		TEST_METHOD(addPoint)
		{
			vector<point_t> root = { {1,1}, {2,3}, {4,5} };
			Trace tr1(root);
			tr1.addPoint(6, 7);
			vector<point_t> tr2 = { {1,1}, {2,3}, {4,5}, {6, 7} };
			Assert::IsTrue(tr1 == tr2);
		}

		TEST_METHOD(deleteLastPoint)
		{
			vector<point_t> root = { {1,1}, {2,3}, {4,5} };
			Trace tr1(root);
			tr1.deleteLastPoint();
			vector<point_t> tr2 = { {1,1}, {2,3} };
			Assert::IsTrue(tr1 == tr2);
		}

		TEST_METHOD(getAmountOfPoints)
		{
			vector<point_t> root = { {1,1}, {2,3}, {4,5} };
			Trace tr1(root);
			Assert::AreEqual(3, tr1.getAmountOfPoints());
		}
	};
}
