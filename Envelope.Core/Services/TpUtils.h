#pragma once

#define HAVE_LIBTECIO 1  // Вывод в бинарном виде
#define N_PAR 29 // количество параметров узла, экспортируемых в текплот-файл

#include "stdafx.h"
#include "Node.h"
#include <stdexcept>


#if HAVE_LIBTECIO // Определить для вывода в бинарном формате
#include "TECIO.h"
static bool binary = true;
//Вывод в бинарном формате
#else
static bool binary = false;

#endif


void setbintf(bool b);
void fillVector(double ** tec_data, int i, int j, const TPoint & vec);

static FILE *datFile;
// для текстового вывода
static int TECINI_t(const char* plName, const char* vars, const char* fName, const char* path, int *a, int *b);

int TECZNE_t(const char *name, int* sizeI, int* sizeJ, int* sizeK, double SolTime, int StrandID, const void * b = NULL);

int TECDAT_t(int* /*size*/ tec_iii, double* tec_data, int *isDoub);

void TECEND_t();

namespace EnvelopeCore{

void  outputModelToTecplot(const char * fname,   double t, double id, const Node ** nn, const int & n_phi, const int & n_zeta, bool outputLandscapeToTecplot, const double * x, const double * y, const double ** zz, const int & n_x, const int & n_y ) ;

// внутренняя функция - запись земли, аналогично предыдущей только без открытия закрытия
void outputLandscapeToTecplot(double t, int id, const double * x, const double * y, const double ** zz, const int & N_x, const int & N_y ) ;

}
