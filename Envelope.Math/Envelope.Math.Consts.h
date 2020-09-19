#ifndef ENVELOPE_MATH_CONSTS_H
#define ENVELOPE_MATH_CONSTS_H

/**
* @enum	TransformDirection
*
* @brief	Направление преобразования (между системами координатами).
*/

enum TransformDirection {
	SKIRT_POINT_TO_LANDSCAPE_POINT,
	LANDSCAPE_POINT_TO_SKIRT_POINT, 
	SKIRT_VECTOR_TO_LANDSCAPE_VECTOR, 
	LANDSCAPE_VECTOR_TO_SKIRT_VECTOR
};

/**
* @enum	SideDirection
*
* @brief	Сторона, относительно узла.
*/

enum SideDirection {
	LEFT, RIGHT, BOTTOM, TOP
};

/**
 * @enum	ExSideDirection
 *
 * @brief	Направления, представленные частями света - North, East, South и т.д.
 */

enum ExSideDirection {
	N, NE, E, SE, S, SW, W, NW
}; 

enum OrientationDirection {
	HORIZONTAL,
	VERTICAL,
	DIAGONAL
};


#define ORIENTATION_DIRECTION_COUNT  2

#define EX_ORIENTATION_DIRECTION_COUNT  3

#define SIDE_DIRECTION_COUNT  4

#define EX_SIDE_DIRECTION_COUNT  8

#define SHIFT_X 0
#define SHIFT_Y 1
#define SHIFT_Z 2
#define SHIFT_U 3
#define SHIFT_V 4
#define SHIFT_W 5

#define VARIABLE_COUNT 6
#define DIMENSION_COUNT 3

#define NON_EXISTING_INDEX -1 // не существующий индекс соседней ячейки

#define SHIFT_TOP 1 // размер дополнительного приграничного слоя сверху
#define SHIFT_BOTTOM 1 // размер дополнительного приграничного слоя снизу
#define SHIFT_LEFT 0 // размер дополнительного приграничного слоя слева
#define SHIFT_RIGHT 0 // размер дополнительного приграничного слоя справа


#define M_PI 3.1415926535897932384626433832795
#define M_2_PI 6.283185307179586476925286766559



#endif //ENVELOPE_MATH_CONSTS_H