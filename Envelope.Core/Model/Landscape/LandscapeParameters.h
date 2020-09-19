#pragma once
#include "Parameters.h"

namespace EnvelopeCore {
	class DllExport LandscapeParameters : public Parameters
	{
		/**	
		* @brief	Границы расчетной области в ДСК.
		*	
		*/

		double x_ini;
		double y_ini;
		double x_fin;
		double y_fin;

	public:
		LandscapeParameters(void);
		~LandscapeParameters(void);

		// Access the X_ini
		double GetX_ini(void) const		{ return(x_ini);	};
		void SetX_ini(double _x_ini)	{ x_ini = _x_ini;	};

		// Access the Y_ini
		double GetY_ini(void) const		{ return(y_ini);	};
		void SetY_ini(double _y_ini)	{ y_ini = _y_ini;	};

		// Access the X_fin
		double GetX_fin(void) const		{ return(x_fin);	};
		void SetX_fin(double _x_fin)	{ x_fin = _x_fin;	};

		// Access the Y_fin
		double GetY_fin(void) const		{ return(y_fin);	};
		void SetY_fin(double _y_fin)	{ y_fin = _y_fin;	};


		bool Read(const char * fileName, const char * section ) ;

		bool Save(const char * fileName , const char * section) const ;
	};

}