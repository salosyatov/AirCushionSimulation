#include "stdafx.h"
#include "FourPointPattern.h"

namespace EnvelopeMath {
	FourPointPattern::FourPointPattern(void)
	{
	}

	FourPointPattern :: FourPointPattern(const TPoint & cur, const TPoint & l, const TPoint & r , const TPoint & t)
		: p_cur(cur), p_l(l), p_r(r), p_t(t)
	{
		p_b = p_cur - (p_t - p_cur);
	}

	FourPointPattern :: ~FourPointPattern(void)
	{
	}

	TVector FourPointPattern :: GetHorizontalCurvatureVec() const
	{
		return curvatureVec(p_l, p_cur, p_r, p_t);
	};

	double FourPointPattern :: GetHorizontalCurvature() const
	{
		return curvature(p_l, p_cur, p_r, p_t);
	};

	TVector FourPointPattern :: GetVerticalCurvatureVec() const {
		return TVector(0.0, 0.0, 0.0);
	};

	double FourPointPattern ::  GetVerticalCurvature() const {

		return 0.0;
	};

	TVector FourPointPattern :: GetNormal() const
	{
		return normal(p_cur, p_l, p_r, p_cur - (p_t - p_cur), p_t);
	};

	double FourPointPattern :: GetLeftEdge()  const {
		return d(p_l, p_cur);
	};

	double FourPointPattern :: GetRightEdge()  const {
		return d(p_r, p_cur);
	};

	double FourPointPattern :: GetBottomEdge()  const {
		return 0.0;
	};

	double FourPointPattern :: GetTopEdge()  const {
		return d(p_t, p_cur);
	};


	TVector FourPointPattern :: GetLeftVec()  const {
		return (p_l - p_cur);
	};

	TVector FourPointPattern :: GetRightVec()  const {
		return (p_r - p_cur);
	};

	TVector FourPointPattern :: GetBottomVec()  const {
		return TVector(0.0, 0.0, 0.0); 
	};

	TVector FourPointPattern :: GetTopVec()  const {
		return (p_t - p_cur);
	};
}
