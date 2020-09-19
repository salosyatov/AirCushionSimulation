#include "stdafx.h"
#include "LandscapeParameters.h"

namespace EnvelopeCore {
	LandscapeParameters::LandscapeParameters(void)
	{
		//по умолчанию
		x_ini = -10.0;
		x_fin = 40.0;
		y_ini = -10.0;
		y_fin = 40.0;

	}


	LandscapeParameters :: ~LandscapeParameters(void)
	{
	}

	bool LandscapeParameters ::  Read(const char * fileName, const char * section ) 
	{
		CIniReader iniReader(fileName);
		this->x_fin = iniReader.ReadFloat(section, "x_fin");
		this->x_ini = iniReader.ReadFloat(section, "x_ini");
		this->y_fin = iniReader.ReadFloat(section, "y_fin");
		this->y_ini = iniReader.ReadFloat(section, "y_ini");

		return true;
	}

	bool LandscapeParameters :: Save(const char * fileName , const char * section) const 
	{
		CIniWriter iniWriter(fileName);
		iniWriter.WriteFloat(section, "x_fin", this->x_fin  );
		iniWriter.WriteFloat(section, "x_ini", this->x_ini  );
		iniWriter.WriteFloat(section, "y_fin", this->y_fin  );
		iniWriter.WriteFloat(section, "y_ini", this->y_ini  );

		return true;
	}
}