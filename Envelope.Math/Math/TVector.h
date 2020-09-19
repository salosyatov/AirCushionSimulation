#pragma once
#ifndef SS_TVector_H
#define SS_TVector_H

#include "common.h"

namespace EnvelopeMath {
	//==================================================================
	//  TVector Class Definition
	//==================================================================

	class DllExport TVector : public TPoint {
	public:
		// Constructors same as TPoint class
		TVector();
		TVector( double a, double b, double c) ;
		~TVector() ;

		//----------------------------------------------------------
		// IO streams and Comparisons: inherit from TPoint class

		//----------------------------------------------------------
		// TVector Unary Operations
		TVector operator-();                // unary minus
		TVector operator~();                // unary 2D perp operator

		//----------------------------------------------------------
		// Scalar Multiplication
		friend DllExport TVector operator*( int, TVector);
		friend DllExport TVector operator*( double, TVector);
		friend DllExport TVector operator*( TVector, int);
		friend DllExport TVector operator*( TVector, double);
		// Scalar Division
		friend DllExport TVector operator/( TVector, int);
		friend DllExport TVector operator/( TVector, double);

		//----------------------------------------------------------
		// TVector Arithmetic Operations
		TVector operator+( TVector);        // TVector add
		TVector operator-( TVector);        // TVector subtract
		double operator*( TVector);        // inner dot product
		double operator|( TVector);        // 2D exterior perp product
		TVector operator^( TVector) const;        // 3D exterior cross product

		TVector& operator*=( double);      // TVector scalar mult
		TVector& operator/=( double);      // TVector scalar div
		TVector& operator+=( TVector);      // TVector increment
		TVector& operator-=( TVector);      // TVector decrement
		TVector& operator^=(const TVector &);      // 3D exterior cross product

		//----------------------------------------------------------
		// TVector Properties
		double len() const {                    // TVector length
			return sqrt(x*x + y*y + z*z);
		}
		double len2() const {                   // TVector length squared (faster)
			return (x*x + y*y + z*z);
		}

		//----------------------------------------------------------
		// Special Operations
		void normalize();                 // convert TVector to unit length
		TVector normalized() const;                 // ¬озвращает нормализованный вектор
		friend DllExport TVector sum( int, int[], TVector[]);     // TVector sum
		friend DllExport TVector sum( int, double[], TVector[]);  // TVector sum
		friend DllExport TVector sum( int, TVector[]);     // TVector sum

		friend DllExport double dot(TVector v1, TVector v2); // скал€рное произведение
		friend DllExport double dot3(TVector v1, TVector v2, TVector v3); //—мешанное произведение
	};
}
#endif SS_TVector_H

