#include "stdafx.h"
#include "IDAUtils.h"



int check_flag(void *flagvalue, char *funcname, int opt)
{
	int *errflag;
	char mes[255];

	/* Check if SUNDIALS function returned NULL pointer - no memory allocated */
	if (opt == 0 && flagvalue == NULL) 
	{
		sprintf(mes, "\nSUNDIALS_ERROR: %s() failed - returned NULL pointer\n\n", 
			funcname);
		throw std::exception(mes);

	} else if (opt == 1) {
		/* Check if flag < 0 */
		errflag = (int *) flagvalue;
		if (*errflag < 0) 
		{
			sprintf(mes, "\nSUNDIALS_ERROR: %s() failed with flag = %d\n\n", 
				funcname, *errflag);
			throw std::exception(mes);
		}
	} 
	else
		if (opt == 2 && flagvalue == NULL) {
		/* Check if function returned NULL pointer - no memory allocated */
		sprintf(mes, "\nMEMORY_ERROR: %s() failed - returned NULL pointer\n\n", 
			funcname);
		throw std::exception(mes);
	}

	return(0);
}

int getOffset(int i, int j, int N_phi, int N_zeta)
{
	return ((i - SHIFT_LEFT) * (N_zeta + 1) + (j - SHIFT_BOTTOM)) * VARIABLE_COUNT;
}
