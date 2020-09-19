#include "stdafx.h"
#include "IniReader.h"

CIniReader::CIniReader(const char* szFileName)
{
	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));
}

int CIniReader::ReadInteger(const char* szSection, const char* szKey, int iDefaultValue)
{
	int iResult = GetPrivateProfileInt((LPCWSTR)szSection,  (LPCWSTR)szKey, iDefaultValue, (LPCWSTR)m_szFileName); 
	return iResult;
}
float CIniReader::ReadFloat(const char* szSection, const char* szKey, float fltDefaultValue)
{
	char szResult[255];
	char szDefault[255];
	float fltResult;
	sprintf_s(szDefault, "%f",fltDefaultValue);
	GetPrivateProfileString((LPCWSTR)szSection,  (LPCWSTR)szKey, (LPCWSTR)szDefault, (LPWSTR)szResult, 255, (LPCWSTR)m_szFileName); 
	fltResult =  atof(szResult);
	return fltResult;
}
bool CIniReader::ReadBoolean(const char* szSection, const char* szKey, bool bolDefaultValue)
{
	char szResult[255];
	char szDefault[255];
	bool bolResult;
	sprintf_s(szDefault, "%s", bolDefaultValue? "True" : "False");
	GetPrivateProfileString((LPCWSTR)szSection, (LPCWSTR)szKey, (LPCWSTR)szDefault, (LPWSTR)szResult, 255, (LPCWSTR)m_szFileName); 
	bolResult =  (strcmp(szResult, "True") == 0 || 
		strcmp(szResult, "true") == 0) ? true : false;
	return bolResult;
}
char* CIniReader::ReadString(const char* szSection, const char* szKey, const char* szDefaultValue)
{
	char* szResult = new char[255];
	memset(szResult, 0x00, 255);
	GetPrivateProfileString((LPCWSTR)szSection,  (LPCWSTR)szKey, 
		(LPCWSTR)szDefaultValue, (LPWSTR)szResult, 255, (LPCWSTR)m_szFileName); 
	return szResult;
}