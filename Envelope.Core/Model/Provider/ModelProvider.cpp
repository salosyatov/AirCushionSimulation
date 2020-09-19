#include "Stdafx.h"
#include "ModelProvider.h"

namespace EnvelopeCore {
	ModelProvider :: ModelProvider(void) 
	{
		throw exception("ModelProvider :: ModelProvider(void) ");
	}

	ModelProvider :: ModelProvider(CalculationParameters calculationParameters, ModelParameters modelParameters)
	{
		initTotalEdge = 0.0;
		M.setlength(3, 3);
		s.setlength(3);

		g.x = 0.0;
		g.y = 0.0;
		g.z = - M_G / M_1000;

		InitializeModel(calculationParameters, modelParameters);

	}


	ModelProvider::~ModelProvider(void)
	{
		if (restSkirtData) delete restSkirtData;
		if (tempSkirtData) delete tempSkirtData;
		if (prevSkirtData) delete prevSkirtData;

		if (landscapeData) delete landscapeData;
	}

	void ModelProvider :: SetCallbackFunc(void (*func)(ModelProvider *sender, Summary &s))
	{
		callbackFunc = func;
	}


	double ModelProvider :: CalcHeight(double x, double y)
	{
		return GetHeightDummy(x, y);
	}


	double ModelProvider :: GetInternalPressure( double t )
	{
		return GetInternalPressureDummy(t);
	}


	double ModelProvider :: GetHeightDummy(double x, double y)
	{
		double z = 1.6 * exp( -( x - 8) * ( x - 8) /3)  ;
		return z > 0 ? z : 0.0;

	}

	double ModelProvider :: GetInternalPressureDummy( double t )
	{
		double p = 100100 / M_1000;
		return p;
	}

	void  ModelProvider :: GetSkirtBasisPlacement(double t, TPoint &centre, double &alpha, double &beta, double &gamma )
	{
		GetSkirtBasisPlacementDummy(t, centre, alpha, beta, gamma);

	}

	void ModelProvider :: GetSkirtBasisPlacementDummy(double t, TPoint &centre, double &alpha, double &beta, double &gamma )
	{
		centre.x = 0.2 * t;
		centre.y = 0.0; 
		centre.z = 4.1; 

		alpha = 0.0;
		beta  = 0.0;
		gamma = 0.0;

		return;
	}




	bool  ModelProvider ::  InitializeLandscape(LandscapeData * landscapeData)
	{
		return InitializeLandscapeDummy(landscapeData);
	}

	bool ModelProvider :: InitializeLandscapeDummy(LandscapeData *landscapeData)
	{
		int N_x = landscapeData->GetCalculationParameters().GetNX();
		int N_y = landscapeData->GetCalculationParameters().GetNY();

		const double * x = landscapeData->GetX();
		const double * y = landscapeData->GetY();
		double ** zz = landscapeData->GetZZ();

		int i(0), j(0);
#pragma omp parallel
		{
#pragma omp for nowait private (j)
			for( i = 0; i < N_x; i++)
				for( j = 0; j < N_y; j++)
				{
					zz[i][j] = GetHeightDummy(x[i], y[j]);
				}
		}
		return true;
	}

	void ModelProvider::InitializeModel(CalculationParameters calculationParameters, ModelParameters modelParameters)
	{
		this->modelParameters = modelParameters;
		this->calculationParameters = calculationParameters;

		int N_phi = calculationParameters.GetNPhi();
		int N_zeta = calculationParameters.GetNZeta();

		const SkirtParameters & skirtParameters = modelParameters.GetSkirtParameters();
		this->restSkirtData = new SkirtData(calculationParameters, skirtParameters);
		this->tempSkirtData = new SkirtData(calculationParameters, skirtParameters);
		this->prevSkirtData = new SkirtData(calculationParameters, skirtParameters);

		this->SetUnstressedState(restSkirtData);


		int cycleNumber = this->calculationParameters.GetCycleNumber();

		if ( cycleNumber == -1)
		{
			// если не указано начальное состоянии в номере файла, то устанавливаем равновесное
			this->SetUnstressedState(tempSkirtData); 
			this->SetUnstressedState(prevSkirtData); 
			this->calculationParameters.SetT(this->calculationParameters.GetTimeMin());

			cout << "Initial unstressed state is set" << endl;

		}
		else
		{
			double t;
			inputFromFile(tempSkirtData, cycleNumber, t);
			throw std::exception("inputFromFile(prevSkirtData, cycleNumber, t)");

			inputFromFile(prevSkirtData, cycleNumber, t); 
			this->calculationParameters.SetT(t);

		}


		this->landscapeData = new LandscapeData(calculationParameters, modelParameters.GetLandscapeParameters());
		InitializeLandscape(landscapeData);
	}


	void  ModelProvider :: PreCalculate(SkirtData * skirtData) const
	{
		int N_phi = calculationParameters.GetNPhi();
		int N_zeta = calculationParameters.GetNZeta();

		int i(0), j(0);
#pragma omp parallel
		{

#pragma omp for nowait private (j) 
			for ( i = 0 + SHIFT_LEFT ; i < N_phi + SHIFT_LEFT; i++)
				for ( j = 0 + SHIFT_BOTTOM; j < N_zeta  + SHIFT_BOTTOM; j++ )
				{

					Node & n_cur = skirtData->GetNN()[i][j];
					Neighbour  neighbours[EX_SIDE_DIRECTION_COUNT];
					getExSideNeighbours(i, j, N_phi, N_zeta, neighbours);

					for (int k = 0 ; k < EX_SIDE_DIRECTION_COUNT; k++)
					{
						Neighbour n = neighbours[k];
						if (isNeighbourTypeReal( n.type))
						{
							TVector L_prev = n_cur.VL[k];
							TVector L = skirtData->GetNN()[n.i][n.j].x - n_cur.x;
							n_cur.VL[k] = L;
							n_cur.NormalizedStretchForce[k] = (2 * L - L_prev).normalized(); 
							n_cur.Factors[k] = L * L_prev.len() / dot(L, L_prev);
						}
					}

				}
		}


	}


	void  ModelProvider :: SetUnstressedState( SkirtData * skirtData)
	{
		//Геометрические параметры

		double r0 =	modelParameters.GetSkirtParameters().GetR0();
		double r1 = modelParameters.GetSkirtParameters().GetR1();
		double h  = modelParameters.GetSkirtParameters().GetH();


		int N_phi = calculationParameters.GetNPhi();
		int N_zeta = calculationParameters.GetNZeta();

		double slope = (r0 - r1)/ h;

		double dphi , dzeta;

		dphi = (M_2_PI) / (double)(N_phi);
		dzeta = h / (double)(N_zeta);


		int i(0), j(0);
		//#pragma omp parallel
		{

			double phi = (0.5 - SHIFT_LEFT) * dphi;
			//#pragma omp for nowait private (j)
			// Расчет узловых величин, не зависящих от соседних узлов
			for ( i = 0  ; i < N_phi + SHIFT_LEFT + SHIFT_RIGHT; i++, phi += dphi)
			{
				if (phi >= M_2_PI) 
					phi =  0.5 * dphi;

				double zeta = - h - SHIFT_BOTTOM * dzeta ;
				for ( j = 0 ; j < N_zeta + 1 + SHIFT_BOTTOM + SHIFT_TOP; j++, zeta += dzeta )
				{
					double r = slope * zeta + r0 ;
					CylindricPoint3D p(r, phi, zeta);
					TVector u(0.0, 0.0,0.0);
					TVector v(0.0, 0.0,0.0);

					skirtData->GetNN()[i][j].x  = p.ToCartesian();
					skirtData->GetNN()[i][j].u = u;
					skirtData->GetNN()[i][j].v = v;
				}
			}
		}

		SetNeighbourhoodData(skirtData);

		double sum_e = 0.0;

		int  k(0);
#pragma omp parallel
		{
#pragma omp for nowait private (j, k) reduction(+ : sum_e)
			for ( i = 0 + SHIFT_LEFT; i < N_phi + SHIFT_LEFT; i++)
				for ( j = 0 + SHIFT_BOTTOM ; j < N_zeta + 1 + SHIFT_BOTTOM; j++ )
				{

					Node & n_cur = skirtData->GetNN()[i][j];
					Neighbour  neighbours[EX_SIDE_DIRECTION_COUNT];
					getExSideNeighbours(i, j, N_phi, N_zeta, neighbours);

					for (k = 0 ; k < EX_SIDE_DIRECTION_COUNT; k++)
					{
						Neighbour n = neighbours[k];
						if (isNeighbourTypeReal( n.type))
						{

							TVector L = skirtData->GetNN()[n.i][n.j].x - n_cur.x;
							n_cur.VL[k] = L;

							n_cur.L0[k] = L.len();

						}
					}

					for ( k = 0 ; k < NEIGHBOUR_COUNT; k++)
					{
						sum_e += n_cur.e[k];
					}
				}
		}

		initTotalEdge = sum_e;


	}


	void ModelProvider :: SetNeighbourhoodData( SkirtData * skirtData) const
	{
		double rho  = modelParameters.GetSkirtParameters().GetDensity();

		int N_phi = calculationParameters.GetNPhi();
		int N_zeta = calculationParameters.GetNZeta();

		int i(0), j(0);
#pragma omp parallel
		{
			// Расчет узловых величин, зависящих от соседних узлов
#pragma omp for nowait private (j)
			for ( i = 0 + SHIFT_LEFT; i < N_phi + SHIFT_LEFT; i++)
			{
				for ( j = 0 + SHIFT_BOTTOM ; j < N_zeta + 1 + SHIFT_BOTTOM; j++ )
				{
					int i_l, i_r, j_b, j_t;

					if (SHIFT_LEFT == 0)
					{
						i_l =  ((i - 1) + N_phi) % N_phi;
						i_r = ((i + 1) + N_phi) % N_phi;
					}
					else
					{
						i_l = i - 1;
						i_r = i + 1;
					}


					j_b = j - 1;
					j_t = j + 1;


					TPoint p = skirtData->GetNN()[i][j].x;

					TPoint p0 = skirtData->GetNN()[i_r][j].x;
					TPoint p1 = skirtData->GetNN()[i][j_t].x;
					TPoint p2 = skirtData->GetNN()[i_l][j].x;
					TPoint p3 = skirtData->GetNN()[i][j_b].x;

					double right = d(p, p0);
					double top = d(p, p1);
					double left = d(p, p2);
					double bottom = d(p, p3);

					// Индексы обозначают направления - вправо, вверх, влево, вниз
					skirtData->GetNN()[i][j].e[0] = right;
					skirtData->GetNN()[i][j].e[1] = top;
					skirtData->GetNN()[i][j].e[2] = left;
					skirtData->GetNN()[i][j].e[3] = bottom;

					double S = 0.25 * (left + right) * (bottom + top);
					skirtData->GetNN()[i][j].S = S ;
					skirtData->GetNN()[i][j].m = S * rho;
				
				}
			}
		}

	}

	void ModelProvider :: SetBoundaryConditions(SkirtData * skirtData) const
	{
		int N_phi = calculationParameters.GetNPhi();
		int N_zeta = calculationParameters.GetNZeta();

#if (SHIFT_BOTTOM == 1)
		for (int i = 0 + SHIFT_LEFT ; i < N_phi + SHIFT_LEFT; i++)
		{

			//Узел из гипотетического нижнего слоя
			Node & n_b = skirtData->GetNN()[i][0];
			n_b.x = skirtData->GetNN()[i][1].x - (skirtData->GetNN()[i][2].x - skirtData->GetNN()[i][1].x).normalized() * restSkirtData->GetNN()[i][1].e[3];
			// по идее, эти узлы не меняются со временем, только у верхнего меняется кривизна
			skirtData->GetNN()[i][N_zeta + SHIFT_BOTTOM].x = restSkirtData->GetNN()[i][N_zeta + SHIFT_BOTTOM].x;
			skirtData->GetNN()[i][N_zeta + 1 + SHIFT_BOTTOM].x = restSkirtData->GetNN()[i][N_zeta + 1 + SHIFT_BOTTOM].x;
			n_b.ClearForces();			

		}
#endif

#if (SHIFT_LEFT == 1)
		for (int j = 0 ; j < N_zeta + 1 + SHIFT_BOTTOM + SHIFT_TOP; j++)
		{

			{
				skirtData->GetNN()[0][j].x = skirtData->GetNN()[N_phi][j].x; // слева
				skirtData->GetNN()[0][j].ClearForces();
				skirtData->GetNN()[N_phi + SHIFT_LEFT][j].x = skirtData->GetNN()[SHIFT_LEFT][j].x; // справа
				skirtData->GetNN()[N_phi + SHIFT_LEFT][j].ClearForces();
			}
		}
#endif

	}

	void ModelProvider :: Start(void (*func)(ModelProvider *sender, Summary &s))
	{
		if (func)
		{
			SetCallbackFunc(func);
		}



		SkirtData skirtData(calculationParameters, modelParameters.GetSkirtParameters() );

		double dt = calculationParameters.GetDt();


		clock_t t1 = clock();
		clock_t t2;

		// Расчет
		double t = calculationParameters.GetT();
		double & t_out = t;
		double tOutput = calculationParameters.GetT();

		while ( t <= calculationParameters.GetTimeMax())
		{


			//Устанавливаем начальные значения
			if (InitStep(t, &skirtData))
			{
				SetBoundaryConditions(&skirtData);

				PreCalculate(&skirtData);

				//Непосредственный расчет
				Calculate(t, t_out, dt,  &skirtData);
				SetBoundaryConditions(&skirtData); 
				FinishStep(&skirtData );
			}

			t = t_out;

			if (calculationParameters.GetOutputEachStep() || t >  tOutput)
			{
				int cycleNumber = calculationParameters.GetCycleNumber();
				calculationParameters.SetCycleNumber(++cycleNumber);

				//Выводим рассчитанные данные
				Summary s = Output(t, &skirtData);
				t2 = clock();
				double cycleTime = (double) (t2 - t1) / (double)CLOCKS_PER_SEC;

				s.SetT(t);
				s.SetCycleTime(cycleTime);


				if (callbackFunc) 
					callbackFunc(this, s);

				t1 = clock();

				tOutput += calculationParameters.GetDtOutput();
			}


			//Переходим на следующий шаг
			calculationParameters.SetT(t);
		}


	}

	bool ModelProvider :: InitStep(double t, SkirtData * skirtData)
	{

		double a, b, g;
		TPoint centre;
		this->GetSkirtBasisPlacement(t, centre, a, b, g);

		UpdateTransformationData(centre, a, b, g);

		//Получаем начальное (на текущем временном шаге) состояние из промежуточных (сохраненных на предыдущем шаге) данных
		if (tempSkirtData)
		{
			int N_phi = skirtData->GetCalculationParameters().GetNPhi();
			int N_zeta = skirtData->GetCalculationParameters().GetNZeta();

			int i(0), j(0), k(0);

#pragma omp parallel
			{

#pragma omp for nowait private (j)
				for ( i = 0 + SHIFT_LEFT; i < N_phi + SHIFT_LEFT; i++)
					for ( j = 0 + SHIFT_BOTTOM; j < N_zeta + 1 + SHIFT_BOTTOM; j++ )
					{
						const Node & n_cur_temp = tempSkirtData->GetNN()[i][j];
						Node & n_cur = skirtData->GetNN()[i][j];

						memcpy(&n_cur, &n_cur_temp, sizeof(Node));
						n_cur.ClearForces();
					}
			}
		}
		else
		{
			throw std::exception("No initial data");
		}
		return true;


	}

	Summary ModelProvider :: Output(double t, SkirtData * skirtData)
	{


		int N_phi = calculationParameters.GetNPhi();
		int N_zeta = calculationParameters.GetNZeta();

		SetNeighbourhoodData(skirtData);

		double sum_e = 0.0;
		int sum_gr = 0;
		double sum_u2 = 0.0;
		double sum_f2 = 0.0;
		double sum_C2 = 0.0;

		int i(0), j(0);

#pragma omp parallel
		{

#pragma omp for nowait private (i) reduction(+ : sum_e, sum_gr, sum_u2, sum_f2, sum_C2)
			for ( j = 0 + SHIFT_BOTTOM; j < N_zeta + 1 + SHIFT_BOTTOM; j++ )
			{
				TVector C;
				for ( i = 0 + SHIFT_LEFT ; i < N_phi + SHIFT_LEFT; i++)
				{
					const Node & n_cur = skirtData->GetNN()[i][j];

					for (int k = 0 ; k < NEIGHBOUR_COUNT; k++)
					{
						sum_e += n_cur.e[k];
					}

					if (n_cur.isGrounded)
						sum_gr++;

					TVector u = n_cur.x - restSkirtData->GetNN()[i][j].x;

					sum_u2 += u.len2();
					sum_f2 += (sum(FORCE_COUNT, n_cur.F)).len2();
					C += n_cur.x;

				}

				sum_C2 += C.x * C.x + C.y * C.y;

			}
		}


		if (calculationParameters.GetOutputToTecplot())
		{
			if (calculationParameters.GetOutputLandscapeToTecplot())
			{
				TransformSkirtDataToLandscape(skirtData);
			}

			OutputModelToTecplot( t, skirtData, calculationParameters.GetOutputLandscapeToTecplot());
		}

		Summary s(sum_e, sum_gr, sum_u2/(N_phi * (N_zeta + 1)));
		s.SetRelativeExpansion( (sum_e / initTotalEdge - 1.0) * 100.0 );
		s.SetForcePerNode(sum_f2 / (N_phi * (N_zeta + 1)) );
		s.SetCentralDisplacement(sum_C2 / (N_zeta + 1));

		int cycleNumber = calculationParameters.GetCycleNumber();
		return s; 
	}

	bool ModelProvider :: TransformSkirtDataToLandscape(SkirtData * skirtData)
	{
		int N_phi = skirtData->GetCalculationParameters().GetNPhi();
		int N_zeta = skirtData->GetCalculationParameters().GetNZeta();

		int i(0), j(0);

#pragma omp parallel
		{

#pragma omp for nowait private (j) 
			for ( i = 0 ; i < N_phi; i++)
				for ( j = 0 ; j < N_zeta + 1; j++ )
				{
					Node & n_cur = skirtData->GetNN()[i][j];

					Transform(SKIRT_POINT_TO_LANDSCAPE_POINT, n_cur.x, n_cur.x);
					Transform(SKIRT_VECTOR_TO_LANDSCAPE_VECTOR, n_cur.v, n_cur.v);
					Transform(SKIRT_VECTOR_TO_LANDSCAPE_VECTOR, n_cur.u, n_cur.u);

				}
		}

		return false;
	}


	void ModelProvider :: OutputModelToTecplot(double t, SkirtData * skirtData, bool outputLandscapeToTecplot) const
	{
		const CalculationParameters & calculationParameters = this->calculationParameters;
		double dt = calculationParameters.GetDt();
		int id = (int)(M_1000 * t/dt) + 1; 

		char fname[255];
		sprintf_s(fname,"skirt_dt%f_t%f.dat", dt, t); 

		outputModelToTecplot(fname, t, id, (const Node **) skirtData->GetNN(), calculationParameters.GetNPhi(), calculationParameters.GetNZeta(),
			outputLandscapeToTecplot,
			this->landscapeData->GetX(),  this->landscapeData->GetY(), (const double **) this->landscapeData->GetZZ(), calculationParameters.GetNX(), calculationParameters.GetNY()) ;


	}


	bool ModelProvider ::  FinishStep(SkirtData * skirtData)
	{
		int N_phi = skirtData->GetCalculationParameters().GetNPhi();
		int N_zeta = skirtData->GetCalculationParameters().GetNZeta();

		int i(0), j(0);

#pragma omp parallel
		{

#pragma omp for nowait //private (j) 
			for ( i = 0 + SHIFT_LEFT ; i < N_phi + SHIFT_LEFT; i++)

				memcpy(tempSkirtData->GetNN()[i], skirtData->GetNN()[i], sizeof(Node) * (N_zeta + 1 + SHIFT_BOTTOM + SHIFT_TOP));
	
		}
		return false;

	}


	//-------------------- Вычисления --------------------------------------
	void ModelProvider :: Calculate(double t, double & t_out, double & dt, SkirtData * skirtData)
	{
		//расчет
		int N_phi = skirtData->GetCalculationParameters().GetNPhi();
		int N_zeta = skirtData->GetCalculationParameters().GetNZeta();

		//------------------ Сначала рассчитываем значения, общие для всех узлов


		TVector gravitationAcceleration;
		if (!calculationParameters.GetCalcScheme()[FORCE_GR_INDEX].ignore)
		{
			gravitationAcceleration = this->CalculateGravitation();
		}


		double pressure = this->GetInternalPressure(t) - this->modelParameters.GetP0();
		const double * kl = this->restSkirtData->GetSkirtParameters().GetKl();
		const double * E = this->restSkirtData->GetSkirtParameters().GetE();
		double thickness = this->restSkirtData->GetSkirtParameters().GetThickness();
		double h3 = thickness * thickness * thickness;
		double mu = this->modelParameters.GetMu();
		//------------------

		int i(0), j(0), k(0);
#pragma omp parallel
		{

#pragma omp for nowait private (j, k) 
			for ( i = 0 + SHIFT_LEFT ; i < N_phi + SHIFT_LEFT; i++)
			{
				for ( j = 0 + SHIFT_BOTTOM ; j < N_zeta + SHIFT_BOTTOM ; j++ ) // по вертикали обрабатываем узлы от 0  до (N_zeta - 1), хотя слой 0 обрабатывается иначе, а N_zeta закреплен
				{
					Node & n_cur = skirtData->GetNN()[i][j]; 
					const Node & n_cur_rest = restSkirtData->GetNN()[i][j]; // соответствующий узел в состоянии покоя
					double m = n_cur_rest.m; //NOTE: масса узла. 

					TPoint x_cur = n_cur.x; // текущее положение	
					TPoint points[SIDE_DIRECTION_COUNT];
					Neighbour  neighbours[SIDE_DIRECTION_COUNT];
					getSideNeighbours(i, j, N_phi, N_zeta, neighbours);

					for (k = 0; k < SIDE_DIRECTION_COUNT; k++ )
					{
						Neighbour n = neighbours[k];
						points[k] = skirtData->GetNN()[n.i][n.j].x;
					}

					PointPattern * pointPattern;
					pointPattern = new FivePointPattern(x_cur,  points); 


					if (!calculationParameters.GetCalcScheme()[FORCE_ST_INDEX].ignore && calculationParameters.GetCalcScheme()[FORCE_ST_INDEX].sch == EXPLICIT)
					{

						TVector stretchForce = calculateStretchExplicit(n_cur_rest, *pointPattern, kl);
						n_cur.F[FORCE_ST_INDEX] = stretchForce;
					}


					TVector normal = calculationParameters.GetCalcScheme()[FORCE_PR_INDEX].ignore && calculationParameters.GetCalcScheme()[FORCE_FR_INDEX].ignore ? nullVector : pointPattern->GetNormal();

					TVector pressureForce = calculationParameters.GetCalcScheme()[FORCE_PR_INDEX].ignore ? nullVector : CalculatePressure(n_cur_rest, normal, pressure);
					TVector frictionForce = calculationParameters.GetCalcScheme()[FORCE_FR_INDEX].ignore ? nullVector : CalculateFriction(n_cur_rest, n_cur, normal, pressure, mu);

					if (pointPattern) delete pointPattern;

					n_cur.F[FORCE_GR_INDEX] = gravitationAcceleration * m;			
					n_cur.F[FORCE_PR_INDEX] = pressureForce ;
					n_cur.F[FORCE_FR_INDEX] = frictionForce ;
				}
			}
		}


		//--------------------------------------------------

		TVector fl[SIDE_DIRECTION_COUNT];
		// Расчет изгиба считаем последовательно
		if (!calculationParameters.GetCalcScheme()[FORCE_FL_INDEX].ignore && calculationParameters.GetCalcScheme()[FORCE_FL_INDEX].sch == EXPLICIT)
		{
			for ( i = 0 + SHIFT_LEFT ; i < N_phi + SHIFT_LEFT; i++)
			{
				for ( j = 0 + SHIFT_BOTTOM ; j < N_zeta + SHIFT_BOTTOM ; j++ ) // по вертикали обрабатываем узлы от 0  до (N_zeta - 1), хотя слой 0 обрабатывается иначе, а N_zeta закреплен
				{

					Node & n_cur = skirtData->GetNN()[i][j]; 
					const Node & n_cur_rest = restSkirtData->GetNN()[i][j]; // соответствующий узел в состоянии покоя
					double m = n_cur_rest.m; //NOTE: масса узла. 

					TPoint x_cur = n_cur.x; // текущее положение	
					TPoint points[SIDE_DIRECTION_COUNT];
					Neighbour  neighbours[SIDE_DIRECTION_COUNT];
					getSideNeighbours(i, j, N_phi, N_zeta, neighbours);

					Node* pnodes[SIDE_DIRECTION_COUNT];

					for (k = 0; k < SIDE_DIRECTION_COUNT; k++ )
					{
						Neighbour n = neighbours[k];
						Node * pnode = skirtData->GetNN()[n.i] + n.j;
						points[k] = pnode->x;
						pnodes[k] = pnode;
					}

					PointPattern * pointPattern;
					pointPattern = new FivePointPattern(x_cur,  points); 


					TVector f_cur;
					calculateFlexural(*pointPattern, f_cur,  E, h3, fl);
					delete pointPattern ;

					n_cur.F[FORCE_FL_INDEX] += f_cur ;
					for (k = 0; k < SIDE_DIRECTION_COUNT; k++ )
					{
						pnodes[k]->F[FORCE_FL_INDEX] += fl[k] ;
					}


				}
			}
		}

		//----------------------------------------------------------
		CalculateBySolver(t, t_out, dt, skirtData);

		ProcessPenetration(skirtData);

	}


	int  ModelProvider :: CalculateBySolver(double t, double & t_out, double & dt, SkirtData * skirtData)
	{
		int N_phi = skirtData->GetCalculationParameters().GetNPhi();
		int N_zeta = skirtData->GetCalculationParameters().GetNZeta();


		int i(0), j(0);

#pragma omp parallel
		{

#pragma omp for nowait private (j) 
			for ( i = 0 + SHIFT_LEFT ; i < N_phi + SHIFT_LEFT; i++)
			{
				for ( j = 0 + SHIFT_BOTTOM ; j < N_zeta + SHIFT_BOTTOM ; j++ ) // по вертикали обрабатываем узлы от 0  до (N_zeta - 1), хотя слой 0 обрабатывается иначе, а N_zeta закреплен
				{

					TPoint x_cur, x_next ; // текущее , следующее положения	
					TVector v_cur, v_next ; // текущая , следующая скорость
					TVector F_cur; // текущая сила

					Node & n_cur = skirtData->GetNN()[i][j];
					const Node & n_cur_rest = restSkirtData->GetNN()[i][j]; // соответствующий узел в состоянии покоя
					x_cur = n_cur.x;
					v_cur = n_cur.v;


					double m = n_cur_rest.m; //NOTE: масса узла. 
					F_cur = sum(FORCE_COUNT, n_cur.F);

					TVector a =  F_cur / m ;

					v_next = v_cur + dt * a;
					x_next = x_cur + dt / M_1000 * v_next;

					n_cur.v = v_next;
					n_cur.x = x_next;
				}
			}
		}

		t_out = t + dt/ M_1000;

		return 0;
	}


	TVector ModelProvider :: CalculateGravitation() const
	{
		TVector gS;
		TVector gL(g); 

		Transform(LANDSCAPE_VECTOR_TO_SKIRT_VECTOR, gS, gL);


		return gS;
	}




	TVector ModelProvider :: CalculatePressure(const Node & n_cur_rest, const TVector & normal,  const double & p ) const
	{
		//NOTE: Здесь считаем, что площадь ячейки не меняется вследствие нерастяжимости материала 
		TVector r = p * n_cur_rest.S * normal;

		return r;
	}

	TVector ModelProvider :: CalculateFriction(const Node & n_cur_rest, const Node & n_cur, const TVector & normal, const double & p, const double & mu  ) const
	{
		TVector f(0.0, 0.0, 0.0);
		if (n_cur.isGrounded) //трение учитываем только для приземных узлов
		{	
			TVector tau = normal^(normal^(n_cur.v));
			tau.normalize();
			f = mu * p * n_cur_rest.S * tau; //NOTE: Здесь считаем, что площадь ячейки не меняется вследствие нерастяжимости материала 
		}

		return f;

	}

	double ModelProvider :: CalcDt()
	{
		throw exception("double ModelProvider :: CalcDt() not implemented");
	}

	void ModelProvider :: ProcessPenetration(SkirtData * skirtData)
	{
		int N_phi = skirtData->GetCalculationParameters().GetNPhi();
		int N_zeta = skirtData->GetCalculationParameters().GetNZeta();


		int i(0), j(0);

#pragma omp parallel
		{

#pragma omp for nowait private (j) 
			for ( i = 0 + SHIFT_LEFT ; i < N_phi  + SHIFT_LEFT; i++)
				for ( j = 0 + SHIFT_BOTTOM ; j < N_zeta + 1 + SHIFT_BOTTOM ; j++ )
				{
					Node & n_cur = skirtData->GetNN()[i][j];

					TPoint p;
					Transform(SKIRT_POINT_TO_LANDSCAPE_POINT, n_cur.x, p);

					if (IsNodeOverLandscape(p))
					{
						n_cur.isGrounded = false;
						continue;
					}
					else
					{
						n_cur.isGrounded = true;

						MoveToLandscape( p);
						Transform(LANDSCAPE_POINT_TO_SKIRT_POINT, n_cur.x, p);

						n_cur.v.x = 0.0; 
						n_cur.v.y = 0.0;
						n_cur.v.z = 0.0;
					}
				}
		}
	}

	int ModelProvider :: Transform(TransformDirection dir, TPoint & skirtPoint, TPoint & landscapePoint) const
	{

		return transform(dir, skirtPoint, landscapePoint, M, s );

	}

	bool ModelProvider :: IsNodeOverLandscape(const TPoint & p) const
	{
		return p.z > CalcHeight(p.x, p.y);
	}

	void ModelProvider :: MoveToLandscape(TPoint & p)
	{
		//Определяем, какому треугольнику относится точка

		double xP = p.x, yP = p.y;

		int N_x = this->landscapeData->GetCalculationParameters().GetNX();
		int N_y = this->landscapeData->GetCalculationParameters().GetNY();

		TPoint A, B, C;
		getThreeNeighbours(p, this->landscapeData->GetX(), this->landscapeData->GetY(), N_x, N_y, A, B, C);


		A.z = CalcHeight(A.x, A.y);
		B.z = CalcHeight(B.x, B.y);
		C.z = CalcHeight(C.x, C.y);


		TPoint t = pointProjection(p, A, B, C);
		p = t;
	}

	void ModelProvider :: UpdateTransformationData(const TPoint & centre, const double &a, const double & b, const double & g)
	{
		M[0][0] = cos(a)*cos(g) - sin(a)*cos(b)*sin(g);
		M[1][0] = sin(a)*cos(g) + cos(a)*cos(b)*sin(g) ;
		M[2][0] = sin(b)*sin(g);
		M[0][1] = -cos(a)*sin(g) - sin(a)*cos(b)*cos(g);
		M[1][1] = -sin(a)*sin(g) + cos(a)*cos(b)*cos(g);
		M[2][1] = sin(b)*cos(g);
		M[0][2] = sin(a)*sin(b);
		M[1][2] = -cos(a)*sin(b);
		M[2][2] = cos(b);

		s[0] = centre.x;
		s[1] = centre.y;
		s[2] = centre.z;
	}
}


