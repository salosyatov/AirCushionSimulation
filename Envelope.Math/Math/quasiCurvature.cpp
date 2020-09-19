#include "stdafx.h"
#include "quasiCurvature.h"

namespace EnvelopeMath {


	double quasiCurvature(const TPoint& A, const TPoint& B,  const TPoint& C, const TPoint& D)
	{
		TVector l1 = A - B;
		TVector l2 = C - B;

		double lenL1 = l1.len();
		double lenL2 = l2.len();


		double l = 0.5 * (lenL1 + lenL2);
		double len12 =  lenL1 * lenL2;
		double cos_alpha;

		double res = 0.0;
		if (len12 == 0.0)
		{
			throw std::exception("quasiCurvature : points match");
		}


		cos_alpha = dot(l1, l2) / len12;
		if (cos_alpha > -1.0)
		{
			res = sqrt(2.0 * (1.0 + cos_alpha )  )  / l; 
		}

		double d = dot3( A - B, D - B,  l1 + l2) ;
		res *= sgn(d);

		return res;
	}

}