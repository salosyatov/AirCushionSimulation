#pragma once

#include "Envelope.Math.Consts.h"

#include "TPoint.h"
#include "TVector.h"

#include "ap.h"
#include "linalg.h"

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

	/**
	* @fn void getThreeNeighbours(const TPoint & curPoint, const double * x, const double * y,
	* int N_x, int N_y, TPoint & A, TPoint & B, TPoint & C);
	*
	* @brief Находит трех ближайших точек-соседей. 
	* 		  Поиск происходит среди точек, которые задаются массивами абсцисс и ординат, то есть 
	* 		  всего N_x * N_y точек. При этом, используется метод дихотомии. 
	*
	* @author Vasily Salosyatov
	* @date 07.12.2012
	*
	* @param P
	* Текущая точка, относительно которой ищутся соседи.
	* @param x
	* Массив значений абсцисс.
	* @param y
	* Массив значений ординат.
	* @param N_x
	* Размер массива значений абсцисс.
	* @param N_y
	* Размер массива значений ординат.
	* @param [in,out] A
	* Соседняя точка.
	* @param [in,out] B
	* Соседняя точка.
	* @param [in,out] C
	* Соседняя точка.
	*/

	DllExport void getThreeNeighbours(const TPoint & P, const double * x, const double * y, int N_x, int N_y, TPoint & A, TPoint & B, TPoint & C);

	/**
	* @fn TPoint pointProjection(const TPoint & P, const TPoint & A, const TPoint & B,
	* const TPoint & C);
	*
	* @brief Получает проекцию точки P на плоскость, заданную точками A, B, C.
	*
	* @author Vasily Salosyatov
	* @date 07.12.2012
	*
	* @param P
	* Текущая точка.
	* @param A
	* Точка задающая плоскость.
	* @param B
	* Точка задающая плоскость.
	* @param C
	* Точка задающая плоскость.
	*
	* @return .
	*/

	DllExport TPoint pointProjection(const TPoint & P, const TPoint & A, const TPoint & B, const TPoint & C);



	DllExport int transform( TransformDirection dir, TPoint & skirtPoint, TPoint & landscapePoint, const alglib::real_2d_array & M, const alglib::real_1d_array & s );
}



