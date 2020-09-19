#include "stdafx.h"
#include "FivePointPattern.h"

namespace EnvelopeMath {
	FivePointPattern :: FivePointPattern(void)
	{

	}

	FivePointPattern :: FivePointPattern(const TPoint & p_cur, const TPoint & p_l, const TPoint & p_r, const TPoint & p_b, const TPoint & p_t)
		: p_cur(p_cur), p_l(p_l), p_r(p_r), p_b(p_b), p_t(p_t)
	{

	}


	FivePointPattern :: ~FivePointPattern(void)
	{

	}

	
		/**
		* @fn TVector FivePointPattern::GetHorizontalCurvature() const
		*
		* @brief Gets horizontal curvature.
		*
		* @author Vasily Salosyatov
		* @date 06.12.2012
		*
		* @return The horizontal curvature.
		*/

		TVector FivePointPattern :: GetHorizontalCurvatureVec() const
		{
			return curvatureVec(p_l, p_cur, p_r, p_t);
		};

		/**
		* @fn TVector FivePointPattern::GetVerticalCurvature()const
		*
		* @brief Gets vertical curvature.
		*
		* @author Vasily Salosyatov
		* @date 06.12.2012
		*
		* @return The vertical curvature.
		*/

		TVector FivePointPattern :: GetVerticalCurvatureVec() const
		{
			return curvatureVec(p_b, p_cur, p_t, p_l);
		};

		double FivePointPattern :: GetHorizontalCurvature() const
		{
			return curvature(p_l, p_cur, p_r, p_t);
		};

		double FivePointPattern :: GetVerticalCurvature() const
		{
			return curvature(p_b, p_cur, p_t, p_l);
		};


		/**
		* @fn	TVector FivePointPattern::GetNormal() const
		*
		* @brief	Gets the normal.
		*
		* @author	Vs
		* @date	07.02.2013
		*
		* @return	The normal.
		*/

		TVector FivePointPattern :: GetNormal() const
		{
			return normal(p_cur, p_l, p_r, p_b, p_t);
		};

		double FivePointPattern :: GetLeftEdge()  const {
			return d(p_l, p_cur);
		};

		double FivePointPattern :: GetRightEdge()  const {
			return d(p_r, p_cur);
		};

		double FivePointPattern :: GetBottomEdge()  const {
			return d(p_b, p_cur);
		};

		double FivePointPattern :: GetTopEdge()  const {
			return d(p_t, p_cur);
		};

		TVector FivePointPattern :: GetLeftVec()  const {
			return (p_l - p_cur);
		};

		TVector FivePointPattern :: GetRightVec()  const {
			return (p_r - p_cur);
		};

		TVector FivePointPattern ::  GetBottomVec()  const {
			return (p_b - p_cur);
		};

		TVector FivePointPattern :: GetTopVec()  const {
			return (p_t - p_cur);
		};
}