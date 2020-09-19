#pragma once

#ifndef INIWRITER_H
#define INIWRITER_H

#include <iostream>
#include <Windows.h> 

class CIniWriter
{
public:
	CIniWriter(const char* szFileName); 
	void WriteInteger(const char* szSection, const char* szKey, int iValue);
	void WriteFloat(const char* szSection, const  char* szKey, float fltValue);
	void WriteBoolean(const char* szSection, const char* szKey, bool bolValue);
	void WriteString(const char* szSection, const char* szKey, char* szValue);
private:
	char m_szFileName[255];
};
#endif //INIWRITER_H