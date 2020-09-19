#include "stdafx.h"
#include "LandscapeData.h"


namespace EnvelopeCore {
	LandscapeData::LandscapeData( void )
	{
		throw std::exception("The method or operation LandscapeData::LandscapeData( void ) is not implemented.");
	}


	LandscapeData::LandscapeData(CalculationParameters calculationParameters, LandscapeParameters landscapeParameters) : Data(calculationParameters)
	{


		this->landscapeParameters = landscapeParameters;

		int N_x = calculationParameters.GetNX();
		int N_y = calculationParameters.GetNY();

		double x_ini = landscapeParameters.GetX_ini();
		double x_fin = landscapeParameters.GetX_fin();
		double y_ini = landscapeParameters.GetY_ini();
		double y_fin = landscapeParameters.GetY_fin();

		double dx , dy;

		dx = (x_fin - x_ini) / (N_x);
		dy = (y_fin - y_ini) / (N_y);

		//
		// Выделяем память
		this->x = Allocate(this->x, N_x);
		this->y = Allocate(this->y, N_y);
		this->zz = Allocate(this->zz, N_x, N_y);

		//NOTE: Заполнение сетки происходит прямо в конструкторе.
		// Если сетка неоднородная, то инициализацию сетку следует
		// проводить, например, в провайдере.
		this->BuildGrid();

	}

	LandscapeData::LandscapeData(const LandscapeData &rhs)
	{
		this->calculationParameters = rhs.calculationParameters;
		this->landscapeParameters = rhs.landscapeParameters;

		int N_x = calculationParameters.GetNX();
		int N_y = calculationParameters.GetNY();

		// Выделяем память
		this->x = Allocate(this->x, N_x);
		this->y = Allocate(this->y, N_y);
		this->zz = Allocate(this->zz, N_x, N_y);

		for (int i = 0 ; i < N_x; i++)
			for (int j = 0 ; j < N_y ; j++ )
			{
				zz[i][j] = rhs.zz[i][j];
				x[i] = rhs.x[i];
				y[j] = rhs.y[j];		
			}
	}

	LandscapeData::~LandscapeData( void )
	{
		int N_x = calculationParameters.GetNX();
		int N_y = calculationParameters.GetNY();

		//освобождаем память

		DeAllocate(this->x, N_x);
		DeAllocate(this->y, N_y);
		DeAllocate(this->zz, N_x, N_y);
	}

	void LandscapeData::BuildGrid()
	{
		int N_x = calculationParameters.GetNX();
		int N_y = calculationParameters.GetNY();

		double x_ini = landscapeParameters.GetX_ini();
		double x_fin = landscapeParameters.GetX_fin();
		double y_ini = landscapeParameters.GetY_ini();
		double y_fin = landscapeParameters.GetY_fin();

		double dx , dy;

		dx = (x_fin - x_ini) / (double)(N_x);
		dy = (y_fin - y_ini) / (double)(N_y);


		//	Центры ячеек
		for(int i = 0; i < N_x; i++)
			x[i] = x_ini + ((double)i+0.5)*dx;

		for(int j = 0; j < N_y; j++)
			y[j] = y_ini + ((double)j+0.5)*dy;
	}
}
