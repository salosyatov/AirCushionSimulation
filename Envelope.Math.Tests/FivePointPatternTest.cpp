#include "stdafx.h"

using namespace System;
using namespace System::Text;
using namespace System::Collections::Generic;
using namespace	Microsoft::VisualStudio::TestTools::UnitTesting;

namespace EnvelopeMathTests
{
	[TestClass]
	public ref class FivePointPatternTest
	{
	public: 
		[TestMethod]
		void flatTorqueForce()
		{
			TPoint cur(0, 0, 0), l(-1. , 0, 0), r(2, 0, 0), b (0, 0, -2.), t(0., 0., 1.);
			FivePointPattern pattern(cur, l, r, b, t);

			//	TVector n;

			//	TVector f = pattern.GetTorqueForce(LEFT);
			//	bool actual = n == f; 
			Assert::AreEqual(0.0, pattern.GetTorqueForce(LEFT).len2(), "LEFT");
			Assert::AreEqual(0.0, pattern.GetTorqueForce(RIGHT).len2(), "RIGHT");
			Assert::AreEqual(0.0, pattern.GetTorqueForce(BOTTOM).len2(), "BOTTOM");
			Assert::AreEqual(0.0, pattern.GetTorqueForce(TOP).len2(), "TOP");

		}

	
	};
}
