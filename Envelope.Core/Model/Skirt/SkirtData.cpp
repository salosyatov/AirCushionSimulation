#include "stdafx.h"
#include "SkirtData.h"

namespace EnvelopeCore {
	SkirtData::SkirtData(void)
	{
		throw std::exception("The method or operation is not implemented.");
	}

	SkirtData::SkirtData(const SkirtData & rhs)
	{
		this->calculationParameters = rhs.calculationParameters;
		this->skirtParameters = rhs.skirtParameters;

		int N_phi = calculationParameters.GetNPhi();
		int N_zeta = calculationParameters.GetNZeta();

		this->nn = Allocate(this->nn, N_phi, N_zeta + 1 + SHIFT_TOP);


		for (int i = 0 ; i < N_phi; i++)
			for (int j = 0 ; j < N_zeta + 1 + SHIFT_TOP; j++ )
			{
				nn[i][j] = rhs.nn[i][j];		
			}

	}

	SkirtData::SkirtData(CalculationParameters calculationParameters, SkirtParameters skirtParameters): Data(calculationParameters)
	{

		this->skirtParameters = skirtParameters;

		int N_phi = calculationParameters.GetNPhi();
		int N_zeta = calculationParameters.GetNZeta();

		double dphi , dzeta;

		dphi = (M_PI) / (N_phi);
		dzeta = (skirtParameters.GetH()) / (N_zeta);

		this->nn = Allocate(this->nn, N_phi, N_zeta + 1 + SHIFT_TOP);

	}

	SkirtData::~SkirtData(void)
	{
		int N_phi = calculationParameters.GetNPhi();
		int N_zeta = calculationParameters.GetNZeta();

		DeAllocate(this->nn, N_phi, N_zeta + 1 + SHIFT_TOP);
	}
}