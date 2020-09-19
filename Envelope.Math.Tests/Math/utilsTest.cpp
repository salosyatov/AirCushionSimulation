#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EnvelopeMathTest
{
	TEST_CLASS(utilsTest)
	{
	public:
/*
		TEST_METHOD(testCurvature)
		{
			TPoint a(-1., -1., -1.), b , c (1., 1., 1.);
			double curv = curvature(a, b, c);
			Assert::AreEqual(0.0, curv);

			// TODO: Your test code here
		}
*/
		TEST_METHOD(testCurvatureFirstQuarter)
		{
		//	TPoint cur, l(-1.0 , 1.0, 0), r(1.0, 1.0, 0), b (0, 0, -2.), t(0., 0., 1.);

			TPoint l(1, 0, -6), cur(0.7, 0.8, -6), r(0, 1, -6), t(0., 0., 1.);

			double curv = curvature(l, cur, r, t);
			//	const wchar_t mes[] = "Curvature <= 0";
			bool actual = curv > 0;
			Assert::AreEqual(true, actual);

		}

		TEST_METHOD(testCurvatureThirdQuarter)
		{
			TPoint l(- 1, 0, -6), cur(- 0.7, - 0.8, -6), r(0, - 1, -6), t(0., 0., 1.);

			double curv = curvature(l, cur, r, t);
			//	const wchar_t mes[] = "Curvature <= 0";
			bool actual = curv > 0;
			Assert::AreEqual(true, actual);

		}

		TEST_METHOD(testCurvatureThirdQuarterNegative)
		{
			TPoint l(- 1, 0, -6), cur(- 0.4, - 0.3, -6), r(0, - 1, -6), t(0., 0., 1.);

			double curv = curvature(l, cur, r, t);
			//	const wchar_t mes[] = "Curvature <= 0";
			bool actual = curv < 0;
			Assert::AreEqual(true, actual);

		}



		//плоскость
		TEST_METHOD(testNormalFlat)
		{
			TPoint c, l(-1. , 0, 0), r(2, 0, 0), b (0, 0, -2.), t(0., 0., 1.);
			TVector n = normal(c, l, r, b, t);
			TVector expected(0., -1. , 0.);
			Assert::AreEqual( 1, expected == n);

		}

		TEST_METHOD(testNormalLineCircle)
		{
			TPoint cur, l(-1.0 , 1.0, 0), r(1.0, 1.0, 0), b (0, 0, -2.), t(0., 0., 1.);
			TVector n = normal(cur, l, r, b, t);

//			TVector hor = - curvatureVec(l, cur, r);
//			TVector ver = - curvatureVec(b, cur, t);
//			n = hor + ver;
//			n.normalize();

			TVector expected(0., -1. , 0.);
			Assert::AreEqual( 1, expected == n);

		}


	};
}