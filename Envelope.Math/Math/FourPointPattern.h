#pragma once

#include "utils.h"
#include "PointPattern.h"

namespace EnvelopeMath {
	/**
	* @class	FourPointPattern
	*
	* @brief	аблон, состоящий из 4 точек - текущая, слева, справа, сверху.
	* 			 *
	* 			***
	*
	* @author	Vs
	* @date	17.02.2013
	*/

	class DllExport FourPointPattern : public PointPattern
	{
	private :
		TPoint p_b; // гипотетическая точка
	protected:
		TPoint p_cur;
		TPoint p_l;
		TPoint p_r; 

		TPoint p_t;

	public:
		FourPointPattern(void);
		FourPointPattern(const TPoint & cur, const TPoint & l, const TPoint & r , const TPoint & t);
		~FourPointPattern(void);

#pragma region PointPattern

				TVector GetCurvatureVec(OrientationDirection od ) const
		{
			TVector res;
			switch (od)
			{
			case HORIZONTAL:
				res = curvatureVec(p_l, p_cur, p_r, p_t);
				break;
			case VERTICAL:
				res = curvatureVec(p_b, p_cur, p_t, p_l);
				break;
			default:
				throw std::exception("TVector GetCurvatureVec(OrientationDirection od ) const");
				break;
			}
			return res;
		};

		double GetCurvature(OrientationDirection od ) const
		{
			double res;
			switch (od)
			{
			case HORIZONTAL:
				res = curvature(p_l, p_cur, p_r, p_t);
				break;
			case VERTICAL:
				res = curvature(p_b, p_cur, p_t, p_l);
				break;
			default:
				throw std::exception("double GetCurvature(OrientationDirection od ) const");
				break;
			}
			return res;
		};

		double GetEdge(SideDirection sd)  const
		{
			double res;
			switch (sd)
			{
			case LEFT:
				res = GetLeftEdge();
				break;
			case RIGHT:
				res = GetRightEdge();
				break;
			case BOTTOM:
				res = GetBottomEdge();
				break;
			case TOP:
				res = GetTopEdge();
				break;
			default:
				throw std::exception("double GetEdge(SideDirection sd)  const");
				break;
			}

			return res;
		};

		TVector GetEdgeVec(SideDirection sd)  const
		{
			TVector res;
			switch (sd)
			{
			case LEFT:
				res = GetLeftVec();
				break;
			case RIGHT:
				res = GetRightVec();
				break;
			case BOTTOM:
				res = GetBottomVec();
				break;
			case TOP:
				res = GetTopVec();
				break;
			default:
				throw std::exception("TVector GetEdgeVec(SideDirection sd)  const");
				break;
			}

			return res;		
		};

		TVector GetHorizontalCurvatureVec() const  ;

		TVector GetVerticalCurvatureVec() const  ;

		double GetHorizontalCurvature() const  ;

		double  GetVerticalCurvature() const  ;

		TVector GetNormal() const  ;

		double GetLeftEdge()  const  ;

		double GetRightEdge()  const  ;

		double GetBottomEdge()  const  ;

		double GetTopEdge()  const  ;

		TVector GetLeftVec()  const  ;

		TVector GetRightVec()  const  ;

		TVector GetBottomVec()  const  ;

		TVector GetTopVec()  const  ;
#pragma endregion
	};

}