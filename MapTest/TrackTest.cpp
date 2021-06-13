#include "CppUnitTest.h"
#include "..\DrawingMap\Track.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TrackTest
{
	TEST_CLASS(TrackTest)
	{
	public:

		TEST_METHOD(Test2)
		{
			Assert::IsTrue(1 == 1);
		}

		TEST_METHOD(emptyConstructor)
		{
			Track tr1({});
			Assert::AreEqual(tr1.getAmountOfPoints(), 0);
		}

		TEST_METHOD(constructor)
		{
			vector<Point> root = { {0,0}, {3,4}, {5,10} };
			Track tr1(root);
			Assert::AreEqual(tr1.getAmountOfPoints(), 3);
			Assert::IsTrue(tr1==root);
		}

		TEST_METHOD(getPoints)
		{
			vector<Point> root = { {1,1}, {2,2}, {4,4} };
			Track tr1(root);
			vector<Point> points = tr1.getPoints();
			Assert::IsTrue(points == root);
		}

		TEST_METHOD(getAmountOfPoints)
		{
			vector<Point> root = { {1,1}, {2,3}, {4,5} };
			Track tr1(root);
			Assert::AreEqual(3, tr1.getAmountOfPoints());
		}

		TEST_METHOD(addPoint)
		{
			vector<Point> root = { {1,1}, {2,3}, {4,5} };
			Track tr1(root);
			tr1.addPoint({ 6, 7 });
			vector<Point> v2 = { {1,1}, {2,3}, {4,5}, {6, 7} };
			Assert::IsTrue(tr1 == v2);
		}

		TEST_METHOD(deleteLastPoint)
		{
			vector<Point> root = { {1,1}, {2,3}, {4,5} };
			Track tr1(root);
			tr1.deleteLastPoint();
			vector<Point> v2 = { {1,1}, {2,3} };
			Assert::IsTrue(tr1 == v2);
		}

		TEST_METHOD(step)
		{
			int x0 = 5, y0 = 2;
			Track tr1({});
			Direction dir = Direction::Down;
			Point p1 = tr1.step(x0, y0, dir);
			Point p2 = { 5, 3 };
			Assert::IsTrue(p1 == p2);
		}
	};
};