#pragma once

#include "consts.h"


#include "TPoint.h"
#include "TVector.h" 

using namespace EnvelopeMath;

namespace EnvelopeCore {
	/**
	* @class	Node
	*
	* @brief	Узел, представляющий концентрированную частицу поверхности.
	*
	* @author	Vasiliy
	* @date	05.11.2012
	*/

	class Node
	{
	public:

#pragma region Динамические величины

		/**
		* @brief	Положение узла.
		*/
		TPoint x;  

		/**
		* @brief	Скорость узла.
		*/

		TVector v;

		/**
		* @brief	Определяет, находится ли узел в приземном слое, т.е. на ландшафте.
		*/

		bool isGrounded;
#pragma endregion


#pragma region Статические величины
		/**
		* @brief	Масса узла.
		*/

		double m;

		/**
		* @brief	Площадь ячейки, центром которой является узел.
		*/

		double S;

		/**
		* @brief	Вертикальная базовая (в состоянии покоя) кривизна. Для конуса нулевая.
		*/

		double C_ver;

		/**
		* @brief	Горизонтальная базовая (в состоянии покоя) кривизна.
		*/

		double C_hor;  

		/**
		* @brief	Массив длин ребер, примыкающих к узлу.
		*/

		double e[NEIGHBOUR_COUNT];

		/**
		* @brief	Массив площадей ячеек, примыкающих к узлу.
		*/

		double A[NEIGHBOUR_COUNT];
#pragma endregion

		/**
		* @brief	Смещение узла относительно положения равновесия.
		*/
		TVector u;

		/**
		 * @brief	Массив действующий на узел сил. Нужен в большей степени для отладки 
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