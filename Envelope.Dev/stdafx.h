// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define DllImport   __declspec( dllimport )
#define DllExport   __declspec( dllexport )


#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <math.h>
#include <time.h>

#include "Envelope.Core.h"

using namespace std;
using namespace EnvelopeMath;
using namespace EnvelopeCore;


static void outputSummary(ModelProvider * sender, Summary &s);




// TODO: reference additional headers your program requires here
