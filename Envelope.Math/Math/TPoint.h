#pragma once

#ifndef SS_TPoint_H
#define SS_TPoint_H

#include "common.h"

namespace EnvelopeMath {
	//==================================================================
	//  TPoint Class Definition
	//==================================================================

	class DllExport TPoint {
		friend class TVector;
	protected:
		int dimn;            // # coords (1, 2, or 3 max here)
		Error err;           // error indicator
	public:
		double x, y, z;      // z=0 for 2D, y=z=0 for 1D

		//----------------------------------------------------------
		// Lots of Constructors (add more as needed)
		TPoint();

		TPoint( double a, double b, double c) ;

		// Destructor
		~TPoint() {};

		//----------------------------------------------------------
		// Input/Output streams
		friend DllExport std::istream& operator>>( std::istream&, TPoint&);
		friend DllExport std::ostream& operator<<( std::ostream&, TPoint);

		//----------------------------------------------------------
		// Assignment "=": use the default to copy all members
		int dim() { return dimn; }      // get dimension
		int setdim( int);               // set new dimension

		//----------------------------------------------------------
		// Comparison (dimension must match, or not)
		int operator==( TPoint) const;
		int operator!=( TPoint) const;

		//----------------------------------------------------------
		// TPoint and TVector Operations (always valid) 
		TVector operator-( TPoint) const;       // TVector difference //!vs
		TPoint  operator+( TVector);      // +translate
		TPoint  operator-( TVector);      // -translate
		TPoint& operator+=( TVector);     // inc translate
		TPoint& operator-=( TVector);     // dec translate

		//----------------------------------------------------------
		// TPoint Scalar Operations (convenient but often illegal)
		// using any type of scalar (int, float, or double)
		//    are not valid for TPoints in general,
		//    unless they are 'affine' as coeffs of 
		//    a sum in which all the coeffs add to 1,
		//    such as: the sum (a*P + b*Q) with (a+b == 1).
		//    The programmer must enforce this (if they want to).

		// Scalar Multiplication
		friend DllExport TPoint operator*( int, TPoint);
		friend DllExport TPoint operator*( double, TPoint);
		friend DllExport TPoint operator*( TPoint, int);
		friend DllExport TPoint operator*( TPoint, double);
		// Scalar Division
		friend DllExport TPoint operator/( TPoint, int);
		friend DllExport TPoint operator/( TPoint, double);

		//----------------------------------------------------------
		// TPoint Addition (also convenient but often illegal)
		//    is not valid unless part of an affine sum.
		//    The programmer must enforce this (if they want to).
		friend DllExport TPoint operator+( TPoint, TPoint);     // add TPoints

		// Affine Sum
		// Returns weighted sum, even when not affine, but...
		// Tests if coeffs add to 1.  If not, sets: err = Esum.
		friend DllExport TPoint asum( int, int[], TPoint[]);
		friend DllExport TPoint asum( int, double[], TPoint[]);

		//----------------------------------------------------------
		// TPoint Relations
		friend DllExport double d( TPoint, TPoint);         // Distance
		friend DllExport double d2( TPoint, TPoint);        // Distance^2


		double isLeft( TPoint, TPoint);           // 2D only
		double Area( TPoint, TPoint); 		// any dim for triangle PPP

		// Collinearity Conditions (any dim n)
		SS_boolean isOnLine( TPoint, TPoint, char);  // is On line (char= flag)
		SS_boolean isOnLine( TPoint, TPoint);        // is On line (flag= all)
		SS_boolean isBefore( TPoint, TPoint);        // is On line (flag= before)
		SS_boolean isBetween( TPoint, TPoint);       // is On line (flag= between)
		SS_boolean isAfter( TPoint, TPoint);         // is On line (flag= after)
		SS_boolean isOnRay( TPoint, TPoint);         // is On line (flag= between|after)

		//----------------------------------------------------------
		// Error Handling
		void  clerr() { err = Enot;}            // clear error
		int   geterr() { return err;}           // get error
		char* errstr();                         // return error string
	};
}
#endif SS_TPoint_H


