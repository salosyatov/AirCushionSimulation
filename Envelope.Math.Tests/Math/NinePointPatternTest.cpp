#include "stdafx.h"
#include "CppUnitTest.h"

#include "NinePointPattern.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace EnvelopeMathTest
{
	TEST_CLASS(NinePointPatternTest)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			const int N = 5;
			TPoint pp[N][N];
			for (int i = 0; i < N; i++)
			{
				for (int j = 0; j < N; j++)
				{
					pp[i][j].x = i;
					pp[i][j].y = j;
				}
			}

			int i(2), j(2);
			int i_l = i - 1;
			int i_r = i + 1;

			int i_ll = i_l - 1;
			int i_rr = i_r + 1;

			int j_b = j - 1;
			int j_t = j + 1 ;

			int j_bb = j - 2;
			int j_tt = j + 2;


			TPoint p_cur = pp[i][i];
			TPoint p_l = pp[i_l][j];
			TPoint p_r = pp[i_r][j];
			TPoint p_t = pp[i][j_t];
			TPoint p_b = pp[i][j_b];

			TPoint p_ll = pp[i_ll][j];
			TPoint p_rr = pp[i_rr][j];
			TPoint p_tt = pp[i][j_tt];
			TPoint p_bb = pp[i][j_bb];

	

			EnvelopeMath::NinePointPattern pattern(p_cur, p_l, p_r, p_b, p_t, p_ll, p_rr, p_bb, p_tt);

			double expected(0.0);
			// System::String message = "HORIZONTAL, LEFT";
			Assert::AreEqual(expected, pattern.GetCurvature(HORIZONTAL, LEFT));


		}

	};
}