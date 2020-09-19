#pragma once

#include "consts.h"


#include "TPoint.h"
#include "TVector.h" 

using namespace EnvelopeMath;

namespace EnvelopeCore {
	/**
	* @class	Node
	*
	* @brief	����, �������������� ����������������� ������� �����������.
	*
	* @author	Vasiliy
	* @date	05.11.2012
	*/

	class Node
	{
	public:

#pragma region ������������ ��������

		/**
		* @brief	��������� ����.
		*/
		TPoint x;  

		/**
		* @brief	�������� ����.
		*/

		TVector v;

		/**
		* @brief	����������, ��������� �� ���� � ��������� ����, �.�. �� ���������.
		*/

		bool isGrounded;
#pragma endregion


#pragma region ����������� ��������
		/**
		* @brief	����� ����.
		*/

		double m;

		/**
		* @brief	������� ������, ������� ������� �������� ����.
		*/

		double S;

		/**
		* @brief	������������ ������� (� ��������� �����) ��������. ��� ������ �������.
		*/

		double C_ver;

		/**
		* @brief	�������������� ������� (� ��������� �����) ��������.
		*/

		double C_hor;  

		/**
		* @brief	������ ���� �����, ����������� � ����.
		*/

		double e[NEIGHBOUR_COUNT];

		/**
		* @brief	������ �������� �����, ����������� � ����.
		*/

		double A[NEIGHBOUR_COUNT];
#pragma endregion

		/**
		* @brief	�������� ���� ������������ ��������� ����������.
		*/
		TVector u;

		/**
		 * @brief	������ ����������� �� ���� ���. ����� � ������� ������� ��� ������� 
		 */

		TVector F[FORCE_COUNT];



	public:
		Node(void);

		~Node(void);


		//----------------------------------------------------------
		// Input/Output streams
		friend DllExport std::istream& operator>>( std::istream&, Node&);
		friend DllExport std::ostream& operator<<( std::ostream&, Node);
	};

}