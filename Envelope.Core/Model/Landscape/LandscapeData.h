#pragma once
#include "Data.h"
#include "LandscapeParameters.h"

namespace EnvelopeCore {

	/**
	 * @class	LandscapeData
	 *
	 * @brief	������, ����������� ��������.
	 *
	 * @author	Vs
	 * @date	22.03.2013
	 */

	class LandscapeData : public Data
	{


		LandscapeParameters landscapeParameters;
		/**
		* @brief	������ �������� ������� � ���.
		*/

		double * x;

		/**
		* @brief	������ �������� ������� � ���.
		*/
		double * y ;

		/**
		* @brief	������ �������� ����� ��������� � ���:
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
		const double * GetX(void) const	{ return(x);	}; //NOTE: � ������, ���� ������� ��������� ����� ����������� �����, ������� ������ const 


		// Access the Y
		const double * GetY(void) const	{ return(y);	};//NOTE: � ������, ���� ������� ��������� ����� ����������� �����, ������� ������ const 


		// Access the Zz
		double ** GetZZ(void) const	{ return(zz);	};
	};

}