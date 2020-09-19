//---------------------------------------------------------------------------

#ifndef MemoryUtilsH
#define MemoryUtilsH

#include <ostream>
//---------------------------------------------------------------------------

// Функция для выделения и освобождения памяти для ОДНОМЕРНЫХ массивов
template <class FictType>
FictType* Allocate(FictType* a, const int &n )
{
	try
	{
		a = new FictType[n];
	}
	catch(std::bad_alloc)
	{

		std::cerr << "Out of memory" << std::endl;
		return NULL;
	}

	return a;
}
//-------------------------------------------------------------------

// Функция для выделения и заполнения  памяти для ОДНОМЕРНЫХ массивов
template <class FictType>
FictType* AllocateFillingByValue(FictType* a, const int &n , FictType Value = 0)
{
	try
	{
		a = new FictType[n];
		for(int i = 0; i < n; i++)
			a[i] = Value;			
	}
	catch(bad_alloc)
	{

		cerr << "Out of memory" << endl;
		return NULL;
	}

	return a;
}
//-------------------------------------------------------------------

// Функция для освобождения памяти для ОДНОМЕРНЫХ массивов
template <class FictType>
int DeAllocate(FictType* a, const int &n)
{
	if (a) delete a;

	return 0;
}
//-------------------------------------------------------------------

// Функция для выделения  памяти для ДВУМЕРНЫХ массивов
template <class FictType>
FictType** Allocate(FictType** a, const int &n , const int &m)
{
	try
	{
		FictType** a = new FictType*[n];
		for (int i = 0; i < n; i++)
		{
			a[i] = new FictType[m];
		}

		return a;
	}
	catch(std::bad_alloc)
	{
		std::cerr << "Out of memory" << std::endl;
		return NULL;
	}

}
//-------------------------------------------------------------------
// Функция для выделения и заполнения памяти для ДВУМЕРНЫХ массивов
template <class FictType>
FictType** AllocateFillingByValue(FictType** a, const int &n , const int &m, FictType Value = 0)
{
	try
	{
		FictType** a = new FictType*[n];
		for (int i = 0; i < n; i++)
		{
			a[i] = new FictType[m];
		}

		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				a[i][j] = Value;

		return a;
	}
	catch(bad_alloc)
	{
		cerr << "Out of memory" << endl;
		return NULL;
	}

}
//-------------------------------------------------------------------

//-----------------------------------------------------------------------------
// Функция для  освобождения памяти для ДВУМЕРНЫХ массивов
template <class FictType>
int DeAllocate(FictType** a, const int &n, const int &m)
{
	if (a)
	{
		for(int i = 0; i < n; i++)
			if (a[i]) delete [] a[i];

		delete a;
	}

	return 0;
}
//-------------------------------------------------------------------


// Функция для выделения и освобождения памяти для ТРЕХМЕРНЫХ массивов
template <class FictType>
FictType*** Allocate(FictType*** a,const int &n, const int &m, const int &l)
{
	try
	{
		FictType ***a = new FictType **[n];
		for(int i = 0; i < n; i++)
			a[i] = new FictType *[m];

		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				a[i][j] = new FictType [l];

		return a;
	}
	catch(bad_alloc)
	{
		cerr << "Out of memory" << endl;
		return NULL;
	}
}

//---------------------------------------------------------------------------
// Функция для выделения и заполнения памяти для ТРЕХМЕРНЫХ массивов
template <class FictType>
FictType*** AllocateFillingByValue(FictType*** a,const int &n, const int &m, const int &l, FictType Value = 0)
{
	try
	{
		FictType ***a = new FictType **[n];

		for(int i = 0; i < n; i++)
			a[i] = new FictType *[m];

		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				a[i][j] = new FictType [l];

		for(int i = 0; i < n; i++)
			for(int j = 0; j < m; j++)
				for(int k = 0; k < l; k++)
					a[i][j][k] = 0.0;

		return a;
	}
	catch(bad_alloc)
	{
		cerr << "Out of memory" << endl;
		return NULL;
	}
}
//---------------------------------------------------------------------------
// Функции для  освобождения памяти для ТРЕХМЕРНЫХ массивов
template <class FictType>
int DeAllocate(FictType ***a, const int &n, const int &m, const int &l)
{
	for(int i = 0; i < n; i++)
		for(int j = 0; j < m; j++)
			if (a[i][j]) delete [] a[i][j];

	for(int i = 0; i < n; i++)
		if (a[i]) delete [] a[i];

	if (a) delete [] a;

	return 0;
}

//---------------------------------------------------------------------------

#endif