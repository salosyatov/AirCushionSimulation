#pragma once
#include "Data.h"
#include "LandscapeParameters.h"

namespace EnvelopeCore {

	/**
	 * @class	LandscapeData
	 *
	 * @brief	Данные, описывающие ландшафт.
	 *
	 * @author	Vs
	 * @date	22.03.2013
	 */

	class LandscapeData : public Data
	{


		LandscapeParameters landscapeParameters;
		/**
		* @brief	Массив значений абсцисс в ДСК.
		*/

		double * x;

		/**
		* @brief	Массив значений ординат в ДСК.
		*/
		double * y ;

		/**
		* @brief	Массив значений высот ландшафта в ДСК:
		* 			 z(x,y) = zz[i][j]
		*/
		double ** zz ;

		/**
		* @fn	void LandscapeData::BuildGrid();
		*
		* @brief	Builds the grid.
		*
		* @author	Vasiliy
		* @date	19.10.2012
		*/
		void BuildGrid();
	public:
		LandscapeData();
		LandscapeData(CalculationParameters calculationParameters, LandscapeParameters landscapeParameters);
		LandscapeData(const LandscapeData &rhs);

		virtual ~LandscapeData(void);

		// Access the X
		const double * GetX(void) const	{ return(x);	}; //NOTE: в случае, если массивы координат будут заполняться извне, следует убрать const 


		// Access the Y
		const double * GetY(void) const	{ return(y);	};//NOTE: в случае, если массивы координат будут заполняться извне, следует убрать const 


		// Access the Zz
		double ** GetZZ(void) const	{ return(zz);	};
	};

}