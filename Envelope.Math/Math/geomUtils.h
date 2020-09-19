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
	* @brief	Площадь треугольника ABC.
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
	* @brief	кривизна (ориентированная) - величина, обратная радиусу кривизны.
	*
	* @author	Vasiliy
	* @date	23.11.2012
	*
	* @param	A	Точка.
	* @param	B	Точка, относительно которой измеряется кривизна.
	* @param	C	Точка.
	* @param	D	Точка, которая необходима для определения знака кривизны. Кривизна считается положительной,
	* 				если векторы BA, BD и BO (O - центр кривизны) образуют правую тройку векторов.
	*
	* @return	.
	*/

	DllExport double curvature(const TPoint& A, const TPoint& B,  const TPoint& C, const TPoint& D); 

	/**
	* @fn	DllExport TVector curvatureVec(const TPoint& A, const TPoint& B, const TPoint& C,
	* 		const TPoint& D);
	*
	* @brief	Вектор кривизны.
	*
	* @author	Vasiliy
	* @date	23.11.2012
	*
	* @param	A	Точка.
	* @param	B	Точка, относительно которой измеряется кривизна.
	* @param	C	Точка.
	* @param	D	Точка, которая необходима для определения знака кривизны. Кривизна считается положительной,
	* 				если векторы BA, BD и BO (O - центр кривизны) образуют правую тройку векторов.
	*
	* @return	Вектор, направленный из т. B к центру кривизны, если кривизна положительная, и в противоположном направлении,
	* 			если кривизна отрицательная. По модулю равен кривизне.
	*/

	DllExport TVector curvatureVec(const TPoint& A, const TPoint& B,  const TPoint& C, const TPoint& D);

	/**
	* @fn	bool curvatureCentre(const TPoint& A, const TPoint& B, const TPoint& C, TPoint& O );
	*
	* @brief	Находит центр кривизны окружности, описанной около треугольника ABC.
	*
	* @author	Vs
	* @date	17.02.2013
	*
	* @param	A		 	The const TPoint&amp; to process.
	* @param	B		 	The const TPoint&amp; to process.
	* @param	C		 	The const TPoint&amp; to process.
	* @param [in,out]	O	Центр кривизны.
	*
	* @return	Является ли центр бесконечным.
	*/

	DllExport bool curvatureCentre(const TPoint& A, const TPoint& B,  const TPoint& C, TPoint& O );

	/**
	* @fn	TVector curvatureVecNormalized(const TPoint& A, const TPoint& B, const TPoint& C);
	*
	* @brief	Нормированный вектор кривизны. Если кривизна нулевая, то вектор нулевой
	*
	* @author	Vs
	* @date	07.02.2013
	*
	* @param	A	Точка.
	* @param	B	Точка, относительно которой измеряется кривизна.
	* @param	C	Точка.
	*
	* @return	Вектор, направленный из т. B к центру кривизны и равный по модулю 1 или 0.
	*/

	DllExport TVector curvatureVecNormalized(const TPoint& A, const TPoint& B,  const TPoint& C);

	/**
	* @fn	DllExport TVector quasiCurvatureVecNormalized(const TPoint& A, const TPoint& B,
	* 		const TPoint& C);
	*
	* @brief	Нормированный линеаризованный вектор  кривизны. Предполагается, что ребра примерно одинаковой длины.
	* 			Если кривизна нулевая, то вектор нулевой
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
	* @brief	Нормаль к поверхности, проходящей через все 5 точек, в точке A
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