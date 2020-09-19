#include "stdafx.h"
#include "geomUtils.h"
#include <cmath>

#define  EPSILON DBL_EPSILON

namespace EnvelopeMath {
	double area(const TPoint& A, const TPoint&  B,  const TPoint& C)  // area
	{

		return 0.5 * ((B-A)^(C-A)).len();
		//	double c = d(A, B);
		//	double a = d(B, C);
		//	double b = d(A, C);
		//	double p = 0.5 * (a+b+c);
		//	return sqrt(p*(p-a)*(p-b)*(p-c));


	}

	double curvature(const TPoint& A, const TPoint& B,  const TPoint& C, const TPoint& D)
	{
//		throw std::exception("double curvature(const TPoint& A, const TPoint& B,  const TPoint& C, const TPoint& D)");
//				return quasiCurvature(A, B, C, D);

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

		return  fabs(curv) * n; //TODO: ������������, ����� �� ��������� ����

	}

	bool curvatureCentre(const TPoint& A, const TPoint& B,  const TPoint& C, TPoint& O )
	{

//		throw std::exception("bool curvatureCentre(const TPoint& A, const TPoint& B,  const TPoint& C, TPoint& O )");

#pragma region 
		bool xDef = false, yDef = false, zDef = false; // �������� ����������� ��������� ����� O (������ ��������� ����������)
		double kBA = 0, kBC = 0;
		// ���������� ������� � ������� � ��������
		TVector BA = A - B, BC = C - B, n = BA^BC, nBA = n^BA, nBC = n^BC;
		// �������� �� �������������� ����� ������ (������� ������� ���������������, ������������ �� ��������).                                // ���������� �������� ������
		TPoint D = (A + B)*0.5, E = (B + C)*0.5;  		

		if (n.len() <= EPSILON)
		{
			// ������� ������ �����������, ������ ����� ����� �� ����� ������
			O = B;
			return true;
		} 
		else
		{
			// ������� ������
			// �������� ������� nBA �� ������������������ OX
			if (fabs(nBA.x) <= EPSILON)
			{
				O.x = D.x;
				xDef = true;
			}
			// �������� ������� nBA �� ������������������ OY
			if (fabs(nBA.y) <= EPSILON)
			{
				O.y = D.y;
				yDef = true;
			}
			// �������� ������� nBA �� ������������������ OZ
			if (fabs(nBA.z) <= EPSILON)
			{
				O.z = D.z;
				zDef = true;
			}

			// �������� ������� nBC �� ������������������ OX
			if (fabs(nBC.x) <= EPSILON && !xDef)
			{
				O.x = E.x;
				xDef = true;
			}
			// �������� ������� nBC �� ������������������ OY
			if (fabs(nBC.y) <= EPSILON && !yDef)
			{
				O.y = E.y;
				yDef = true;
			}
			// �������� ������� nBC �� ������������������ OZ
			if (fabs(nBC.z) <= EPSILON && !zDef)
			{
				O.z = E.z;
				zDef = true;
			}
			/* ��� ����� ����������. ������ ���������� ���������. ���������� ��������: 
			�) �� ���������� �����-������ ���� �� ��������� - ���������� 4 ������� � �������� ����� ��������� (���� � ����� ����� �� ������� ������������)
			�) ���������� �����-������ ���� �� ��������� - ������ ������� �������� ����������, ��������� �� ���������� ���������
			�) �� ���������� ������ - ����� �� ������� ������� ���������
			�) ��������� ���������� �� 
			*/
			// ��������� ����� �)
			if (!(xDef && yDef && zDef))
				if (xDef && yDef && !zDef) // �� ���������� ������ O.z
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
					if (xDef && !yDef && zDef) // �� ���������� ������ O.y
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
						if (!xDef && yDef && zDef) // �� ���������� ������ O.x
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
						} else // ������� �)
							if (xDef) // ���������� ������ O.x
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
								if (yDef) // ���������� ������ O.y
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
									if (zDef) // ���������� ������ O.z
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
												} else 
												{
													//std::cout << "�����. " << A << B << C << std::endl; //TODO: ������
													//throw std::exception("curvatureCentre");
													//char x;
													//std::cin >> x;
												}

										}

									} else // ���������� �������� 2 ��������: ���� �� ����������, ���� �� ���������� ������
										if (!xDef && !yDef && !zDef) // ������ �� ����������
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
//		return quasiCurvatureVecNormalized(A, B, C);


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

	TVector quasiCurvatureVecNormalized(const TPoint& A, const TPoint& B,  const TPoint& C)
	{
		TVector vec;
		vec = (A - B) + (C - B);
		vec.normalize();
		return vec;
		
	}


	TVector normal(const TPoint& cur, const TPoint& l,  const TPoint& r, const TPoint& b, const TPoint& t)
	{
		return quasiNormal(cur, l, r, b, t);

		//		TVector n = ((l-cur)^(r-cur))^((b-cur)^(t-cur));
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
}