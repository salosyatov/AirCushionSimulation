#include "stdafx.h"
#include "ModelParameters.h"

namespace EnvelopeCore {

	ModelParameters::ModelParameters(void)
	{
		p0 = 100; //атмосферное давление в кПа
		mu = 0.3;
	}


	ModelParameters::~ModelParameters(void)
	{
	}

	bool ModelParameters :: Read(const char * fileName )
	{	
		return this->landscapeParameters.Read(fileName, LANDSCAPE) && this->skirtParameters.Read(fileName, SKIRT);
	}


	bool ModelParameters :: Save(const char * fileName ) const
	{
		return this->landscapeParameters.Save(fileName, LANDSCAPE) && this->skirtParameters.Save(fileName, SKIRT);
	}
}