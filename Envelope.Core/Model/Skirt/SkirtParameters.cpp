#include "stdafx.h"
#include "SkirtParameters.h"

namespace EnvelopeCore {
	SkirtParameters::SkirtParameters(void)
	{
		this->r0 = 1.5;
		this->r1 = 1.0;
		this->h = 3.0;
		this->density = 13; // для резины
		this->kb_hor = 1;
		this->kb_ver = 1;
		this->kl_hor = 1;
		this->kl_ver = 1;
	}


	SkirtParameters :: ~SkirtParameters(void)
	{
	}

	bool SkirtParameters :: Read(const char * fileName , const char * section)
	{
		CIniReader iniReader(fileName);
		this->density = iniReader.ReadFloat(section, "density");
		this->h = iniReader.ReadFloat(section, "h");
		this->kb_hor = iniReader.ReadFloat(section, "kb_hor");
		this->kb_ver = iniReader.ReadFloat(section, "kb_ver");
		this->kl_hor = iniReader.ReadFloat(section, "kl_hor");
		this->kl_ver = iniReader.ReadFloat(section, "kl_ver");
		this->r0 = iniReader.ReadFloat(section, "r0");
		this->r1 = iniReader.ReadFloat(section, "r1");

		return true;
	}

	bool SkirtParameters :: Save(const char * fileName , const char * section) const 
	{
		CIniWriter iniWriter(fileName);
		iniWriter.WriteFloat(section, "density", this->density  );   
		iniWriter.WriteFloat(section, "h", this->h  );  
		iniWriter.WriteFloat(section, "kb_hor", this->kb_hor  );   
		iniWriter.WriteFloat(section, "kb_ver", this->kb_ver  );   
		iniWriter.WriteFloat(section, "kl_hor", this->kl_hor  );   
		iniWriter.WriteFloat(section, "kl_ver", this->kl_ver  );   
		iniWriter.WriteFloat(section, "r0", this->r0  );   
		iniWriter.WriteFloat(section, "r1", this->r1  );   

		return true;
	}
}