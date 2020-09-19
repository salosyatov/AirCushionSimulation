#pragma once

#include "Envelope.Math.Consts.h"

#include "TPoint.h"
#include "TVector.h"

namespace EnvelopeMath {

	class DllExport BigPointPattern
	{
	public:
		BigPointPattern(void);
		~BigPointPattern(void);

		virtual TVector GetCurvatureVec(OrientationDirection od, SideDirection sd ) const = 0;

		virtual double GetCurvature(OrientationDirection od, SideDirection sd) const = 0;

	};
}
