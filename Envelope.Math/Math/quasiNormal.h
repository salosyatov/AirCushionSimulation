#pragma once

#include "TPoint.h"
#include "TVector.h"


namespace EnvelopeMath {

	TVector quasiNormal(const TPoint& A, const TPoint& B,  const TPoint& C, const TPoint& D, const TPoint& E);

}
