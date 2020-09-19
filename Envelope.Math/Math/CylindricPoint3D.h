#pragma once
#include "TPoint.h"

namespace EnvelopeMath {

	/**
	 * @class	CylindricPoint3D
	 *
	 * @brief	“очка в цилиндрической системе координат.
	 *
	 * @author	Vs
	 * @date	20.03.2013
	 */

	class DllExport CylindricPoint3D
	{
		double r;
		double phi;
		double zeta;
	public:
		CylindricPoint3D(void);
		CylindricPoint3D( double _r, double _phi, double _zeta);
		~CylindricPoint3D(void);

		/**
		 * @fn	TPoint CylindricPoint3D::ToCartesian() const;
		 *
		 * @brief	Converts this object to a cartesian.
		 *
		 * @author	Vs
		 * @date	20.03.2013
		 *
		 * @return	This object as a TPoint.
		 */

		TPoint ToCartesian() const;
	};
}
