#include "stdafx.h"
#include "TpUtils.h"


void setbintf(bool b)
{
	binary = b;
}

void fillVector(double ** data, int i, int j, const TPoint & vec)
{
	data[i][j] = vec.x;
	data[++i][j] = vec.y;
	data[++i][j] = vec.z;
}

static int TECINI_t(const char* plName, const char* vars, const char* fName, const char* path, int *a, int *b)
{

#if HAVE_LIBTECIO
#ifdef OLD_TECIO // для старых версий - отсутствует поддержка времени.
	if(binary)return TECINI((char*)plName,(char*)vars,(char*)fName,(char*)path,a,b);

#else
	int FileType= 0;

	if(binary)return TECINI111((char*)plName,(char*)vars,(char*)fName,(char*)path,&FileType,a,b);

#endif
#endif
	datFile = fopen (fName, "w");
	fprintf(datFile, "TITLE=\"%s\"\n",plName);
	fprintf(datFile, "VARIABLES=%s\n",vars);
	return 1;

}

int TECZNE_t(const char *name, int* sizeI, int* sizeJ, int* sizeK, double SolTime, int StrandID, const void * b )
{

#if HAVE_LIBTECIO
#ifdef OLD_TECIO
	if(binary)
		return TECZNE((char*)name,sizeI,sizeJ,sizeK,(char *)"BLOCK",(char *)b);
#else
	int ZoneType=0;
	//0=ORDERED
	int icm=0,jcm=0,kcm=0,parent=0,IsBlock=1,NFConns=0,FNMode=0,NumFaceNodes=1,NumBFaces=1,NumBConnections=1;

	int ShrConn=0;

	if (binary)
		return TECZNE111((char*)name,&ZoneType,sizeI,sizeJ,sizeK,&icm,&jcm,&kcm,
		&SolTime,
		&StrandID,&parent,&IsBlock,
		&NFConns,&FNMode,&NumFaceNodes,&NumBFaces,&NumBConnections,NULL,
		NULL,NULL,&ShrConn);


#endif
#endif
	fprintf (datFile, "ZONE T=\"%s\", STRANDID=%d, SOLUTIONTIME=%e\nI=%d, J=%d, K=%d, F=%s\n",name,StrandID,SolTime,*sizeI,*sizeJ,*sizeK,"BLOCK");
	return 1;


}


int TECDAT_t(int* /*size*/ tec_iii, double* tec_data, int *isDoub)
{

#if HAVE_LIBTECIO
#ifdef OLD_TECIO
	if(binary)return TECDAT(tec_iii,tec_data,isDoub);

#else
	if(binary){

		return TECDAT111(tec_iii,tec_data,isDoub);

	}

#endif
#endif
	for(int i = 0;i < *tec_iii; i++){

		fprintf(datFile,"%e\t",tec_data[i]);
		if((i+1)%5 == 0)
			fprintf(datFile,"\n");

	}

	fprintf(datFile,"\n");
	return 1;
}

void TECEND_t()
{

#if HAVE_LIBTECIO
#ifdef OLD_TECIO
	if(binary){
		TECEND();
		return;

	}

#else
	if(binary){
		TECEND111();
		return;

	}

#endif
#endif
	fclose(datFile);
}

namespace EnvelopeCore{
	// запись временного слоя
	// t -время
	// dt - шаг вывода (для вычисления id=(int)(t/dt)+1;)
	void  outputModelToTecplot(const char * fname,   double t, double id, const Node ** nn, const int & n_phi, const int & n_zeta, bool outputLandscape, const double * x, const double * y, const double ** zz, const int & n_x, const int & n_y ) 
	{

		// массив данных
		double **tec_data = new double *[N_PAR];

		int isDebug = 0, isDoub = 1;

		int N_z1 = n_zeta + 1;

		int N_phi1 = n_phi + 1;

		int tec_iii = N_phi1 * N_z1;
		// размерность на 1ну переменную

		for (int i = 0; i < N_PAR; i++) 
			tec_data[i] = new double[tec_iii];

		char buff[64];


		sprintf_s(buff,"skirt_%f:",t);	

		// инициализация файла вывода
		// заголовок,список переменных,имя файла, путь, дебажный вывод текплотной записи, данные с двойной точностью
		TECINI_t(buff,
			"Xx Xy Xz Ux Uy Uz Vx Vy Vz F_gr_x F_gr_y F_gr_z F_st_x F_st_y F_st_z F_fl_x F_fl_y F_fl_z F_pr_x F_pr_y F_pr_z F_fr_x F_fr_y F_fr_z m S isG C_ver C_hor",
			fname,"./",&isDebug,&isDoub);

		int zdir = 1;

		// инициализация зоны
		// имя , iMx , jMx, kMx==1, Time, ID
		TECZNE_t(buff, &N_phi1, &N_z1, &zdir, t, id);

		// заполнения данных
		for (int j = 0 ; j < N_z1; j++ )
			for (int i = 0 ; i < N_phi1 ; i++) // n_phi + 1 для склейки
			{

				const Node & n_cur = nn[(i==n_phi)?0:i][j];

				int cInd(j * N_phi1 + i);

				fillVector(tec_data, 0, cInd, n_cur.x);
				fillVector(tec_data, 3, cInd, n_cur.u);
				fillVector(tec_data, 6, cInd, n_cur.v);

				fillVector(tec_data, 9 + 3 * FORCE_GR_INDEX, cInd, n_cur.F[FORCE_GR_INDEX] );
				fillVector(tec_data, 9 + 3 * FORCE_ST_INDEX, cInd, n_cur.F[FORCE_ST_INDEX] );
				fillVector(tec_data, 9 + 3 * FORCE_FL_INDEX, cInd, n_cur.F[FORCE_FL_INDEX] );
				fillVector(tec_data, 9 + 3 * FORCE_PR_INDEX, cInd, n_cur.F[FORCE_PR_INDEX] );
				fillVector(tec_data, 9 + 3 * FORCE_FR_INDEX, cInd, n_cur.F[FORCE_FR_INDEX] );

				tec_data[24][cInd] = n_cur.m;
				tec_data[25][cInd] = n_cur.S;
				tec_data[26][cInd] = (double)n_cur.isGrounded;
				tec_data[27][cInd] = n_cur.C_ver;
				tec_data[28][cInd] = n_cur.C_hor;
			}

			// вывод данных для зоны
			for (int i = 0; i < N_PAR; i++)
				TECDAT_t (&tec_iii, &(tec_data[i][0]), &isDoub);

			for (int i = 0; i < N_PAR; i++) 
				delete [] tec_data[i];

			// выводим землю с тем же id (для временной анимации)
			if (outputLandscape)
			{
				outputLandscapeToTecplot(t, id, x, y, zz, n_x, n_y);
			}


			// закрытие файла
			TECEND_t();

			delete [] tec_data;
	}


	// внутренняя функция - запись земли, аналогично предыдущей только без открытия закрытия
	void outputLandscapeToTecplot(double t, int id, const double * x, const double * y, const double ** zz, const int & n_x, const int & n_y ) 
	{
		int N_x = n_x;
		int N_y = n_y;

		double **tec_data = new double *[N_PAR];

		int isDeb = 0, isDoub = 1;

		int tec_iii = N_x * N_y;

		for (int i = 0; i < N_PAR; i++) 
			tec_data[i] = new double[N_x * N_y];

		int zdir = 1;

		TECZNE_t("Land", &N_x, &N_y, &zdir, t, id);

		for(int j = 0; j < N_y; j++)
			for(int i = 0; i < N_x; i++)
			{

				int cInd(j * N_x + i);

				tec_data[0][cInd] = x[i];

				tec_data[1][cInd] = y[j];

				tec_data[2][cInd] = zz[i][j];

				for (int k = 3 ; k < N_PAR; k++)
				{
					tec_data[k][cInd] = 0;
				}
			}


			for (int i = 0; i < N_PAR; i++)
				TECDAT_t (&tec_iii, &(tec_data[i][0]), &isDoub);

			for (int i = 0; i < N_PAR; i++)
				delete[]tec_data[i];

			delete [] tec_data;
	}
}