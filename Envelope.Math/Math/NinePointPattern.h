#pragma once
#include "utils.h"
#include "BigPointPattern.h"
//#include "FivePointPattern.h"

namespace EnvelopeMath {
	/**
	* @class	NinePointPattern
	*
	* @brief	аблон, состоящий из 9 точек.
	* 			  *
	* 			  *
	* 			*****
	* 			  *
	* 			  *
	*
	* @author	Vs
	* @date	05.04.2013
	*/

	class DllExport NinePointPattern : public BigPointPattern
	{
	protected:
		TPoint p_cur;

		TPoint p_l;
		TPoint p_r; 
		TPoint p_b;
		TPoint p_t;

	protected:
		TPoint p_ll;
		TPoint p_rr;
		TPoint p_bb;
		TPoint p_tt;

	public:
		NinePointPattern(void);
		NinePointPattern(const TPoint & cur, const TPoint & l, const TPoint & r ,const TPoint & b, const TPoint & t, const TPoint & ll, const TPoint & rr ,const TPoint & bb, const TPoint & tt);
		~NinePointPattern(void);

		TVector GetCurvatureVec(OrientationDirection od, SideDirection sd ) const 
		{
			TVector res;
			switch (od)
			{
			case HORIZONTAL:
				switch (sd)
				{
				case LEFT:
					res = curvatureVec(p_ll , p_l, p_cur, p_t);
					break;
				case RIGHT:
					res = curvatureVec(p_cur, p_r, p_rr , p_t);
					break;
				case BOTTOM:
					throw std::exception ("GetCurvatureVec - incompatible directions");
					break;
				case TOP:
					throw std::exception ("GetCurvatureVec - incompatible directions");
					break;
				default:
					throw std::exception ("GetCurvatureVec - unknown SideDirection");
					break;
				}
				break;

			case VERTICAL:
				switch (sd)
				{
				case LEFT:
					throw std::exception ("GetCurvatureVec - incompatible directions");
					break;
				case RIGHT:
					throw std::exception ("GetCurvatureVec - incompatible directions");
					break;
				case BOTTOM:
					res = curvatureVec(p_bb , p_b , p_cur, p_l );
					break;
				case TOP:
					res = curvatureVec(p_cur, p_t, p_tt, p_l);
					break;
				default:
					throw std::exception ("GetCurvatureVec - unknown SideDirection");
					break;
				}
				break;
			default:
				throw std::exception ("GetCurvatureVec - unknown OrientationDirection");
				break;
			}

			return res;
		};

		double GetCurvature(OrientationDirection od, SideDirection sd) const 
		{
			double res;
			switch (od)
			{
			case HORIZONTAL:
				switch (sd)
				{
				case LEFT:
					res = curvature(p_ll , p_l, p_cur, p_t);
					break;
				case RIGHT:
					res = curvature(p_cur, p_r, p_rr , p_t);
					break;
				case BOTTOM:
					throw std::exception ("GetCurvature - incompatible directions");
					break;
				case TOP:
					throw std::exception ("GetCurvature - incompatible directions");
					break;
				default:
					throw std::exception ("GetCurvature - unknown SideDirection");
					break;
				}
				break;

			case VERTICAL:
				switch (sd)
				{
				case LEFT:
					throw std::exception ("GetCurvature - incompatible directions");
					break;
				case RIGHT:
					throw std::exception ("GetCurvature - incompatible directions");
					break;
				case BOTTOM:
					res = curvature(p_bb , p_b , p_cur, p_l );
					break;
				case TOP:
					res = curvature(p_cur, p_t, p_tt, p_l);
					break;
				default:
					throw std::exception ("GetCurvature - unknown SideDirection");
					break;
				}
				break;
			default:
				throw std::exception ("GetCurvature - unknown OrientationDirection");
				break;
			}

			return res;
		};
	};
}
