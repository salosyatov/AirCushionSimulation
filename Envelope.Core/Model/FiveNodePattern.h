#pragma once
#include "Envelope.Math.Consts.h"
#include "Node.h"


namespace EnvelopeCore {
	class FiveNodePattern
	{
	protected:
		Node n_cur;
		Node n_l;
		Node n_r; 
		Node n_b;
		Node n_t;

	public:
		FiveNodePattern(void);
		FiveNodePattern(const Node & n_cur, const Node & n_l, const Node & n_r ,const Node & n_b, const Node & n_t);
		~FiveNodePattern(void);

		double GetCurvature(OrientationDirection od, SideDirection sd) const 
		{
			double res;
			switch (od)
			{
			case HORIZONTAL:
				switch (sd)
				{
				case LEFT:
					res = n_l.C_hor;
					break;
				case RIGHT:
					res = n_r.C_hor;
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
					res = n_b.C_ver;
					break;
				case TOP:
					res = n_t.C_ver;
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