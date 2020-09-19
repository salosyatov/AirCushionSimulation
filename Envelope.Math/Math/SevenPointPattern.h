#pragma once

#include "utils.h"
#include "BigPointPattern.h"

namespace EnvelopeMath {
	/**
	* @class	SevenPointPattern
	*
	* @brief	������, ��������� �� 9 �����.
	* 			  *
	* 			  *
	* 			*****
	*
	* @author	Vs
	* @date	05.04.2013
	*/

	class DllExport SevenPointPattern : public BigPointPattern
	{
	protected:
		TPoint p_cur;

		TPoint p_l;
		TPoint p_r; 
		TPoint p_t;

	protected:
		TPoint p_ll;
		TPoint p_rr;
		TPoint p_tt;
	public:
		SevenPointPattern(void);
		SevenPointPattern(const TPoint & cur, const TPoint & l, const TPoint & r , const TPoint & t, const TPoint & ll, const TPoint & rr, const TPoint & tt);
		~SevenPointPattern(void);

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
					// ������� ������
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
					res = 0.0;
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