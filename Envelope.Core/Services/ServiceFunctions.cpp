#define STYLE 1
#if STYLE
	#include<cmath>
	#include<cstdlib>
	#include<new>

	#include<iostream>
	#include<fstream>
	#include<iomanip>
	#include <algorithm>

	using namespace std;

#else
	#include<math.h>
	#include<stdlib.h>
	#include<new.h>

	#include<iostream.h>
	#include<fstream.h>
	#include<iomanip.h>
#endif

#include "ServiceFunctions.h"

//---------------------------------------------------------------------------

// ”ункции для считывания и записи одномерных из/в файлы

void ReadArrFromFile(ifstream &in, const int &n, double *&Array)
{
	for(int i=0; i<n; i++)
		in.read((char*)(&Array[i]),sizeof(double));
}

void WriteArrToFile(ofstream &out, const int &n, double *&Array)
{
	for(int i=0; i<n; i++)
		out.write((char*)(&Array[i]),sizeof(double));
}

//---------------------------------------------------------------------------

// ”ункции для считывания и записи двумерных массивов из/в файлы

void ReadArrFromFile(ifstream &in, const int &n, const int &m, double **&Array)
{
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			in.read((char*)(&Array[i][j]),sizeof(double));

}

void WriteArrToFile(ofstream &out, const int &n, const int &m, double **&Array)
{
	for(int i=0; i<n; i++)
		for(int j=0; j<m; j++)
			out.write((char*)(&Array[i][j]),sizeof(double));
}

//---------------------------------------------------------------------------


