#include "stdafx.h"


#include "TPoint.h"
#include "TVector.h"
namespace EnvelopeMath {
	//==================================================================
	// TPoint Class Methods
	//==================================================================

	//------------------------------------------------------------------
	// Constructors (add more as needed)
	//------------------------------------------------------------------

	TPoint :: TPoint() 
	{ 
		dimn = 3;
		x = y = z = 0.0;
		err=Enot; 
	}


	TPoint :: TPoint( double a, double b, double c) {
		dimn=3; x=a; y=b; z=c; err=Enot; }



	//------------------------------------------------------------------
	// IO streams
	//------------------------------------------------------------------

	// Read input TPoint format: "(%f)", "(%f, %f)", or "(%f, %f, %f)"
	std::istream& operator>>( std::istream& input, TPoint& P) {
		char c;
		input >> c;                // skip '('
		input >> P.x;
		input >> c;                
		if (c == ')') {
			P.setdim(1);       // 1D coord
			return input;
		}
		// else                    // skip ','
		input >> P.y;
		input >> c;
		if (c == ')') {
			P.setdim(2);       // 2D coord
			return input;
		}
		// else                    // skip ','
		input >> P.z;
		P.setdim(3);               // 3D coord
		input >> c;                // skip ')'
		return input;
	}

	// Write output TPoint in format: "(%f)", "(%f, %f)", or "(%f, %f, %f)"
	std::ostream& operator<<( std::ostream& output, TPoint P) {
		switch (P.dim()) {
		case 1:
			output << "(" << P.x << ")";
			break;
		case 2:
			output << "(" << P.x << ", " << P.y << ")";
			break;
		case 3:
			output << "(" << P.x << ", " << P.y << ", " << P.z << ")";
			break;
		default:
			output << "Error: P.dim = " << P.dim();
		}
		return output;
	}

	//------------------------------------------------------------------
	// Assign (set) dimension
	//------------------------------------------------------------------

	int TPoint::setdim( int n) {
		switch (n) {
		case 1: y = 0;
		case 2: z = 0;
		case 3:
			return dimn = n;
		default:                      // out of range value
			err = Edim;           // just flag the error
			return SS_ERROR;
		}
	}

	//------------------------------------------------------------------
	// Comparison (note: dimension must compare)
	//------------------------------------------------------------------

	int TPoint::operator==( TPoint Q) const
	{
		if (dimn != Q.dim()) return SS_FALSE;
		switch (dimn) {
		case 1:
			return (x == Q.x);
		case 2:
			return (x==Q.x && y==Q.y);
		case 3:
		default:
			return (x == Q.x && y == Q.y && z == Q.z );
		}
	}

	int TPoint::operator!=( TPoint Q) const
	{
		if (dimn != Q.dim()) return SS_TRUE;
		switch (dimn) {
		case 1:
			return (x!=Q.x);
		case 2:
			return (x!=Q.x || y!=Q.y);
		case 3:
		default:
			return (x!=Q.x || y!=Q.y || z!=Q.z);
		}
	}

	//------------------------------------------------------------------
	// TPoint TVector Operations
	//------------------------------------------------------------------

	TVector TPoint::operator-( TPoint Q) const        // TVector diff of TPoints
	{
		TVector v;
		v.x = x - Q.x;
		v.y = y - Q.y;
		v.z = z - Q.z;
		v.dimn = max( dimn, Q.dim());
		return v;
	}

	TPoint TPoint::operator+( TVector v)        // +ve translation
	{
		TPoint P;
		P.x = x + v.x;
		P.y = y + v.y;
		P.z = z + v.z;
		P.dimn = max( dimn, v.dim());
		return P;
	}

	TPoint TPoint::operator-( TVector v)        // -ve translation
	{
		TPoint P;
		P.x = x - v.x;
		P.y = y - v.y;
		P.z = z - v.z;
		P.dimn = max( dimn, v.dim());
		return P;
	}

	TPoint& TPoint::operator+=( TVector v)        // +ve translation
	{
		x += v.x;
		y += v.y;
		z += v.z;
		dimn = max( dimn, v.dim());
		return *this;
	}

	TPoint& TPoint::operator-=( TVector v)        // -ve translation
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
		dimn = max( dimn, v.dim());
		return *this;
	}

	//------------------------------------------------------------------
	// TPoint Scalar Operations (convenient but often illegal)
	//        are not valid for TPoints in general,
	//        unless they are 'affine' as coeffs of 
	//        a sum in which all the coeffs add to 1,
	//        such as: the sum (a*P + b*Q) with (a+b == 1).
	//        The programmer must enforce this (if they want to).
	//------------------------------------------------------------------

	TPoint operator*( int c, TPoint Q) {
		TPoint P;
		P.x = c * Q.x;
		P.y = c * Q.y;
		P.z = c * Q.z;
		P.dimn = Q.dim();
		return P;
	}

	TPoint operator*( double c, TPoint Q) {
		TPoint P;
		P.x = c * Q.x;
		P.y = c * Q.y;
		P.z = c * Q.z;
		P.dimn = Q.dim();
		return P;
	}

	TPoint operator*( TPoint Q, int c) {
		TPoint P;
		P.x = c * Q.x;
		P.y = c * Q.y;
		P.z = c * Q.z;
		P.dimn = Q.dim();
		return P;
	}

	TPoint operator*( TPoint Q, double c) {
		TPoint P;
		P.x = c * Q.x;
		P.y = c * Q.y;
		P.z = c * Q.z;
		P.dimn = Q.dim();
		return P;
	}

	TPoint operator/( TPoint Q, int c) {
		TPoint P;
		P.x = Q.x / c;
		P.y = Q.y / c;
		P.z = Q.z / c;
		P.dimn = Q.dim();
		return P;
	}

	TPoint operator/( TPoint Q, double c) {
		TPoint P;
		P.x = Q.x / c;
		P.y = Q.y / c;
		P.z = Q.z / c;
		P.dimn = Q.dim();
		return P;
	}

	//------------------------------------------------------------------
	// TPoint Addition (also convenient but often illegal)
	//    is not valid unless part of an affine sum.
	//    The programmer must enforce this (if they want to).
	//------------------------------------------------------------------

	TPoint operator+( TPoint Q, TPoint R)
	{
		TPoint P;
		P.x = Q.x + R.x;
		P.y = Q.y + R.y;
		P.z = Q.z + R.z;
		P.dimn = max( Q.dim(), R.dim());
		return P;
	}

	//------------------------------------------------------------------
	// Affine Sums
	// Returns weighted sum, even when not affine, but...
	// Tests if coeffs add to 1.  If not, sets: err = Esum.
	//------------------------------------------------------------------

	TPoint asum( int n, int c[], TPoint Q[])
	{
		int        maxd = 0;
		int        cs = 0;
		TPoint      P;

		for (int i=0; i<n; i++) {
			cs += c[i];
			if (Q[i].dim() > maxd)
				maxd = Q[i].dim();
		}
		if (cs != 1)                 // not an affine sum
			P.err = Esum;        // flag error, but compute sum anyway

		for (int i=0; i<n; i++) {
			P.x += c[i] * Q[i].x;
			P.y += c[i] * Q[i].y;
			P.z += c[i] * Q[i].z;
		}
		P.dimn = maxd;
		return P;
	}

	TPoint asum( int n, double c[], TPoint Q[])
	{
		int        maxd = 0;
		double     cs = 0.0;
		TPoint      P;

		for (int i=0; i<n; i++) {
			cs += c[i];
			if (Q[i].dim() > maxd)
				maxd = Q[i].dim();
		}
		if (cs != 1)                 // not an affine sum
			P.err = Esum;        // flag error, but compute sum anyway

		for (int i=0; i<n; i++) {
			P.x += c[i] * Q[i].x;
			P.y += c[i] * Q[i].y;
			P.z += c[i] * Q[i].z;
		}
		P.dimn = maxd;
		return P;
	}

	//------------------------------------------------------------------
	// Distance between TPoints
	//------------------------------------------------------------------

	double d( TPoint P, TPoint Q) {      // Euclidean distance
		double dx = P.x - Q.x;
		double dy = P.y - Q.y;
		double dz = P.z - Q.z;
		return sqrt(dx*dx + dy*dy + dz*dz);
	}

	double d2( TPoint P, TPoint Q) {     // squared distance (more efficient)
		double dx = P.x - Q.x;
		double dy = P.y - Q.y;
		double dz = P.z - Q.z;
		return (dx*dx + dy*dy + dz*dz);
	}


	//------------------------------------------------------------------
	// Sidedness of a TPoint wrt a directed line P1->P2
	//        - makes sense in 2D only
	//------------------------------------------------------------------

	double TPoint::isLeft( TPoint P1, TPoint P2) {
		if (dimn != 2 || P1.dim() != 2 || P2.dim() != 2) {
			err = Edim;        // flag error, but compute anyway
		}
		return ((P1.x - x) * (P2.y - y) - (P2.x - x) * (P1.y - y));
	}

	//------------------------------------------------------------------
	// Error Routines
	//------------------------------------------------------------------

	char* TPoint::errstr() {            // return error string
		switch (err) {
		case Enot:
			return "no error";
		case Edim:
			return "error: invalid dimension for operation";
		case Esum:
			return "error: TPoint sum is not affine";
		default:
			return "error: unknown err value";
		}
	}

}