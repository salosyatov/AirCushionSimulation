//------------------------------------------------------------------
// Copyright 2002, softSurfer (www.softsurfer.com)
// This code may be freely used and modified for any purpose
// providing that this copyright notice is included with it.
// SoftSurfer makes no warranty for this code, and cannot be held
// liable for any real or imagined damage resulting from it's use.
// Users of this code must verify correctness for their application.
//------------------------------------------------------------------

#ifndef SS_Common_H
#define SS_Common_H



	enum SS_boolean {SS_FALSE=0, SS_TRUE=1, SS_ERROR=(-1)};

	// Error codes
	enum Error {
		Enot,	// no error
		Edim,	// error: dim of point invalid for operation
		Esum	// error: sum not affine (cooefs add to 1)
	};

// utility macros
#define	abs(x)		((x) >= 0 ? x : -(x));
#define	min(x,y)	((x) < (y) ? (x) : (y));
#define	max(x,y)	((x) > (y) ? (x) : (y));
#define sgn(x)        ((x) > 0 ? 1 : ((x) < 0 ? -1 : 0 ) )

#endif SS_Common_H
