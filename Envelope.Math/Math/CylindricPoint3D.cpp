#include "stdafx.h"
#include "CylindricPoint3D.h"

namespace EnvelopeMath {
	CylindricPoint3D::CylindricPoint3D(void)
	{
	}
	CylindricPoint3D::CylindricPoint3D( double _r, double _phi, double _zeta): r(_r), phi(_phi), zeta(_zeta)
	{
	}

	CylindricPoint3D::~CylindricPoint3D(void)
	{
	}

	TPoint CylindricPoint3D::ToCartesian() const
	{
		TPoint p(r * cos(phi), r * sin(phi), zeta);
		return p;
	}
}