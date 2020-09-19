/**
* @file	CalculationParameters.h
*
* @brief	Declares the calculation parameters class.
*/

#pragma once

#include "Parameters.h"
#include "Envelope.Core.Consts.h"

namespace EnvelopeCore {

	enum Solver
	{
		INTERNAL,

		IDA

	};

	enum scheme {
		EXPLICIT , 
		IMPLICIT
	};

	struct CalcScheme
	{
		bool ignore;
		scheme sch;

	};

	/**
	* @class	CalculationParameters
	*
	* @brief	��������� �������.
	*
	* @author	Vasiliy
	* @date	18.10.2012
	*/

	class DllExport CalculationParameters : public Parameters
	{

	private:

		/**
		* @brief	����� ����� ��� ����������� �����.
		*/

		int cycleNumber;

		/**
		* @brief	�������� ������ ���.
		*/

		bool outputEachStep;

		/**
		 * @brief	������, ������������ ����� ������� ��������� ����.
		 */

		CalcScheme calcScheme[FORCE_COUNT];

		/**
		 * @brief	��������.
		 */

		Solver solver;


	private:

		/**
		* @brief	The time minimum.
		*/

		double timeMin;
		/**
		* @brief	The time maximum.
		*/
		double timeMax;

		/**
		* @brief	��� �� ������� (� ����� ������ ��������, � ����� - ����� �����������), � ��.
		*/

		double dt;

		/**
		* @brief	��� �� ������� ����������� (������ ���������� � ��������� ).
		*/

		double dtOutput;

		/**
		* @brief	������� �����.
		*/

		double t;


		/**
		* @brief	����� ��������� (�����) �� ��� Ox.
		*/

		int n_x;

		/**
		* @brief	����� ��������� (�����) �� ��� Oy.
		*/
		int n_y;


		/**
		* @brief	����� ��������� (�����) �� �����.
		*/
		int n_phi;

		/**
		* @brief	����� ��������� (�����) �� ������.
		*/
		int n_zeta;

		/**
		* @brief	����������, �������� �� ���������� � tecplot �����.
		*/
		bool outputToTecplot;

		/**
		* @brief	true to output landscape to tecplot.
		*/

		bool outputLandscapeToTecplot;





	public:
		CalculationParameters(void);
		~CalculationParameters(void);

		bool Read(const char * fileName, const char * section ) ;

		bool Save(const char * fileName , const char * section) const ;



		/**
		���������
		**/


		// Access the N_X
		int GetNX(void) const	{ return(n_x);	};
		void SetNX(int x)		{ n_x = x;		};

		// Access the N_Y
		int GetNY(void) const	{ return(n_y);	};
		void SetNY(int y)		{ n_y = y;		};

		// Access the Zeta
		int GetNZeta(void) const	{ return(n_zeta);	};
		void SetNZeta(int zeta)	{ n_zeta = zeta;	};

		// Access the Phi
		int GetNPhi(void) const	{ return(n_phi);	};
		void SetNPhi(int phi)	{ n_phi = phi;		};

		// Access the T
		double GetT(void) const	{ return(t);	};
		void SetT(double _t)	{ t = _t;		};

		// Access the TimeMin
		double GetTimeMin(void) const		{ return(timeMin);		};
		void SetTimeMin(double _timeMin)	{ timeMin = _timeMin;	};

		// Access the TimeMax
		double GetTimeMax(void) const		{ return(timeMax);		};
		void SetTimeMax(double _timeMax)	{ timeMax = _timeMax;	};

		// Access the Dt
		double GetDt(void) const	{ return(dt);	};
		void SetDt(double _dt)		{ dt = _dt;		};

		// Access the DtOutput
		double GetDtOutput(void) const		{ return(dtOutput);		};
		void SetDtOutput(double _dtOutput)	{ dtOutput = _dtOutput;	};

		// Access the CalcScheme[FORCE_COUNT]
		const CalcScheme * GetCalcScheme(void) const
		{
			return calcScheme;						
		};


		void SetCalcScheme(const CalcScheme _calcScheme[FORCE_COUNT])	
		{
			memcpy(calcScheme, _calcScheme, FORCE_COUNT * sizeof(CalcScheme));
		};

		// Access the OutputToTecplot
		bool GetOutputToTecplot(void) const				{ return(outputToTecplot);				};
		void SetOutputToTecplot(bool _outputToTecplot)	{ outputToTecplot = _outputToTecplot;	};

		// Access the OutputToTecplot
		bool GetOutputLandscapeToTecplot(void) const				{ return(outputLandscapeToTecplot);				};
		void SetOutputLandscapeToTecplot(bool _outputLandscapeToTecplot)	{ outputLandscapeToTecplot = _outputLandscapeToTecplot;	};

		// Access the CycleNumber
		int GetCycleNumber(void) const			{ return(cycleNumber);			};
		void SetCycleNumber(int _cycleNumber)	{ cycleNumber = _cycleNumber;	};

		// Access the OutputEachStep
		bool GetOutputEachStep(void) const				{ return(outputEachStep);			};
		void SetOutputEachStep(bool _outputEachStep)	{ outputEachStep = _outputEachStep;	};

		// Access the Solver
		const Solver& GetSolver(void) const		{ return(solver);	};
		void SetSolver(const Solver& _solver)	{ solver = _solver;	};


	};

}