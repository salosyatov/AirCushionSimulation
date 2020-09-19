#pragma once
#include "CalculationParameters.h"
#include "LandscapeParameters.h"

namespace EnvelopeCore {
	/**
	* @class	ModelData
	*
	* @brief	������ ������, �������������� ���� ��� � �� ��������� � �������� �������
	*
	* @author	Vasiliy
	* @date	18.10.2012
	*/

	class ModelData
	{

	private:
		CalculationParameters calculationParameters;

		/**
		* @brief	��������� ���������.
		*/

		LandscapeParameters landscapeParameters;


		//	LandscapeData landscapeData;


	public:
		ModelData(void);
		ModelData(CalculationParameters calculationParameters);

		~ModelData(void);


		// Access the CalculationParameters
		const CalculationParameters& GetCalculationParameters(void) const					{ return(calculationParameters);					};
		void SetCalculationParameters(const CalculationParameters& _calculationParameters)	{ calculationParameters = _calculationParameters;	};

	};
}
