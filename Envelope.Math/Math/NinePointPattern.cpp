#include "stdafx.h"
#include "NinePointPattern.h"

namespace EnvelopeMath {
	NinePointPattern::NinePointPattern(void)
	{
	}
	NinePointPattern::NinePointPattern(const TPoint & cur, const TPoint & l, const TPoint & r ,const TPoint & b, const TPoint & t, const TPoint & ll, const TPoint & rr ,const TPoint & bb, const TPoint & tt)
		: p_cur(cur), p_l(l), p_r(r), p_b(b), p_t(t),
		   p_ll(ll), p_rr(rr), p_bb(bb), p_tt(tt)
	{
		
	}

	NinePointPattern::~NinePointPattern(void)
	{
	}
}