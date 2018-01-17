#include "parser.h"

/*Procedure for 1st*/
void read_ini_file(string file_name, vector<pair<string, string>> &sections) {
	ifstream file(file_name, ios_base::in);
	if (!file) cout << "didn't open";
	string str, param, val;

	while (getline(file, str)) {

		if (str.find('[') != string::npos && str.find(';') == string::npos) {
			//cout << "Section has been founded: " << str.substr(1, str.find(']')-1) << endl;
			sections.push_back(make_pair("[]", str.substr(1, str.find(']') - 1)));

		}

		if (str.find('=') != string::npos && str.find('=') < str.find(';')) {
			/*//deleting spaces
			str.erase(remove(str.begin(), str.end(), ' '), str.end()); //http://ru.cppreference.com/w/cpp/algorithm/remove
			if (str.find(';') != string::npos) {
				str = str.substr(0, str.find(';'));
			}
			cout << "New parametr founded: " << str << endl;*/
			//deleting spaces
			str.erase(remove(str.begin(), str.end(), ' '), str.end());

			param = str.substr(0, str.find('=') - 1);
			val = str.substr(str.find('=') + 1, str.find(';') - str.find('=') - 1);
			sections.push_back(make_pair(param, val));
		}
	}
	file.close();
}

void IniParser::Initialize(const char * filename_cstr) {
	ifstream file(filename_cstr, ios_base::in);

	if (string(filename_cstr).find(".ini") == string::npos) throw new error_format();
	if (!file) throw new error_file();
	string str, param, val;

	while (getline(file, str)) {
		if (str.find('[') != string::npos && str.find(';') == string::npos) {
			sections.push_back(make_pair("[]", str.substr(1, str.find(']') - 1)));
		}

		if (str.find('=') != string::npos && str.find('=') < str.find(';')) {
			//deleting spaces
			str.erase(remove(str.begin(), str.end(), ' '), str.end());

			param = str.substr(0, str.find('='));
			val = str.substr(str.find('=') + 1, str.find(';') - str.find('=') - 1);
			sections.push_back(make_pair(param, val));
		}
	}
	file.close();
}

int IniParser::IsHaveSection(const char * section_name) const {
	
	vector <pair<string, string>> ::const_iterator itr;
	int i = 0;
	for (itr = sections.begin(); itr != sections.end(); ++itr) {
		if (itr->first == "[]" && itr->second == section_name)
			return i;
		i++;
	}
	return -1;
}

bool IniParser::IsHaveParam(const char * section_name, const char * param_name) const {
	vector <pair<string, string>> ::const_iterator itr;
	int i = IsHaveSection(section_name);
	if (i != -1) {
		for (itr = sections.begin() + i; itr != sections.end(); ++itr) {
			if (itr->first == param_name)
				return true;
		}
		return false;
	}

}

void IniParser::ShowData() const{
	if (sections.empty()) cout << "No data\n";
	vector <pair<string, string>>::const_iterator itr;
	for (itr = sections.begin(); itr != sections.end(); ++itr) {
		if (itr->first == "[]")
			cout << itr->second << endl;
		else cout << itr->first << " = " << itr->second << '\n';
	}
}

template<>
int IniParser::get_value(const char* section_name, const char* param_name)
{
	if (!this->IsHaveParam(section_name, param_name)) throw new error_no_param();
	else if (string(this->Search(section_name, param_name)).empty()) throw new error_not_initialized();
	return atoi(this->Search(section_name, param_name));
}
template<>
double IniParser::get_value(const char* section_name, const char* param_name)
{
	if (!this->IsHaveParam(section_name, param_name)) throw new error_no_param();
	else if (string(this->Search(section_name, param_name)).empty()) throw new error_not_initialized();
	return atof(this->Search(section_name, param_name));
}
template<>
string IniParser::get_value(const char* section_name, const char* param_name)
{
	if (!this->IsHaveParam(section_name, param_name)) throw new error_no_param();
	else if (string(this->Search(section_name, param_name)).empty()) throw new error_not_initialized();
	return string(this->Search(section_name, param_name));
}
void IniParser::del()
{
	this->~IniParser();
}

void menu::ShowMenu(IniParser e) {
	cout << "1. Show data\n2. Get value int value\n3. Get float value\n4. Get string value\n5. Delete\n6. Close program\n";
	int choice, i_value;
	string sec, param, s_value;
	double d_value;
	cin >> choice;
	do {
		switch (choice)
		{
		case 1:
			e.ShowData();
			break;
		case 2:
			cout << "Put the name of section and parametr\n";
			cin >> sec >> param;
			try {
				 i_value = e.get_value<int>(sec.c_str(), param.c_str());
				 cout << i_value << endl;
			}
			catch (error_no_param *e) {
				cout << e->what() << endl;
			}
			catch (error_not_initialized *e) {
				cout << e->what() << endl;
			}
			break;
		case 3:
			cout << "Put the name of section and parametr\n";
			cin >> sec >> param;
			try {
				d_value = e.get_value<double>(sec.c_str(), param.c_str());
				cout << d_value << endl;
			}
			catch (error_no_param *e) {
				cout << e->what() << endl;
			}
			catch (error_not_initialized *e) {
				cout << e->what() << endl;
			}
			break;
		case 4:
			cout << "Put the name of section and parametr\n";
			cin >> sec >> param;
			try {
				s_value = e.get_value<string>(sec.c_str(), param.c_str());
				cout << s_value << endl;
			}
			catch (error_no_param *e) {
				cout << e->what() << endl;
			}
			catch (error_not_initialized *e) {
				cout << e->what() << endl;
			}
			break;
		case 5:
			e.del();
			break;
		case 6:
			break;
		}
		cout << "1. Show data\n2. Get value int value\n3. Get float value\n4. Get string value\n5. Delete\n6. Close program\n";
		cin >> choice;
	} while (choice != 6);
}