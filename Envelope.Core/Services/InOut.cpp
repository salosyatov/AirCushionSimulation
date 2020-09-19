#include "stdafx.h"
#include "InOut.h"

namespace EnvelopeCore {

	void inputFromFile(SkirtData * skirtData, const int & cycleNumber, double &t)
	{
		char FileName[255];

		sprintf(FileName, "Data%04i.inf", cycleNumber);

		ifstream file_in;

		file_in.open(FileName, ios::in|ios::binary);

		if(!file_in)
		{
			char message[255];
			sprintf(message, "Open File Error - File %s is absent", FileName);
			throw exception(message);
		}

		double n_phi, n_zeta;

		file_in.read((char*)(&t),sizeof(double));
		file_in.read((char*)(&n_phi),sizeof(int));
		file_in.read((char*)(&n_zeta),sizeof(int));

		for (int i = 0 ; i < n_phi; i++)
			for (int j = 0 ; j < n_zeta + 1; j++ )
			{

				Node & n_cur = skirtData->GetNN()[i][j];

				file_in >> n_cur;

			}

			file_in.close();
	}

	void outputFromFile(SkirtData * skirtData, const int & cycleNumber, const double &t)
	{
		char FileName[255];

		sprintf(FileName, "Data%04i.inf", cycleNumber);


		ofstream file_out(FileName, ios::out|ios::binary);


		if(!file_out)
		{
			char message[255];
			sprintf(message, "Creation File Error - File %s hasn't been created", FileName);
			throw exception(message);
		}

		file_out.write((char*)(&t),sizeof(double));

		double n_phi, n_zeta;
		n_phi  = skirtData->GetCalculationParameters().GetNPhi();
		n_zeta = skirtData->GetCalculationParameters().GetNZeta();

		file_out.write((char*)(&n_phi),sizeof(int));
		file_out.write((char*)(&n_zeta),sizeof(int));

		for (int i = 0 ; i < n_phi; i++)
			for (int j = 0 ; j < n_zeta + 1; j++ )
			{

				const Node & n_cur =  skirtData->GetNN()[i][j];

				file_out << n_cur;

			}

			file_out.close();

	}
}