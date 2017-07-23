#pragma once
#ifdef UTILITIES_EXPORTS
#define UTILITIES_LIBRARY_API __declspec(dllexport)
#else
#define UTILITIES_LIBRARY_API __declspec(dllimport)
#endif // UTILITIES_EXPORT



#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <cstdio>
#include <cctype>

class Utilities
{
#define ALFANUM "abcdefghijklmnopqrstuvwxyz1234567890"
#define NONALFANUM "\t\n\ "
#define CHARCTERS "abcdefghijklmnopqrstuvwxyz"
#define NUMBERS "1234567890"
public:
	// return code 1: incorrect character encoutered
	int ERRNOUTILITIES;
	UTILITIES_LIBRARY_API void Erase(std::string &str, char *cntrl_char);
	UTILITIES_LIBRARY_API std::ifstream OpenFileStream(std::string filename);
	UTILITIES_LIBRARY_API std::string OpenAndReadFileAndClose(std::string filename);
	UTILITIES_LIBRARY_API std::vector<std::string> split(std::string data, char delim);
	UTILITIES_LIBRARY_API int Contains(std::string data, char * chars);
	UTILITIES_LIBRARY_API void CloseFile(std::ifstream filename);
	UTILITIES_LIBRARY_API void GetSyntacticalPos(std::string data,char control, int *pos);
	UTILITIES_LIBRARY_API bool is_number(const std::string & s);
	UTILITIES_LIBRARY_API char GetFirstNonWhiteSpaceChar(std::string JSON);
	UTILITIES_LIBRARY_API bool ContainsOnlyWhitespace(std::string JSON);
	UTILITIES_LIBRARY_API float getNumber(std::string buff);
	UTILITIES_LIBRARY_API bool is_bool(std::string buff);
	UTILITIES_LIBRARY_API bool is_null(std::string buff);
};
