#include "stdafx.h"
#include "quasiNormal.h"

namespace EnvelopeMath {

	TVector quasiNormal(const TPoint& cur, const TPoint& l,  const TPoint& r, const TPoint& b, const TPoint& t)
	{
		TVector n1 = (t - cur)^(l - cur);
		TVector n2 = (r - cur)^(t - cur);
		TVector n3 = (b - cur)^(r - cur);
		TVector n4 = (l - cur)^(b - cur);
		TVector n = n1.normalized() + n2.normalized() + n3.normalized() + n4.normalized(); //по идее, эти нормали нужно нормировать, но мы считаем, что ребра примерно равны
		n.normalize();

		return n;

	}


}