#pragma once

#include "Envelope.Math.Consts.h"

#include "TPoint.h"
#include "TVector.h"

#include "quasiCurvature.h"
#include "quasiNormal.h"

using namespace alglib;

namespace EnvelopeMath {

	/**
	* @fn	double area(const TPoint& A, const TPoint& B, const TPoint& C);
	*
	* @brief	������� ������������ ABC.
	*
	* @author	Vasiliy
	* @date	23.11.2012
	*
	* @param	A	The const TPoint&amp; to process.
	* @param	B	The const TPoint&amp; to process.
	* @param	C	The const TPoint&amp; to process.
	*
	* @return	.
	*/

	DllExport double area(const TPoint& A, const TPoint& B,  const TPoint& C); 

	/**
	* @fn	DllExport double curvature(const TPoint& A, const TPoint& B, const TPoint& C,
	* 		const TPoint& D);
	*
	* @brief	�������� (���������������) - ��������, �������� ������� ��������.
	*
	* @author	Vasiliy
	* @date	23.11.2012
	*
	* @param	A	�����.
	* @param	B	�����, ������������ ������� ���������� ��������.
	* @param	C	�����.
	* @param	D	�����, ������� ���������� ��� ����������� ����� ��������. �������� ��������� �������������,
	* 				���� ������� BA, BD � BO (O - ����� ��������) �������� ������ ������ ��������.
	*
	* @return	.
	*/

	DllExport double curvature(const TPoint& A, const TPoint& B,  const TPoint& C, const TPoint& D); 

	/**
	* @fn	DllExport TVector curvatureVec(const TPoint& A, const TPoint& B, const TPoint& C,
	* 		const TPoint& D);
	*
	* @brief	������ ��������.
	*
	* @author	Vasiliy
	* @date	23.11.2012
	*
	* @param	A	�����.
	* @param	B	�����, ������������ ������� ���������� ��������.
	* @param	C	�����.
	* @param	D	�����, ������� ���������� ��� ����������� ����� ��������. �������� ��������� �������������,
	* 				���� ������� BA, BD � BO (O - ����� ��������) �������� ������ ������ ��������.
	*
	* @return	������, ������������ �� �. B � ������ ��������, ���� �������� �������������, � � ��������������� �����������,
	* 			���� �������� �������������. �� ������ ����� ��������.
	*/

	DllExport TVector curvatureVec(const TPoint& A, const TPoint& B,  const TPoint& C, const TPoint& D);

	/**
	* @fn	bool curvatureCentre(const TPoint& A, const TPoint& B, const TPoint& C, TPoint& O );
	*
	* @brief	������� ����� �������� ����������, ��������� ����� ������������ ABC.
	*
	* @author	Vs
	* @date	17.02.2013
	*
	* @param	A		 	The const TPoint&amp; to process.
	* @param	B		 	The const TPoint&amp; to process.
	* @param	C		 	The const TPoint&amp; to process.
	* @param [in,out]	O	����� ��������.
	*
	* @return	�������� �� ����� �����������.
	*/

	DllExport bool curvatureCentre(const TPoint& A, const TPoint& B,  const TPoint& C, TPoint& O );

	/**
	* @fn	TVector curvatureVecNormalized(const TPoint& A, const TPoint& B, const TPoint& C);
	*
	* @brief	������������� ������ ��������. ���� �������� �������, �� ������ �������
	*
	* @author	Vs
	* @date	07.02.2013
	*
	* @param	A	�����.
	* @param	B	�����, ������������ ������� ���������� ��������.
	* @param	C	�����.
	*
	* @return	������, ������������ �� �. B � ������ �������� � ������ �� ������ 1 ��� 0.
	*/

	DllExport TVector curvatureVecNormalized(const TPoint& A, const TPoint& B,  const TPoint& C);

	/**
	* @fn	DllExport TVector quasiCurvatureVecNormalized(const TPoint& A, const TPoint& B,
	* 		const TPoint& C);
	*
	* @brief	������������� ��������������� ������  ��������. ��������������, ��� ����� �������� ���������� �����.
	* 			���� �������� �������, �� ������ �������
	*
	* @author	Vs
	* @date	13.07.2013
	*
	* @param	A	The const TPoint&amp; to process.
	* @param	B	The const TPoint&amp; to process.
	* @param	C	The const TPoint&amp; to process.
	*
	* @return	.
	*/

	DllExport TVector quasiCurvatureVecNormalized(const TPoint& A, const TPoint& B,  const TPoint& C);

	/**
	* @fn	TVector normal (const TPoint& A, const TPoint& B, const TPoint& C, const TPoint& D,
	* 		const TPoint& E);
	*
	* @brief	������� � �����������, ���������� ����� ��� 5 �����, � ����� A
	*
	* @author	Vasiliy
	* @date	23.11.2012
	*
	* @param	A	The const TPoint&amp; to process.
	* @param	B	The const TPoint&amp; to process.
	* @param	C	The const TPoint&amp; to process.
	* @param	D	The const TPoint&amp; to process.
	* @param	E	The const TPoint&amp; to process.
	*
	* @return	.
	*/

	DllExport TVector normal (const TPoint& A, const TPoint& B,  const TPoint& C, const TPoint& D, const TPoint& E);
}