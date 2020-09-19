
#include "stdafx.h"
#include "utils.h"

#include <cmath>

#define  EPSILON DBL_EPSILON

namespace EnvelopeMath {

	double area(const TPoint& A, const TPoint&  B,  const TPoint& C)  // area
	{
		return 0.5 * ((B-A)^(C-A)).len();
	}

	double curvature(const TPoint& A, const TPoint& B,  const TPoint& C, const TPoint& D)
	{
		TPoint O;
		if (!curvatureCentre(A, B, C, O))
		{
			double d = dot3( A - B, D - B,  O - B) ;
			
			return sgn(d) / (B - O).len();
		}
		else
			return 0.0;

	}

	TVector curvatureVec(const TPoint& A, const TPoint& B,  const TPoint& C, const TPoint& D)
	{

		double curv = curvature(A, B, C, D);
		TVector n = curvatureVecNormalized(A, B, C);

		return  fabs(curv) * n; //TODO: определиться, нужно ли учитывать знак

	}

	bool curvatureCentre(const TPoint& A, const TPoint& B,  const TPoint& C, TPoint& O )
	{
#pragma region 
		bool xDef = false, yDef = false, zDef = false; // признаки определения координат точки O (центра описанной окружности)
		double kBA = 0, kBC = 0;
		// Определяем векторы и нормали к сторонам
		TVector BA = A - B, BC = C - B, n = BA^BC, nBA = n^BA, nBC = n^BC;
		// Проверка на принадлежность одной прямой (находим площадь параллелограмма, построенного на векторах).                                
		// Определяем середины сторон
		TPoint D = (A + B)*0.5, E = (B + C)*0.5;  		

		if (n.len() <= EPSILON)
		{
			// Площадь меньше погрешности, значит точки лежат на одной прямой
			O = B;
			return true;
		} 
		else
		{
			// Считаем дальше
			// Проверка нормали nBA на перпендикулярность OX
			if (fabs(nBA.x) <= EPSILON)
			{
				O.x = D.x;
				xDef = true;
			}
			// Проверка нормали nBA на перпендикулярность OY
			if (fabs(nBA.y) <= EPSILON)
			{
				O.y = D.y;
				yDef = true;
			}
			// Проверка нормали nBA на перпендикулярность OZ
			if (fabs(nBA.z) <= EPSILON)
			{
				O.z = D.z;
				zDef = true;
			}

			// Проверка нормали nBC на перпендикулярность OX
			if (fabs(nBC.x) <= EPSILON && !xDef)
			{
				O.x = E.x;
				xDef = true;
			}
			// Проверка нормали nBC на перпендикулярность OY
			if (fabs(nBC.y) <= EPSILON && !yDef)
			{
				O.y = E.y;
				yDef = true;
			}
			// Проверка нормали nBC на перпендикулярность OZ
			if (fabs(nBC.z) <= EPSILON && !zDef)
			{
				O.z = E.z;
				zDef = true;
			}
			/* Что можно определили. Теперь определяем остальное. Собственно варианты: 
			а) не определена какая-нибудь одна из координат - существует 4 способа её выразить через известные (хоть в одном будут не нулевые коэффициенты)
			б) определена какая-нибудь одна из координат - решаем систему линейных уранвнений, состоящих из неивестных координат
			в) не определено ничего - опять же решение системы уравнений
			д) собствено определено всё 
			*/
			// Реализуем пункт а)
			if (!(xDef && yDef && zDef))
				if (xDef && yDef && !zDef) // Не определена только O.z
				{
					if (fabs(nBA.x) > EPSILON)
						O.z = nBA.z/nBA.x*(O.x - D.x) + D.z;
					else 
						if (fabs(nBA.y) > EPSILON)
							O.z = nBA.z/nBA.y*(O.y - D.y) + D.z;
						else
							if (fabs(nBC.x) > EPSILON)
								O.z = nBC.z/nBC.x*(O.x - E.x) + E.z;
							else
								O.z = nBC.z/nBC.y*(O.y - E.y) + E.z;
					zDef = true;
				} else
					if (xDef && !yDef && zDef) // Не определена только O.y
					{
						if (fabs(nBA.x) > EPSILON)
							O.y = nBA.y/nBA.x*(O.x - D.x) + D.y;
						else
							if (fabs(nBA.z) > EPSILON)
								O.y = nBA.y/nBA.z*(O.z - D.z) + D.y;
							else
								if (fabs(nBC.x) > EPSILON)
									O.y = nBC.y/nBC.x*(O.x - E.x) + E.y;
								else
									O.y = nBC.y/nBC.z*(O.z - E.z) + E.y;
						yDef = true;
					} else
						if (!xDef && yDef && zDef) // не определена только O.x
						{
							if (fabs(nBA.y) > EPSILON)
								O.x = nBA.x/nBA.y*(O.y - D.y) + D.x;
							else
								if (fabs(nBA.z) > EPSILON)
									O.x = nBA.x/nBA.z*(O.z - D.z) + D.x;
								else
									if (fabs(nBC.y) > EPSILON)
										O.x = nBC.x/nBC.y*(O.y - E.y) + E.x;
									else
										O.x = nBC.x/nBC.z*(O.z - E.z) + E.x;
							xDef = true;
						} else // Варинат б)
							if (xDef) // Определена только O.x
							{
								kBA = nBA.z/nBA.y; kBC = nBC.z/nBC.y;
								if (fabs(kBA - kBC) > EPSILON)
								{
									O.y = (E.z - D.z + kBA*D.y - kBC*E.y)/(kBA-kBC);
									O.z = nBA.z/nBA.y*(O.y - D.y) + D.z;
								} 
								else
								{
									if (fabs(nBA.x) > EPSILON)
									{
										O.y = nBA.y/nBA.x*(O.x - D.x) + D.y;
										O.z = nBA.z/nBA.x*(O.x - D.x) + D.z;
									} else
										if (fabs(nBC.x) > EPSILON)
										{
											O.y = nBC.y/nBC.x*(O.x - E.x) + E.y;
											O.z = nBC.z/nBC.x*(O.x - E.x) + E.z;
										} 
								}
							} else
								if (yDef) // Определена только O.y
								{
									kBA = nBA.x/nBA.z, kBC = nBC.x/nBC.z;
									if (fabs(kBA - kBC) > EPSILON)
									{
										O.z = (E.x - D.x + kBA*D.z - kBC*E.z)/(kBA-kBC);
										O.x = kBA*(O.z - D.z) + D.x;
									}
									else
									{
										if (fabs(nBA.y) > EPSILON)
										{
											O.x = nBA.x/nBA.y*(O.y - D.y) + D.x;
											O.z = nBA.z/nBA.y*(O.y - D.y) + D.z;
										} else
											if (fabs(nBC.y) > EPSILON)
											{
												O.x = nBC.x/nBC.y*(O.y - E.y) + E.x;
												O.z = nBC.z/nBC.y*(O.y - E.y) + E.z;
											} 
									}

								} else
									if (zDef) // Определена только O.z
									{
										kBA = nBA.x/nBA.y, kBC = nBC.x/nBC.y;
										if (fabs(kBA - kBC) > EPSILON)
										{
											O.y = (E.x - D.x + kBA*D.y - kBC*E.y)/(kBA-kBC);
											O.x = kBA*(O.y - D.y) + D.x;
										} else
										{
											if (fabs(nBA.z) > EPSILON)
											{
												O.x = nBA.x/nBA.z*(O.z - D.z) + D.x;
												O.y = nBA.y/nBA.z*(O.z - D.z) + D.y;
											} else
												if (fabs(nBC.z) > EPSILON)
												{
													O.x = nBC.x/nBC.z*(O.z - E.z) + E.x;
													O.y = nBC.y/nBC.z*(O.z - E.z) + E.y;
												} 
										}

									} else // Собственно осталось 2 варианта: либо всё определено, либо не определено ничего
										if (!xDef && !yDef && !zDef) // Ничего не определено
										{
											kBA = nBA.x/nBA.y, kBC = nBC.x/nBC.y;
											if (fabs(kBA - kBC) > EPSILON)
											{
												O.y = (E.x - D.x + kBA*D.y - kBC*E.y)/(kBA-kBC);
												O.x = kBA*(O.y - D.y) + D.x;
												O.z = nBA.z/nBA.y*(O.y - D.y) + D.z;
											}
											else
											{
												kBA = nBA.z/nBA.x; kBC = nBC.z/nBC.x;
												O.x = (E.z - D.z + kBA*D.x - kBC*E.x)/(kBA - kBC);
												O.y = nBA.y/nBA.x*(O.x - D.x) + D.y;
												O.z = kBA*(O.x - D.x) + D.z;
											}
										}					
		}

		return false;

#pragma endregion
	}

	TVector curvatureVecNormalized(const TPoint& A, const TPoint& B,  const TPoint& C)
	{

		TPoint O;
		TVector Vec(0.0, 0.0, 0.0);
		if( !curvatureCentre(A, B, C, O))
		{
			Vec = O - B;
			if (fabs(Vec.x) > EPSILON || fabs(Vec.y) > EPSILON || fabs(Vec.z) > EPSILON)
				Vec.normalize();

		}

		return Vec;


	}


	TVector normal(const TPoint& cur, const TPoint& l,  const TPoint& r, const TPoint& b, const TPoint& t)
	{
		TVector hor = - curvatureVec(l, cur, r, t);
		TVector ver = - curvatureVec(b, cur, t, l);
		TVector n = hor + ver;
		n.normalize();
		if (n.len2() == 0.0)
		{
			n = (t - cur )^ (l - cur);
			n.normalize();
		}
		return n;
	}

	void Neighbours(const double z0, const double * z, int N_z, int & a , int & b)
	{
		/* z0 - одна из координат точки
		z - массив координат, N_z - количество его элементов
		a и b - границы отрезка, между которыми происходит поиск
		*/	
		// Определяем середину отрезка
		int d, z1, z2;
		double d1, d2;
		a = 0; 
		b = N_z - 1;
	
		if (z0 < z[a])
			throw std::exception("Neighbours : value less than minimal boundary");

		if (z0 > z[b])
			throw std::exception("Neighbours : value more than maximal boundary");


		do { 
			d = (a+b)/2; 
			z1 = d - 1; 
			z2 = d + 1;
			d1 = abs(z0 - z[z1]); 
			d2 = abs(z0 - z[z2]);
			if (d1 > d2) 
				a = d;
			else 
				b = d;
		} while ((b - a) > 1);
	}


	void getThreeNeighbours(const TPoint & curPoint, const double * x, const double * y, int N_x, int N_y, TPoint & A, TPoint & B, TPoint & C)
	{
		
		int x1 = 0, x2 = N_x - 1, y1 = 0, y2 = N_y - 1;
		TPoint D[4], E;
		Neighbours(curPoint.x, x, N_x, x1, x2);
		Neighbours(curPoint.y, y, N_y, y1, y2);
		
		// Имеем 4 точки, из которых надо выкинуть наиболее удалённую
		D[0].x = x[x1]; D[0].y = y[y1];
		D[1].x = x[x1]; D[1].y = y[y2];
		D[2].x = x[x2]; D[2].y = y[y1];
		D[3].x = x[x2]; D[3].y = y[y2];
		
		for (int i = 0; i < 3; i++)
			if ((D[i] - curPoint).len2() > (D[i+1] - curPoint).len2())
			{
				E = D[i];
				D[i] = D[i+1];
				D[i+1] = E;
			}

			A = D[0]; B = D[1]; C = D[2];

			

	}

	TPoint pointProjection(const TPoint & P, const TPoint & A, const TPoint & B, const TPoint & C)
	{
		TVector n = (B-A)^(C-A);
		n.normalize();
		double d = (P-A)*n;

		return P - d * n;
	}

	int transform( TransformDirection dir, TPoint & skirtPoint, TPoint & landscapePoint, const alglib::real_2d_array & M, const alglib::real_1d_array & s )
	{
		alglib::real_1d_array xS;
		alglib::real_1d_array xL;
		xS.setlength(3);
		xL.setlength(3);

		double  _xs[3];
		double  _xl[3];

		switch (dir)
		{
		case SKIRT_POINT_TO_LANDSCAPE_POINT:

			_xs[0] = skirtPoint.x;
			_xs[1] = skirtPoint.y;
			_xs[2] = skirtPoint.z;

			xS.setcontent(3, _xs);	

			alglib::rmatrixmv(3,3, M, 0 , 0 , 1 /*Транспонированная  матрица */, xS , 0, xL, 0);

			alglib::vadd(xL.getcontent(), s.getcontent(), 3);
			//xL = xL + s; // Получаем положение узла относительно ландшафта	

			landscapePoint.x = xL(0);
			landscapePoint.y = xL(1);
			landscapePoint.z = xL(2);

			return 0;

		case LANDSCAPE_POINT_TO_SKIRT_POINT:

			_xl[0] = landscapePoint.x;
			_xl[1] = landscapePoint.y;
			_xl[2] = landscapePoint.z;

			xL.setcontent(3, _xl);

			alglib::vsub(xL.getcontent(), s.getcontent(), 3);
			alglib::rmatrixmv(3,3, M, 0 , 0 , 0 /*Прямая  матрица */, xL , 0, xS, 0);

			skirtPoint.x = xS(0);
			skirtPoint.y = xS(1);
			skirtPoint.z = xS(2);

			return 0;

		case SKIRT_VECTOR_TO_LANDSCAPE_VECTOR:

			_xs[0] = skirtPoint.x;
			_xs[1] = skirtPoint.y;
			_xs[2] = skirtPoint.z;

			xS.setcontent(3, _xs);	

			alglib::rmatrixmv(3,3, M, 0 , 0 , 1 /*Транспонированная  матрица */, xS , 0, xL, 0);

			landscapePoint.x = xL(0);
			landscapePoint.y = xL(1);
			landscapePoint.z = xL(2);

			return 0;

		case LANDSCAPE_VECTOR_TO_SKIRT_VECTOR:

			_xl[0] = landscapePoint.x;
			_xl[1] = landscapePoint.y;
			_xl[2] = landscapePoint.z;

			xL.setcontent(3, _xl);

			alglib::rmatrixmv(3,3, M, 0 , 0 , 0 /*Прямая  матрица */, xL , 0, xS, 0);

			skirtPoint.x = xS(0);
			skirtPoint.y = xS(1);
			skirtPoint.z = xS(2);

			return 0;
		}

		throw std::exception("Unknown TransformDirection");	
	}


}