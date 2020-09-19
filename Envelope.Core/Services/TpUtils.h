#pragma once

#define HAVE_LIBTECIO 1  // ����� � �������� ����
#define N_PAR 29 // ���������� ���������� ����, �������������� � �������-����

#include "stdafx.h"
#include "Node.h"
#include <stdexcept>


#if HAVE_LIBTECIO // ���������� ��� ������ � �������� �������
#include "TECIO.h"
static bool binary = true;
//����� � �������� �������
#else
static bool binary = false;

#endif


void setbintf(bool b);
void fillVector(double ** tec_data, int i, int j, const TPoint & vec);

static FILE *datFile;
// ��� ���������� ������
static int TECINI_t(const char* plName, const char* vars, const char* fName, const char* path, int *a, int *b);

int TECZNE_t(const char *name, int* sizeI, int* sizeJ, int* sizeK, double SolTime, int StrandID, const void * b = NULL);

int TECDAT_t(int* /*size*/ tec_iii, double* tec_data, int *isDoub);

void TECEND_t();

namespace EnvelopeCore{

void  outputModelToTecplot(const char * fname,   double t, double id, const Node ** nn, const int & n_phi, const int & n_zeta, bool outputLandscapeToTecplot, const double * x, const double * y, const double ** zz, const int & n_x, const int & n_y ) ;

// ���������� ������� - ������ �����, ���������� ���������� ������ ��� �������� ��������
void outputLandscapeToTecplot(double t, int id, const double * x, const double * y, const double ** zz, const int & N_x, const int & N_y ) ;

}
