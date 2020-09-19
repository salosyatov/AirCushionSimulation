#pragma once
#include "SkirtParameters.h"
#include "Data.h"
#include "Node.h"

namespace EnvelopeCore {

	/**
	 * @class	SkirtData
	 *
	 * @brief	Skirt data.
	 *
	 * @author	Vs
	 * @date	22.03.2013
	 */

	class DllExport SkirtData : public Data
	{

	private:

		/**
		* @brief	Options for controlling the skirt.
		*/

		SkirtParameters skirtParameters;

		/**
		* @brief	Массив узлов, размещенных на юбке.
		*/

		Node ** nn;

	public:
		SkirtData(void);
		SkirtData(CalculationParameters calculationParameters, SkirtParameters skirtParameters);
		SkirtData(const SkirtData & rhs);
		~SkirtData(void);

		// Access the nn
		Node ** GetNN(void) { return(nn);	};

		// Access the SkirtParameters
		const SkirtParameters& GetSkirtParameters(void) const				{ return(skirtParameters);				};
		void SetSkirtParameters(const SkirtParameters& _skirtParameters)	{ skirtParameters = _skirtParameters;	};
	};

}