#pragma once
#include "Parameters.h"

namespace EnvelopeCore {

	/**
	 * @class	SkirtParameters
	 *
	 * @brief	Skirt parameters.
	 *
	 * @author	Vs
	 * @date	22.03.2013
	 */

	class DllExport SkirtParameters : public Parameters
	{

	private:

		/**
		* @brief	Радиус верхнего основания конуса.
		*/

		double r0;

		/**
		* @brief	Радиус нижнего основания конуса (в состоянии покоя).
		*/

		double r1;

		/**
		* @brief	Высота конуса (в состоянии покоя).
		*/

		double h;

		/**
		* @brief	Поверхностная плотность (кг/м^2).
		*/

		double density;	

		/**
		* @brief	Коэффициент горизонтальной упругости изгиба, кН м.
		*/

		double kb_hor;

		/**
		* @brief	Коэффициент вертикальной упругости изгиба, кН м.
		*/

		double kb_ver;

		/**
		* @brief Коэффициент горизонтальной упругости сдвига, в кН/м
		*/

		double kl_hor;

		/**
		* @brief Коэффициент вертикальной упругости сдвига, в кН/м
		*/

		double kl_ver;

	public:
		SkirtParameters(void);
		~SkirtParameters(void);

		// Access the R0
		double GetR0(void) const	{ return(r0);	};
		void SetR0(double _r0)		{ r0 = _r0;		};

		// Access the R1
		double GetR1(void) const	{ return(r1);	};
		void SetR1(double _r1)		{ r1 = _r1;		};

		// Access the H
		double GetH(void) const	{ return(h);	};
		void SetH(double _h)	{ h = _h;		};


		// Access the Density
		double GetDensity(void) const		{ return(density);		};
		void SetDensity(double _density)	{ density = _density;	};


		// Access the Kb_hor
		double GetKb_hor(void) const	{ return(kb_hor);	};
		void SetKb_hor(double _kb_hor)	{ kb_hor = _kb_hor;	};

		// Access the Kb_ver
		double GetKb_ver(void) const	{ return(kb_ver);	};
		void SetKb_ver(double _kb_ver)	{ kb_ver = _kb_ver;	};

		// Access the Kl_hor
		double GetKl_hor(void) const	{ return(kl_hor);	};
		void SetKl_hor(double _kl_hor)	{ kl_hor = _kl_hor;	};

		// Access the Kl_ver
		double GetKl_ver(void) const	{ return(kl_ver);	};
		void SetKl_ver(double _kl_ver)	{ kl_ver = _kl_ver;	};


		bool Read(const char * fileName, const char * section ) ;

		bool Save(const char * fileName , const char * section) const ;

	};
}
