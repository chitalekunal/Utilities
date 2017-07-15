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
		std::string fileContents((std::istreambuf_iterator<char>(file)), (std::istreambuf_iterator<char>()));
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
	char open = control, close;
	if (open == '(') close = (char)((int)open + 1);
	else close = (char)((int)open + 2);

	for (i = 0; i <= data.length(); i++) {
		if (data[i] == open) {
			bracket_counter++;
			starter = true;
		}
		else if (data[i] == close) bracket_counter--;

		string_length_counter++;
		if (starter && bracket_counter == 0) break;
	}

	*pos = 1;
	*(pos + 1) = (int)data.find(control);
	*(pos + 2) = string_length_counter;

}

bool Utilities::is_number(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

char Utilities::GetFirstNonWhiteSpaceChar(std::string JSON) {
	for (int i = 0; i < JSON.length(); i++) {
		if (JSON[i] != ' ' && JSON[i] != '\n' && JSON[i] != '\t') return JSON[i];
	}
	return -1;
}

std::vector<std::string> Utilities::Vectorize(std::string buff, char *control) {
	std::vector<std::string> v;
	std::string buffer;
	int i = 0, pos[3];

	while (buff.length() > i && GetFirstNonWhiteSpaceChar(buff) != -1) {
		if (buff[i] == '"' && buff[i-1] != '\\') {
			int strt = buff.find('"',i);
			int end = buff.find('"', strt + 1);
			buffer += buff.substr(strt, end - strt+1);
			i += end - strt +1;
		}
		else if (buff[i] == '{' && buff[i - 1] != '\\') {
			GetSyntacticalPos(buff.substr(i),'{',pos);
			buffer += buff.substr(pos[1] + i, pos[2]);
			i += pos[2];
		}
		else if (buff[i] == '[' && buff[i - 1] != '\\') {
			GetSyntacticalPos(buff.substr(i), '[', pos);
			buffer += buff.substr(pos[1]+i,pos[2]);
			i += pos[2];
		}

		if (buff[i] == ',' && buff[i - 1] != '\\') {
			v.push_back(buffer);
			buffer.clear();
		}
		else if (buff[i] == ':' && buff[i -1] != '\\') {
			buffer += ':';
		}
		i++;
	}
	v.push_back(buffer);
	buffer.clear();
	return v;
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