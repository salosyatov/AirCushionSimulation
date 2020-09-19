#include "stdafx.h"
#include "FiveNodePattern.h"

namespace EnvelopeCore {
	FiveNodePattern::FiveNodePattern(void)
	{
	}

	FiveNodePattern::FiveNodePattern(const Node & n_cur, const Node & n_l, const Node & n_r , const Node & n_b, const Node & n_t)
		: n_cur(n_cur), n_l(n_l), n_r(n_r), n_b(n_b), n_t(n_t)
	{
	}

	FiveNodePattern::~FiveNodePattern(void)
	{
	}
}