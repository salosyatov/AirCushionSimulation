#pragma once

#include "TPoint.h"
#include "TVector.h"


namespace EnvelopeMath {

	/**
	 * @fn	DllExport double quasiCurvature(const TPoint& A, const TPoint& B, const TPoint& C,
	 * 		const TPoint& D);
	 *
	 * @brief	кривизна (модуль) - величина, обратная радиусу кривизны.
	 *
	 * @author	Vs
	 * @date	23.05.2013
	 *
	 * @param	A	The const TPoint&amp; to process.
	 * @param	B	The const TPoint&amp; to process.
	 * @param	C	The const TPoint&amp; to process.
	 * @param	D	The const TPoint&amp; to process.
	 *
	 * @return	.
	 */

	DllExport double quasiCurvature(const TPoint& A, const TPoint& B,  const TPoint& C, const TPoint& D);
}