#pragma once

namespace EnvelopeCore {
	/**
	* @class	Parameters
	*
	* @brief	Параметры системы, необходимые для моделирования.
	*
	* @author	Vasiliy
	* @date	18.10.2012
	*/

	class DllExport Parameters
	{
	public:
		Parameters(void);
		virtual ~Parameters(void);

		/**
		* @fn	bool virtual Parameters::Read(char * fileName ) = 0;
		*
		* @brief	Reads the given file.
		*
		* @author	Vasiliy
		* @date	18.10.2012
		*
		* @param [in,out]	fileName	If non-null, the file name to read.
		*
		* @return	true if it succeeds, false if it fails.
		*/

		bool virtual Read(const char * fileName, const char * section ) = 0;

		/**
		* @fn	bool virtual Parameters::Save(char * fileName ) = 0;
		*
		* @brief	Saves the given file.
		*
		* @author	Vasiliy
		* @date	18.10.2012
		*
		* @param [in,out]	fileName	If non-null, the file name to save.
		*
		* @return	true if it succeeds, false if it fails.
		*/

		bool virtual Save(const char * fileName, const char * section ) const = 0;
	};
}