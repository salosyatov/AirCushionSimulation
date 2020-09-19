#ifndef ServiceFunctions_H
#define ServiceFunctions_H

    #include<fstream>
    using namespace std;



	void ReadArrFromFile(ifstream &in, const int &n, double *&Array);
	void WriteArrToFile(ofstream &out, const int &n, double *&Array);

	void ReadArrFromFile(ifstream &in, const int &n, const int &m, double **&Array);
	void WriteArrToFile(ofstream &out, const int &n, const int &m, double **&Array);

 

#endif //ServiceFunctions_H
