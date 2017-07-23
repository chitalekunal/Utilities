// Utilities.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Utilities.h"

void Utilities::Erase(std::string &str, char *cntrl_char) {
	for (int i = 0; i < strlen(cntrl_char); i++) {
		str.erase( std::remove(str.begin(), str.end(), cntrl_char[i]), str.end());
	}
}

std::ifstream Utilities::OpenFileStream(std::string filename) {

	//Opens a file and returns file stream name

	std::ifstream file(filename.c_str());

	if (file) {
		return file;
	}
	else
	{
		printf("JSON file %s not found\nProcessing Aborted", filename.c_str());
		exit(1);
	}
}

std::string Utilities::OpenAndReadFileAndClose(std::string filename) {
	//Opens a file ,reads contents and closes the stream

	std::ifstream file(filename.c_str());


	if (file) {
		file.seekg(0, std::ios::end);
		int fileSize = file.tellg();
		file.seekg(0, std::ios::beg);
		char *buffer = new char[fileSize];

		file.read(buffer, fileSize);
		std::string fileContents(buffer);
		return fileContents;
		file.close();
	}
	else
	{
		printf("JSON file %s not found\nProcessing Aborted", filename.c_str());
		exit(1);
	}
}

std::vector<std::string> Utilities::split(std::string data, char delim) {
	std::vector<std::string> result;
	std::string buffer;
	std::istringstream iss(data);

	while (std::getline(iss, buffer, delim)) {
		result.push_back(buffer);
	}
	return result;
}

int Utilities::Contains(std::string data, char *chars) {
	int i = 0;
	for (i = 0; i < strlen(chars); i++) {
		if (data.find(chars[i]) != std::string::npos) return 1;
	}
	return 0;
}

void Utilities::CloseFile(std::ifstream filename) {
	filename.close();
}


void Utilities::GetSyntacticalPos(std::string data, char control, int *pos) {
	int bracket_counter = 0, string_length_counter = 0,i;
	bool starter = false;
	bool condition1, condition2;
	char open = control, close;
	if (open == '(') close = (char)((int)open + 1);
	else close = (char)((int)open + 2);

	for (i = 0; i <= data.length(); i++) {
		if ( i == 0 ){
			condition1 = (data[i] == open);
			condition2 = (data[i] == close);
		}
		else {
			condition1 = (data[i] == open && data[i-1] != '\\');
			condition2 = (data[i] == close && data[i - 1] != '\\');
		}

		if ( condition1 ) {
			bracket_counter++;
			starter = true;
		}
		else if ( condition2 )
			bracket_counter--;

		string_length_counter++;
		if (starter && bracket_counter == 0) break;
	}

	*pos = 1;
	*(pos + 1) = (int)data.find(control);
	*(pos + 2) = string_length_counter;

}

bool Utilities::is_number(const std::string& s)
{
	for (int i = 0; i < s.length(); i++) {
		if (s[i] >= '0' && s[i] <= '9') continue;
		return false;
	}
	return true;
}

char Utilities::GetFirstNonWhiteSpaceChar(std::string JSON) {
	for (int i = 0; i < JSON.length(); i++) {
		if (JSON[i] != ' ' && JSON[i] != '\n' && JSON[i] != '\t') return JSON[i];
	}
	return -1;
}

bool Utilities::ContainsOnlyWhitespace(std::string JSON)
{
	bool decision = false;
	for (int i = 0; i < JSON.length(); i++) {
		if (JSON[i] == ' ' || JSON[i] == '\n' || JSON[i] == '\t') {
			decision = true;
		}
		else {
			decision = false;
			break;
		}
	}
	return decision;
}

float Utilities::getNumber(std::string buff) {
	std::string number;

	for (int i = 0; i < buff.length(); i++) {
		if (GetFirstNonWhiteSpaceChar(buff.substr(i)) == ',' || GetFirstNonWhiteSpaceChar(buff.substr(i)) == ']' || GetFirstNonWhiteSpaceChar(buff.substr(i)) == '}') {
			ERRNOUTILITIES = 0;
			return atof(number.c_str()); 
		}
		else if (buff[i] <= '9' && buff[i] >= '0') { number += buff[i]; }
		else {
			ERRNOUTILITIES = 1;
			return NULL;
		}
	}
}

UTILITIES_LIBRARY_API bool Utilities::is_bool(std::string buff)
{
	int p1 = buff.find(',');
	std::string temp;
	if (p1 >-1) temp = buff.substr(0, p1);
	else temp = buff;
	Erase(temp,"\t\n ");
	if (temp == "true" || temp == "false")
		return true;
	return false;
}

UTILITIES_LIBRARY_API bool Utilities::is_null(std::string buff)
{
	int p1 = buff.find(',');
	std::string temp;
	if (p1 >-1) temp = buff.substr(0, p1);
	else temp = buff;
	Erase(temp, "\t\n ");
	if (temp == "null" )
		return true;
	return false;
}
