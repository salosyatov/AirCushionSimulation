#pragma once

#include "TPoint.h"
#include "TVector.h"

namespace EnvelopeMath {

	class DllExport PointPattern
	{
	public:
		PointPattern(void);
		~PointPattern(void);

		virtual double GetCurvature(OrientationDirection od ) const = 0;

		virtual TVector GetCurvatureVec(OrientationDirection od ) const = 0;	

		virtual double GetEdge(SideDirection sd)  const = 0;

		virtual  TVector GetEdgeVec(SideDirection sd)  const = 0;

		TVector GetTorqueForce(SideDirection sd)  const 
		{
			TVector c;
			OrientationDirection od;

			switch (sd)
			{
			case LEFT:
				od = HORIZONTAL;
				break;
			case RIGHT:
				od = HORIZONTAL;
				break;
			case BOTTOM:
				od = VERTICAL;
				break;
			case TOP:
				od = VERTICAL;
				break;
			default:
				throw std::exception("TVector GetTorqueForce(SideDirection sd)  const ");
				break;
			}
			c = GetCurvatureVec(od);
			TVector r = GetEdgeVec(sd);
			TVector M = - r ^ c ;
			
			TVector F = M ^ r ;

			F.normalize();
			double curv = c.len();
			double edge = r.len();

			if (edge == 0.0)
			{
				F *= 0.0;
			}
			else
			{
				F *=  curv/edge ;
			}
			
			return F;
		
		};

		virtual TVector GetNormal() const = 0;

		virtual double GetLeftEdge()  const = 0;

		virtual double GetRightEdge()  const = 0;

		virtual double GetBottomEdge()  const = 0;

		virtual double GetTopEdge()  const = 0;

		virtual TVector GetLeftVec()  const = 0;

		virtual TVector GetRightVec()  const = 0;

		virtual TVector GetBottomVec()  const = 0;

		virtual TVector GetTopVec()  const = 0;

	};

}