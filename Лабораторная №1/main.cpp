#include"parser.h"

int main() {
	IniParser ex; 
	string name_of_file;
	bool is_open = false;

	while (!is_open) {
		cin >> name_of_file;
		try {
			ex.Initialize(name_of_file.c_str());
			is_open = true;
		}
		catch (error_file *e) {
			cout << e->what() << endl;
		}
		catch (error_format *e) {
			cout << e->what() << endl;
		}
	}

	menu m;
	m.ShowMenu(ex);
}