#ifndef ENVELOPE_MATH_CONSTS_H
#define ENVELOPE_MATH_CONSTS_H

/**
* @enum	TransformDirection
*
* @brief	����������� �������������� (����� ��������� ������������).
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
* @brief	�������, ������������ ����.
*/

enum SideDirection {
	LEFT, RIGHT, BOTTOM, TOP
};

/**
 * @enum	ExSideDirection
 *
 * @brief	�����������, �������������� ������� ����� - North, East, South � �.�.
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

#define NON_EXISTING_INDEX -1 // �� ������������ ������ �������� ������

#define SHIFT_TOP 1 // ������ ��������������� ������������� ���� ������
#define SHIFT_BOTTOM 1 // ������ ��������������� ������������� ���� �����
#define SHIFT_LEFT 0 // ������ ��������������� ������������� ���� �����
#define SHIFT_RIGHT 0 // ������ ��������������� ������������� ���� ������


#define M_PI 3.1415926535897932384626433832795
#define M_2_PI 6.283185307179586476925286766559



#endif //ENVELOPE_MATH_CONSTS_H