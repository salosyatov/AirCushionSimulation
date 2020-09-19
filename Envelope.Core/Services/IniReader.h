#pragma once

#ifndef INIREADER_H
#define INIREADER_H

#include <iostream>
#include <Windows.h>

class CIniReader
{
public:
	CIniReader(const char* szFileName); 
	int ReadInteger(const char* szSection, const char* szKey, int iDefaultValue = 0);
	float ReadFloat(const char* szSection,const  char* szKey, float fltDefaultValue = 0.0);
	bool ReadBoolean(const char* szSection, const char* szKey, bool bolDefaultValue = false);
	char* ReadString(const char* szSection, const char* szKey, const char* szDefaultValue = "");
private:
	char m_szFileName[255];
};
#endif
//INIREADER_H