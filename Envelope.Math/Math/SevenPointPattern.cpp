#include "stdafx.h"
#include "SevenPointPattern.h"

namespace EnvelopeMath {
	SevenPointPattern::SevenPointPattern(void)
	{
	}

	SevenPointPattern::SevenPointPattern(const TPoint & cur, const TPoint & l, const TPoint & r , const TPoint & t, const TPoint & ll, const TPoint & rr, const TPoint & tt)
		: p_cur(cur), p_l(l), p_r(r), p_t(t),
		p_ll(ll), p_rr(rr), p_tt(tt)
	{
	}
	SevenPointPattern::~SevenPointPattern(void)
	{
	}
}