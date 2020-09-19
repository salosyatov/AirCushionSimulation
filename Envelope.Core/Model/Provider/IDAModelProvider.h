#pragma once
#include "Stdafx.h"
#include "ModelProvider.h"
#include "IDAUtils.h"

#include "MemoryUtils.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <ida/ida.h>
//#include <ida/ida_band.h>
#include <ida/ida_dense.h>
#include <ida/ida_spgmr.h>

#include <nvector/nvector_serial.h>
#include <sundials/sundials_dense.h>

#include <sundials/sundials_spgmr.h>
#include <sundials/sundials_types.h>

#define ZERO  RCONST(0.0)
#define ONE   RCONST(1.0)
#define TWO   RCONST(2.0)

namespace EnvelopeCore {
	class DllExport IDAModelProvider : public ModelProvider
	{
	private:
		void *mem;
		N_Vector uu, up, constraints, id, res;
		int ier;
		long int netf, ncfn;
		realtype rtol, atol, t0, t1, tout, tret;
		int  CalculateBySolver(double t, double & t_out, double & dt, SkirtData * skirtData);
	public:
		IDAModelProvider(CalculationParameters calculationParameters, ModelParameters modelParameters);
		~IDAModelProvider(void);
	};

}