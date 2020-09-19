// Main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


void outputSummary(ModelProvider * sender, Summary &s)
{
	cout << s.GetT() << "\t s: \t" << s.GetCycleTime() << " \t"<< s.GetRelativeExpansion() << "%\t " << s.GetGroundedCount() << " \t" << s.GetDeviation() << " \t" << s.GetCentralDisplacement() << " \t" << s.GetForcePerNode() << endl;
}


void startSignal()
{
	Beep(1080, 500); 
}	

void badSignal()
{
	Beep(10000, 2200); 
	Beep(8300, 3200); 
}

void endSignal()
{
	Beep(1480, 1200); 
	Beep(1568, 1200); 

	Beep(440.65, 1200); 
	Beep(220, 1200); 
}

int _tmain(int argc, _TCHAR* argv[])
{
	startSignal();

	CalculationParameters calculationParameters;

	calculationParameters.SetOutputToTecplot(true);
	calculationParameters.SetOutputLandscapeToTecplot(false);
	calculationParameters.SetOutputEachStep(false);
	calculationParameters.SetDtOutput(0.5);
	calculationParameters.SetTimeMax(70.05);


	SkirtParameters skirtParameters;
	const int N_kl = 1; 
	const int N_kb = 1;

	const int N_dt = 1;
	const int N_ign = 1;

	double arr_kl[] = {10, 10 , 100}; // массив коэффициентов жесткости
	double arr_dt[] = { 0.0005, 0.010, 0.050   }; // массив шагов интегрирования
	double arr_kb[] = {0.01};
	unsigned char arr_ign[] = {0x07};
	
	for(int i_ign = 0; i_ign < N_ign; i_ign++)
	{

		for (int i_kb = 0; i_kb < N_kb; i_kb++)
		{
			double kb = arr_kb[i_kb];
		
			for (int i_dt = 0; i_dt < N_dt; i_dt++ )
			{
				calculationParameters.SetDt(arr_dt[i_dt] * M_1000);

				for (int i_kl = 0; i_kl < N_kl; i_kl++)
				{
					double kl = arr_kl[i_kl];
		
					cout << clock() << "     ############### Calculation started #################" << endl;
					cout << "dt = " << calculationParameters.GetDt() << " s" << endl;
					cout << "Kl = " << skirtParameters.GetKl()[HORIZONTAL] << " N/m"<<endl; 
					cout << "E = " << skirtParameters.GetE()[HORIZONTAL] << " Pa"<<endl; 


					cout << "IgnoreGravitation : " << calculationParameters.GetCalcScheme()[FORCE_GR_INDEX].ignore << endl;
					cout << "IgnoreStretchCompression : " << calculationParameters.GetCalcScheme()[FORCE_ST_INDEX].ignore << endl;
					cout << "IgnoreFlex : " << calculationParameters.GetCalcScheme()[FORCE_FL_INDEX].ignore << endl;
					cout << "IgnorePressure : " << calculationParameters.GetCalcScheme()[FORCE_PR_INDEX].ignore << endl;

					cout << "Stretch Scheme : " << calculationParameters.GetCalcScheme()[FORCE_ST_INDEX].sch << endl;
					cout << "Solver : " << calculationParameters.GetSolver() << endl;


					// начальное время 
					clock_t start = clock(); 
					clock_t finish;


					try
					{

						ModelParameters  modelParameters ;
						modelParameters.SetSkirtParameters(skirtParameters);

						ModelProvider * modelProvider;

						switch (calculationParameters.GetSolver())
						{
						case INTERNAL:
							modelProvider = new ModelProvider(calculationParameters, modelParameters);		
							break;
						case IDA:
							modelProvider = new IDAModelProvider(calculationParameters, modelParameters);
							break;
						default:
							throw exception("Unknown solver chosen");
							break;
						}


						modelProvider->Start(outputSummary);

						delete modelProvider;

						// время окончания
						finish = clock(); 

						// время выполнения в секундах 
						int time =  (finish - start) / CLOCKS_PER_SEC;
						int hours = time / 3600;
						int minutes = (time / 60) % 60;
						int seconds = time % 60; 

						cout << "Total Time: " << hours << 'h' << minutes << 'm' << seconds << 's' << endl; 

						cout << "Simulation finished successfully!" << endl;

					}
					catch(const std::exception &e)
					{
						cout << e.what() << endl;

						finish = clock(); 
						// время выполнения в секундах 
						cout << "Total Time: " << (double) (finish - start) / (double)CLOCKS_PER_SEC << endl; 
						cout << "Simulation FAILED!!!" << endl;
						badSignal();

					}

					cout << "############### Calculation finished #################" << endl;
				}
			}
		}
	}

	cout << clock() << " Testing finished!" << endl;
	endSignal();
}

