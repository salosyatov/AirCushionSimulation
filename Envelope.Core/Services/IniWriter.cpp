#include "stdafx.h"
#include "IniWriter.h"

CIniWriter::CIniWriter(const char* szFileName)
{
	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));
}
void CIniWriter::WriteInteger(const char* szSection, const char* szKey, int iValue)
{
	char szValue[255];
	sprintf_s(szValue, "%d", iValue);
	WritePrivateProfileString((LPCWSTR)szSection,  (LPCWSTR)szKey, (LPCWSTR)szValue, (LPCWSTR)m_szFileName); 
}
void CIniWriter::WriteFloat(const char* szSection, const char* szKey, float fltValue)
{
	char szValue[255];
	sprintf_s(szValue, "%f", fltValue);
	WritePrivateProfileString((LPCWSTR)szSection,  (LPCWSTR)szKey, (LPCWSTR)szValue, (LPCWSTR)m_szFileName); 
}
void CIniWriter::WriteBoolean(const char* szSection, const char* szKey, bool bolValue)
{
	char szValue[255];
	sprintf_s(szValue, "%s", bolValue ? "True" : "False");
	WritePrivateProfileString((LPCWSTR)szSection,  (LPCWSTR)szKey, (LPCWSTR)szValue, (LPCWSTR)m_szFileName); 
}
void CIniWriter::WriteString(const char* szSection, const char* szKey, char* szValue)
{
	WritePrivateProfileString((LPCWSTR)szSection,  (LPCWSTR)szKey, (LPCWSTR)szValue, (LPCWSTR)m_szFileName);
}