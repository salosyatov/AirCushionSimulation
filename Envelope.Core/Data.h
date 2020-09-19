#pragma once
#include "CalculationParameters.h"

namespace EnvelopeCore {
	class DllExport Data
	{
	protected:
		CalculationParameters calculationParameters;

	public:
		Data(void);
		Data(CalculationParameters calculationParameters);

		~Data(void);

		// Access the CalculationParameters
		const CalculationParameters& GetCalculationParameters(void) const					{ return(calculationParameters);					};
		void SetCalculationParameters(const CalculationParameters& _calculationParameters)	{ calculationParameters = _calculationParameters;	};
	};
}
