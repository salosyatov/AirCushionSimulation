#pragma once

#include "consts.h"

#include "SkirtParameters.h"
#include "LandscapeParameters.h"

namespace EnvelopeCore {
	/**
	* @class	ModelParameters
	*
	* @brief	Параметры модели (не меняются во время расчета).
	*
	* @author	Vasiliy
	* @date	23.10.2012
	*/

	class DllExport ModelParameters
	{

	private:
		SkirtParameters skirtParameters;

		LandscapeParameters landscapeParameters;

		/**
		* @brief	Атмосферное давление.
		*/

		double p0;

		/**
		* @brief Коэффициент трения оболочки и ландшафта.
		*/

		double mu;


	public:
		ModelParameters(void);
		~ModelParameters(void);

		/**
		* @fn	bool ModelParameters::Read(char * fileName );
		*
		* @brief	Reads the given file.
		*
		* @author	Vasiliy
		* @date	18.10.2012
		*
		* @param [in,out]	fileName	If non-null, the file name to read.
		*
		* @return	true if it succeeds, false if it fails.
		*/

		bool Read(const char * fileName );

		bool Save(const char * fileName ) const;



		// Access the P0
		double GetP0(void) const	{ return(p0);	};
		void SetP0(double _p0)		{ p0 = _p0;		};

		void SetSkirtParameters(SkirtParameters val) { skirtParameters = val; }
		SkirtParameters GetSkirtParameters() const { return skirtParameters; }


		void SetLandscapeParameters(LandscapeParameters val) { landscapeParameters = val; }
		LandscapeParameters GetLandscapeParameters() const { return landscapeParameters; }

		// Access the Mu
		double GetMu(void) const	{ return(mu);	};
		void SetMu(double _mu)		{ mu = _mu;		};
	};
}
