#include "stdafx.h"
#include "Forces.h"

namespace EnvelopeCore {

	void CalculateFlexural(const Node & n_cur_rest, const PointPattern & pattern, const double & kb_hor, const double & kb_ver, TVector & f_cur, TVector & f_l, TVector & f_r, TVector & f_b, TVector & f_t ) 
	{
		double sign = 1.0;

		TVector fl_l = sign * kb_hor * pattern.GetTorqueForce(LEFT);
		TVector fl_r = sign * kb_hor * pattern.GetTorqueForce(RIGHT);

		TVector fl_b = sign * kb_ver * pattern.GetTorqueForce(BOTTOM);
		TVector fl_t = sign * kb_ver * pattern.GetTorqueForce(TOP);
		f_cur = - (fl_l + fl_r) - (fl_b + fl_t);

		f_l = fl_l;
		f_r = fl_r;
		f_b = fl_b;
		f_t = fl_t;


	}
}
