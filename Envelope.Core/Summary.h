#pragma once

namespace EnvelopeCore {
	class DllExport Summary
	{


	private:

		double forcePerNode;
		/**
		* @brief	����� ���� ����� - ��������, ��������������� ����������.
		*/

		double totalEdgeLength;

		/**
		* @brief	���������� ��������� �����.
		*/

		int groundedCount;

		/**
		* @brief	������������������ ������������, �� ���� ����� ��������� ���� ���������� ����� �� ��������� ����������, �������� �� ���������� �����.
		*/

		double deviation;

		/**
		* @brief	������������� ����������.
		*/

		double relativeExpansion;

		/**
		* @brief	����� ������� ����� ��������.
		*/

		double cycleTime;

		/**
		* @brief	��������� �����.
		*/

		double t;

		/**
		* @brief	������� ���������� �� ����������� ��� �� ������ ���� � ������� �� ����.
		*/

		double centralDisplacement;




	public:

		Summary(double _totalEdgeLength = 0.0, int _groundedCount = 0, double _deviation = 0.0);



		// Access the RelativeExpansion
		double GetRelativeExpansion(void) const					{ return(relativeExpansion);				};
		void SetRelativeExpansion(double _relativeExpansion)	{ relativeExpansion = _relativeExpansion;	};

		// Access the GroundedCount
		int GetGroundedCount(void) const			{ return(groundedCount);			};
		void SetGroundedCount(int _groundedCount)	{ groundedCount = _groundedCount;	};

		// Access the Deviation
		double GetDeviation(void) const			{ return(deviation);		};
		void SetDeviation(double _deviation)	{ deviation = _deviation;	};


		// Access the TotalEdgeLength
		double GetTotalEdgeLength(void) const				{ return(totalEdgeLength);				};
		void SetTotalEdgeLength(double _totalEdgeLength)	{ totalEdgeLength = _totalEdgeLength;	};

		// Access the CycleTime
		double GetCycleTime(void) const			{ return(cycleTime);		};
		void SetCycleTime(double _cycleTime)	{ cycleTime = _cycleTime;	};

		// Access the T
		double GetT(void) const	{ return(t);	};
		void SetT(double _t)	{ t = _t;		};

		// Access the ForcePerNode
		double GetForcePerNode(void) const			{ return(forcePerNode);			};
		void SetForcePerNode(double _forcePerNode)	{ forcePerNode = _forcePerNode;	};

		// Access the CentralDisplacement
		double GetCentralDisplacement(void) const					{ return(centralDisplacement);					};
		void SetCentralDisplacement(double _centralDisplacement)	{ centralDisplacement = _centralDisplacement;	};

	};

}