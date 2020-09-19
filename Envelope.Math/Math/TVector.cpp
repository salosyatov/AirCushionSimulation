#include "stdafx.h"


#include "TPoint.h"
#include "TVector.h"
namespace EnvelopeMath {


	TVector :: TVector() : TPoint() {};

	TVector :: TVector( double a, double b, double c) : TPoint(a,b,c) {};

	TVector :: ~TVector() {};

	//------------------------------------------------------------------
	//  Unary Ops
	//------------------------------------------------------------------

	// Unary minus
	TVector TVector::operator-() {
		TVector v;
		v.x = -x; v.y = -y; v.z = -z;
		v.dimn = dimn;
		return v;
	}

	// Unary 2D perp operator
	TVector TVector::operator~() {
		if (dimn != 2) err = Edim;   // and continue anyway
		TVector v;
		v.x = -y; v.y = x; v.z = z;
		v.dimn = dimn;
		return v;
	}

	//------------------------------------------------------------------
	//  Scalar Ops
	//------------------------------------------------------------------

	// Scalar multiplication
	TVector operator*( int c, TVector w )  {
		TVector v;
		v.x = c * w.x;
		v.y = c * w.y;
		v.z = c * w.z;
		v.dimn = w.dim();
		return v;
	}

	TVector operator*( double c, TVector w )  {
		TVector v;
		v.x = c * w.x;
		v.y = c * w.y;
		v.z = c * w.z;
		v.dimn = w.dim();
		return v;
	}

	TVector operator*( TVector w, int c ) {
		TVector v;
		v.x = c * w.x;
		v.y = c * w.y;
		v.z = c * w.z;
		v.dimn = w.dim();
		return v;
	}

	TVector operator*( TVector w, double c ) {
		TVector v;
		v.x = c * w.x;
		v.y = c * w.y;
		v.z = c * w.z;
		v.dimn = w.dim();
		return v;
	}

	// Scalar division
	TVector operator/( TVector w, int c ) {
		TVector v;
		v.x = w.x / c;
		v.y = w.y / c;
		v.z = w.z / c;
		v.dimn = w.dim();
		return v;
	}

	TVector operator/( TVector w, double c ) {
		TVector v;
		v.x = w.x / c;
		v.y = w.y / c;
		v.z = w.z / c;
		v.dimn = w.dim();
		return v;
	}

	//------------------------------------------------------------------
	//  Arithmetic Ops
	//------------------------------------------------------------------

	TVector TVector::operator+( TVector w ) {
		TVector v;
		v.x = x + w.x;
		v.y = y + w.y;
		v.z = z + w.z;
		v.dimn = max( dimn, w.dim());
		return v;
	}

	TVector TVector::operator-( TVector w ) {
		TVector v;
		v.x = x - w.x;
		v.y = y - w.y;
		v.z = z - w.z;
		v.dimn = max( dimn, w.dim());
		return v;
	}

	//------------------------------------------------------------------
	//  Products
	//------------------------------------------------------------------

	// Inner Dot Product
	double TVector::operator*( TVector w ) {
		return (x * w.x + y * w.y + z * w.z);
	}

	// 2D Exterior Perp Product
	double TVector::operator|( TVector w ) {
		if (dimn != 2) err = Edim;    // and continue anyway
		return (x * w.y - y * w.x);
	}

	// 3D Exterior Cross Product
	TVector TVector::operator^( TVector w ) const {
		TVector v;
		v.x = y * w.z - z * w.y;
		v.y = z * w.x - x * w.z;
		v.z = x * w.y - y * w.x;
		v.dimn = 3;
		return v;
	}

	//------------------------------------------------------------------
	//  Shorthand Ops
	//------------------------------------------------------------------

	TVector& TVector::operator*=( double c ) {        // TVector scalar mult
		x *= c;
		y *= c;
		z *= c;
		return *this;
	}

	TVector& TVector::operator/=( double c ) {        // TVector scalar div
		x /= c;
		y /= c;
		z /= c;
		return *this;
	}

	TVector& TVector::operator+=( TVector w ) {        // TVector increment
		x += w.x;
		y += w.y;
		z += w.z;
		dimn = max(dimn, w.dim());
		return *this;
	}

	TVector& TVector::operator-=( TVector w ) {        // TVector decrement
		x -= w.x;
		y -= w.y;
		z -= w.z;
		dimn = max(dimn, w.dim());
		return *this;
	}

	TVector& TVector::operator^=(const TVector & w ) {        // 3D exterior cross product
		double ox=x, oy=y, oz=z;
		x = oy * w.z - oz * w.y;
		y = oz * w.x - ox * w.z;
		z = ox * w.y - oy * w.x;
		dimn = 3;
		return *this;
	}

	//------------------------------------------------------------------
	//  Special Operations
	//------------------------------------------------------------------

	void TVector::normalize() {                      // convert to unit length
		double ln = sqrt( x*x + y*y + z*z );
		if (ln == 0) return;                    // do nothing for nothing
		x /= ln;
		y /= ln;
		z /= ln;
	}

	TVector TVector:: normalized() const
	{
		double ln = sqrt( x*x + y*y + z*z );
		TVector n(0.0,0.0,0.0 );
		if (ln != 0.0)
		{
			n.x =  x / ln;
			n.y =  y / ln;
			n.z =  z / ln;

		}
		return n;
	}

	TVector sum( int n, int c[], TVector w[] ) {     // TVector sum
		int     maxd = 0;
		TVector  v;

		for (int i=0; i<n; i++) {
			if (w[i].dim() > maxd)
				maxd = w[i].dim();
		}
		v.dimn = maxd;

		for (int i=0; i<n; i++) {
			v.x += c[i] * w[i].x;
			v.y += c[i] * w[i].y;
			v.z += c[i] * w[i].z;
		}
		return v;
	}

	TVector sum( int n, double c[], TVector w[] ) {  // TVector sum
		int     maxd = 0;
		TVector  v;

		for (int i=0; i<n; i++) {
			if (w[i].dim() > maxd)
				maxd = w[i].dim();
		}
		v.dimn = maxd;

		for (int i=0; i<n; i++) {
			v.x += c[i] * w[i].x;
			v.y += c[i] * w[i].y;
			v.z += c[i] * w[i].z;
		}
		return v;
	}

	TVector sum( int n, TVector w[])    // TVector sum
	{
		int     maxd = 0;
		TVector  v;

		for (int i=0; i<n; i++) {
			if (w[i].dim() > maxd)
				maxd = w[i].dim();
		}
		v.dimn = maxd;

		for (int i=0; i<n; i++) {
			v.x += w[i].x;
			v.y += w[i].y;
			v.z += w[i].z;
		}
		return v;	
	}


	double dot(TVector v1, TVector v2) // скалярное произведение
	{
		return 	v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	}

	double dot3(TVector v1, TVector v2, TVector v3)
	{
		return dot(v1, v2^v3);
	}
}