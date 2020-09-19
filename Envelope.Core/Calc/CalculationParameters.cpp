#include "stdafx.h"
#include "CalculationParameters.h"

namespace EnvelopeCore {
	CalculationParameters::CalculationParameters(void)
	{
		n_x = 100;
		n_y = 100;
		n_phi = 32;
		n_zeta = 31;


		timeMin = 0.0;
		timeMax = 90.0;
		t = timeMin;
		dt = 1;
		dtOutput = 10;

		cycleNumber = -1;

		calcScheme[FORCE_GR_INDEX].ignore = false;
		calcScheme[FORCE_GR_INDEX].sch = EXPLICIT;

		calcScheme[FORCE_ST_INDEX].ignore = false;
		calcScheme[FORCE_ST_INDEX].sch = EXPLICIT;

		calcScheme[FORCE_FL_INDEX].ignore = false;
		calcScheme[FORCE_FL_INDEX].sch = EXPLICIT;

		calcScheme[FORCE_PR_INDEX].ignore = false;
		calcScheme[FORCE_PR_INDEX].sch = EXPLICIT;

		calcScheme[FORCE_FR_INDEX].ignore = false;
		calcScheme[FORCE_FR_INDEX].sch = EXPLICIT;

		solver = INTERNAL;

		outputToTecplot = false;
		outputLandscapeToTecplot = false; 

		outputEachStep = false;
	}


	CalculationParameters::~CalculationParameters(void)
	{
	}

	bool CalculationParameters::Read(const char * fileName , const char * section)
	{
		CIniReader iniReader(fileName);

		this->dt = iniReader.ReadFloat(section, "dt");
		this->timeMax = iniReader.ReadFloat(section, "timeMax");
		this->timeMin = iniReader.ReadFloat(section, "timeMin");

		this->n_x = iniReader.ReadInteger(section, "n_x");
		this->n_y = iniReader.ReadInteger(section, "n_y");
		this->n_phi = iniReader.ReadInteger(section, "n_phi");
		this->n_zeta = iniReader.ReadInteger(section, "n_zeta");

		return true;
	}

	bool CalculationParameters::Save(const char * fileName , const char * section) const
	{
		CIniWriter iniWriter(fileName);

		iniWriter.WriteFloat(section, "dt", this->dt  );
		iniWriter.WriteFloat(section, "timeMax", this->timeMax  );
		iniWriter.WriteFloat(section, "timeMin", this->timeMin  );


		iniWriter.WriteInteger(section, "n_x", this->n_x  );
		iniWriter.WriteInteger(section, "n_y", this->n_y  );
		iniWriter.WriteInteger(section, "n_phi", this->n_phi  );
		iniWriter.WriteInteger(section, "n_zeta", this->n_zeta  );

		return true;
	}

}
