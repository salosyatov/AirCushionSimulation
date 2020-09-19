#include "stdafx.h"
#include "Node.h"

namespace EnvelopeCore {
	Node::Node(void)
	{
		isGrounded = false;
		C_hor = C_ver = 0.0;
	}


	Node::~Node(void)
	{
	}

	//------------------------------------------------------------------
	// IO streams
	//------------------------------------------------------------------

	// Read input Node format: "((%f, %f, %f))"
	std::istream& operator>>( std::istream& input, Node& N) {
		char c;

		input >> c;                // skip '('
		input >> c;                // skip '('
		input >> N.x ;
		input >> c;                // skip ')'
	
			input >> c;                // skip '('
		input >> N.v ;
		input >> c;                // skip ')'
		input >> c;                // skip ')'

		char g;
		input >> g;

		N.isGrounded =  g == '+' ;

		return input;
	}

	// Write output Node in format: "((%f, %f, %f))"
	std::ostream& operator<<( std::ostream& output, Node P) {

		char gr = ' ';
		if ( P.isGrounded)
		{
			gr = '+';
		}

		output << "(" << P.x << P.v << ")" << gr;

		return output;
	}
}