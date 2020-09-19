#pragma once
#include "CalculationParameters.h"

namespace EnvelopeCore {
	/**
	* @class	CalculatingData
	*
	* @brief	Рассчитываемые данные - различные показатели, массивы значений и т.д.
	* 			Данные хранятся на одном временном слое.
	*
	* @author	Vasiliy
	* @date	18.10.2012
	*/

	class CalculatingData
	{
		CalculationParameters calculationParameters;

	public:
		CalculatingData(void);
		CalculatingData(CalculationParameters calculationParameters);
		~CalculatingData(void);
	};
}
