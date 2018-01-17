#pragma once
#ifndef _parser
#define _parser
#include<string>
#include<algorithm>
#include<vector>
#include<iterator>
#include<iostream>
#include<fstream>>
#include"exceptions.h"

using namespace std;

class IniParser {
private:
	vector<pair<string, string>> sections;
public:     
	IniParser() = default;   

	~IniParser() = default;

	void Initialize(const char* filename_cstr) throw (error_file, error_format);

	int IsHaveSection(const char* section_name) const;

	bool IsHaveParam(const char* section_name, const char* param_name) const;

	void ShowData() const;

	void del();

	template<typename T> T Search(T section_name, T param_name);

	template<typename T> T get_value(const char* section_name, const char* param_name) throw (error_no_param, error_not_initialized);

}; 


class menu {
public:
	void ShowMenu(IniParser e);
};

void read_ini_file(string, vector<pair<string, string>> &);
#endif // !_parser

template<typename T>
inline T IniParser::Search(T section_name, T param_name)
{
	vector <pair<string, string>> ::const_iterator itr;
	int i = this->IsHaveSection(section_name);
	for (itr = this->sections.begin() + i; itr != this->sections.end(); ++itr)
		if (itr->first == param_name)
			return itr->second.c_str();
}
