#pragma once
#include "CalculationParameters.h"

namespace EnvelopeCore {
	/**
	* @class	CalculatingData
	*
	* @brief	�������������� ������ - ��������� ����������, ������� �������� � �.�.
	* 			������ �������� �� ����� ��������� ����.
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
