#include "stdafx.h"
#include "IDAModelProvider.h"

namespace EnvelopeCore {

	static int setInitialProfile(SkirtData * skirtData, N_Vector uu, N_Vector up, 
		N_Vector id, N_Vector res);

	static void setOutData(N_Vector uu, SkirtData * skirtData);

	int residual(realtype tres, N_Vector yy, N_Vector yp, N_Vector resval, 
		void *user_data);



	IDAModelProvider :: IDAModelProvider(CalculationParameters calculationParameters, ModelParameters modelParameters)
		: ModelProvider(calculationParameters, modelParameters)
	{

		int N_phi = calculationParameters.GetNPhi();
		int N_zeta = calculationParameters.GetNZeta();

		//2. Set problem dimensions
		long int NEQ = (N_phi + SHIFT_LEFT + SHIFT_RIGHT) * (N_zeta + 1) * VARIABLE_COUNT; // Верхний слой обсчитывать не будем, так как он не изменяется

		rtol = RCONST(1.0e-4) ;
		atol = RCONST(1.0e-3);

		mem = NULL;
		uu = up = constraints = id = res = NULL;

		/* Create vectors uu, up, res, constraints, id. */
		uu = N_VNew_Serial(NEQ);
		if(check_flag((void *)uu, "N_VNew_Serial", 0)) return ;

		up = N_VNew_Serial(NEQ);
		if(check_flag((void *)up, "N_VNew_Serial", 0)) return ;

		res = N_VNew_Serial(NEQ);
		if(check_flag((void *)res, "N_VNew_Serial", 0)) return ;

		constraints = N_VNew_Serial(NEQ);
		if(check_flag((void *)constraints, "N_VNew_Serial", 0)) return ;

		id = N_VNew_Serial(NEQ);
		if(check_flag((void *)id, "N_VNew_Serial", 0)) return ;

		/* Set constraints to all 0's for all solution values. */
		N_VConst(ZERO, constraints);

		/*4. Create ida object. Call IDACreate and IDAMalloc to initialize solution */
		mem = IDACreate();
		if(check_flag((void *)mem, "IDACreate", 0)) return ;

		//5. Initialize ida solver
		ier = IDAInit(mem, residual, t0, uu, up);
		if(check_flag(&ier, "IDAInit", 1)) return ;

		//6. Specify integration tolerances
		ier = IDASStolerances(mem, rtol, atol);
		if(check_flag(&ier, "IDASStolerances", 1)) return ;

		//8. Attach linear solver module. Call IDADense to specify the linear solver
		ier = IDADense(mem, NEQ);
		if(check_flag(&ier, "IDADense", 1)) return ;

		ier = IDASpgmr(mem, 0);
		if(check_flag(&ier, "IDASpgmr", 1)) return ;

		long num_steps = 1000;
		ier = IDASetMaxNumSteps(mem, num_steps);
		if(check_flag(&ier, "IDASetMaxNumSteps", 1)) return ;

	}

	IDAModelProvider::~IDAModelProvider(void)
	{

		N_VDestroy_Serial(constraints);

		//14. Deallocate memory for solution vectors
		N_VDestroy_Serial(uu);
		N_VDestroy_Serial(up);
		N_VDestroy_Serial(id);
		N_VDestroy_Serial(res);

		//15. Free solver memory
		IDAFree(&mem);

	}

	int  IDAModelProvider :: CalculateBySolver(double t, double & t_out, double & dt, SkirtData * skirtData)
	{
		/* Set remaining input parameters. */
		t0   = t;
		t1   = t + dt / M_1000; //TODO: определить ограничение на шаг
		tout = t + dt / M_1000; //TODO:!!!


		//3. Set vectors of initial value. Initialize uu, up, id.
		setInitialProfile(skirtData, uu, up, id, res );

		//5. Initialize ida solver
		ier = IDAReInit(mem, t0, uu, up);
		if(check_flag(&ier, "IDAReInit", 1)) return(1);

		// 7. Set optional inputs
		//	ier = IDASetUserData(mem, data);
		ier = IDASetUserData(mem, (void *)skirtData);
		if(check_flag(&ier, "IDASetUserData", 1)) return(1);

		//12. Advance solution in time
		ier = IDASolve(mem, tout, &tret, uu, up, IDA_NORMAL);
		if(check_flag(&ier, "IDASolve", 1)) return(1);
		//		N_VPrint_Serial(uu);
		//		N_VPrint_Serial(up);

		//13. Get optional outputs. Print remaining counters. 
		ier = IDAGetNumErrTestFails(mem, &netf);
		check_flag(&ier, "IDAGetNumErrTestFails", 1);
		ier = IDAGetNumNonlinSolvConvFails(mem, &ncfn);
		check_flag(&ier, "IDAGetNumNonlinSolvConvFails", 1);
		if (netf != 0 || ncfn != 0)
		{
			printf("\n netf = %ld,   ncfn = %ld \n", netf, ncfn); //TODO:
		}

		setOutData(uu, skirtData);
		t_out = tret;

		return 0;

	}



	static int setInitialProfile(SkirtData * skirtData, N_Vector uu, N_Vector up, 
		N_Vector id, N_Vector res )
	{
		realtype  *udata, *updata, *iddata;
		//	long int mm, mm1, i, j, offset, loc;

		int N_phi =  skirtData->GetCalculationParameters().GetNPhi();
		int N_zeta = skirtData->GetCalculationParameters().GetNZeta();

		udata = NV_DATA_S(uu);
		updata = NV_DATA_S(up);
		iddata = NV_DATA_S(id);

		/* Initialize id to 1's. */
		N_VConst(ONE, id);  //!!!

		/* Initialize uu on all grid points. */ 

		int k(0), u_offset(0), f_offset(0);
		for (int i = 0 + SHIFT_LEFT; i < N_phi + SHIFT_LEFT; i++ )
		{
			for (int j = 0 + SHIFT_BOTTOM; j < N_zeta + 1 + SHIFT_BOTTOM; j++ )
			{
				const Node & n_cur = skirtData->GetNN()[i][j];
				udata[u_offset + SHIFT_X] = n_cur.x.x;
				udata[u_offset + SHIFT_Y] = n_cur.x.y;
				udata[u_offset + SHIFT_Z] = n_cur.x.z;
				// считаем , что скорость в м\с
				udata[u_offset + SHIFT_U] = n_cur.v.x;
				udata[u_offset + SHIFT_V] = n_cur.v.y;
				udata[u_offset + SHIFT_W] = n_cur.v.z;

				k++;
				u_offset = k * VARIABLE_COUNT;
				f_offset = k * DIMENSION_COUNT;
			}
		}

		/* Initialize up vector to 0. */
		N_VConst(ZERO, up);

		/* heatres sets res to negative of ODE RHS values at interior points. */
		residual(ZERO, uu, up, res, skirtData);

		/* Copy -res into up to get correct interior initial up values. */
		N_VScale(-ONE, res, up);


		return(0);

	}


	static void setOutData(N_Vector uu, SkirtData * skirtData)
	{
		realtype *uv;

		uv = NV_DATA_S(uu); 

		int N_phi =  skirtData->GetCalculationParameters().GetNPhi();
		int N_zeta = skirtData->GetCalculationParameters().GetNZeta();

		int i(0), j(0), k(0), u_offset(0), r(0);

#pragma omp parallel
		{

#pragma omp for nowait private (j)
			for ( i = 0 + SHIFT_LEFT; i < N_phi + SHIFT_LEFT; i++)
			{
				for ( j = 0 + SHIFT_BOTTOM; j < N_zeta + SHIFT_BOTTOM; j++ )
				{
					Node & n_cur = skirtData->GetNN()[i][j];
					int offset = getOffset(i, j, N_phi, N_zeta);
					n_cur.x.x = uv[offset + SHIFT_X];
					n_cur.x.y = uv[offset + SHIFT_Y];
					n_cur.x.z = uv[offset + SHIFT_Z];
					n_cur.v.x = uv[offset + SHIFT_U];
					n_cur.v.y = uv[offset + SHIFT_V];
					n_cur.v.z = uv[offset + SHIFT_W];

				}
			}
		}
	}


	int residual(realtype tres, N_Vector uu, N_Vector up, N_Vector resval, 
		void *user_data)
	{

		realtype *uv, *upv, *resv;

		uv = NV_DATA_S(uu); 
		upv = NV_DATA_S(up); 
		resv = NV_DATA_S(resval);

		SkirtData * skirtData = (SkirtData * ) user_data;

		const CalculationParameters & calculationParameters = skirtData->GetCalculationParameters();

		int N_phi =  calculationParameters.GetNPhi();
		int N_zeta = calculationParameters.GetNZeta();

		TVector ** flex = NULL;
		TVector nullVector;
		if (!calculationParameters.GetCalcScheme()[FORCE_FL_INDEX].ignore && calculationParameters.GetCalcScheme()[FORCE_FL_INDEX].sch == IMPLICIT)
		{

			const double * E = skirtData->GetSkirtParameters().GetE();
			double thickness = skirtData->GetSkirtParameters().GetThickness();
			double h3 = thickness * thickness * thickness;
			flex = AllocateFillingByValue(flex, N_phi + SHIFT_LEFT + SHIFT_RIGHT, N_zeta + SHIFT_BOTTOM + 1 + SHIFT_TOP, nullVector); 

			int i(0), j(0), k(0), u_offset(0), r(0);
			for ( i = 0 + SHIFT_LEFT; i < N_phi + SHIFT_LEFT; i++)
			{

				Neighbour  neighbours[SIDE_DIRECTION_COUNT];
				TVector fl[SIDE_DIRECTION_COUNT];
				for ( j = 0 + SHIFT_BOTTOM; j < N_zeta + 1 + SHIFT_BOTTOM; j++ )
				{
					TVector f;
					int cur_offset = getOffset(i, j, N_phi, N_zeta);
					int offset;
					const Node & n_cur = skirtData->GetNN()[i][j];

					TPoint** points = new TPoint*[SIDE_DIRECTION_COUNT];
					TVector* pf[SIDE_DIRECTION_COUNT];
					getSideNeighbours(i, j, N_phi, N_zeta, neighbours);

					for (k = 0; k < SIDE_DIRECTION_COUNT; k++ )
					{
						Neighbour n = neighbours[k];
						if (isNeighbourTypeReal(n.type))
						{
							offset = getOffset(n.i, n.j, N_phi, N_zeta);
							points[k] = new TPoint(uv[offset + SHIFT_X], uv[offset + SHIFT_Y], uv[offset + SHIFT_Z]);

						}
						else
						{
							if (n.type == FICTITUOUS_TOP)
							{
								points[k] = new TPoint(skirtData->GetNN()[n.i][n.j].x);
							}
							if (n.type == FICTITUOUS_BOTTOM)
							{
								points[k] = NULL;
							}

						}

						pf[k] = flex[n.i] + n.j;

					}

					TPoint x_cur = TPoint(uv[cur_offset + SHIFT_X], uv[cur_offset + SHIFT_Y], uv[cur_offset + SHIFT_Z]);
					PointPattern * pointPattern;
					pointPattern = new FivePointPattern(x_cur, (const TPoint **) points); 


					TVector f_cur;
					calculateFlexural(*pointPattern, f_cur,  E, h3, fl);

					delete pointPattern ;

					flex[i][j] += f_cur ;
					for (k = 0; k < SIDE_DIRECTION_COUNT; k++ )
					{
						delete points[k];
						*pf[k] += fl[k]; 					
					}

					delete [] points;
				}
			}
		}



		int i(0), j(0), k(0), u_offset(0), r(0);
		double m;

		//#pragma omp parallel
		{

			//#pragma omp for nowait private (j, k)
			for ( i = 0 + SHIFT_LEFT; i < N_phi + SHIFT_LEFT; i++)
			{

				Neighbour  neighbours[EX_SIDE_DIRECTION_COUNT];
				for ( j = 0 + SHIFT_BOTTOM; j < N_zeta + 1 + SHIFT_BOTTOM; j++ )
				{
					TVector f;
					int cur_offset = getOffset(i, j, N_phi, N_zeta);
					const Node & n_cur = skirtData->GetNN()[i][j];

					TVector r(uv[cur_offset + SHIFT_X], uv[cur_offset + SHIFT_Y], uv[cur_offset + SHIFT_Z]);

					getExSideNeighbours(i, j, N_phi, N_zeta, neighbours);

					for (k = 0 ; k < EX_SIDE_DIRECTION_COUNT; k++)
					{
						Neighbour n = neighbours[k];
						if (isNeighbourTypeReal(n.type)) 
						{
							int offset = getOffset(n.i, n.j, N_phi, N_zeta);
							TVector rk(uv[offset + SHIFT_X], uv[offset + SHIFT_Y], uv[offset + SHIFT_Z]);
							OrientationDirection od;
							getByExSide((const ExSideDirection &)k, &od);
							realtype kl = skirtData->GetSkirtParameters().GetKl()[od];
							f += kl * (dot(rk - r, n_cur.Factors[k]) - n_cur.L0[k]) * n_cur.NormalizedStretchForce[k];

						}
					}

					f += sum(FORCE_COUNT, n_cur.F);
					if (flex)
					{
						f += flex[i][j];
					}

					m = n_cur.m;

					resv[cur_offset + SHIFT_X] = upv[cur_offset + SHIFT_X] - uv[cur_offset + SHIFT_U];
					resv[cur_offset + SHIFT_Y] = upv[cur_offset + SHIFT_Y] - uv[cur_offset + SHIFT_V];
					resv[cur_offset + SHIFT_Z] = upv[cur_offset + SHIFT_Z] - uv[cur_offset + SHIFT_W];

					resv[cur_offset + SHIFT_U] = upv[cur_offset + SHIFT_U] - f.x / m;
					resv[cur_offset + SHIFT_V] = upv[cur_offset + SHIFT_V] - f.y / m;
					resv[cur_offset + SHIFT_W] = upv[cur_offset + SHIFT_W] - f.z / m;

				}
			}
		}

		if (flex)
			DeAllocate(flex, N_phi + SHIFT_LEFT + SHIFT_RIGHT, N_zeta + SHIFT_BOTTOM + 1 + SHIFT_TOP);

		return(0);
	}

}