#pragma once
#include "Node.h"
#include "SkirtData.h"

namespace EnvelopeCore {
	void inputFromFile(SkirtData * skirtData, const int & cycleNumber, double &t);

	void outputFromFile(SkirtData * skirtData, const int & cycleNumber, const double &t);

}