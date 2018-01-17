#include "Factorization.h"
#include<iostream>
int main(int argc, char* argv[]) {
	try {if (argc != 3) throw new error_arguments();}
	catch (error_arguments *e) { std::cout << e->what(); return 1; };

	std::ifstream in(argv[1], std::ios_base::in);
	std::ofstream out(argv[2]);

	Factorization f;
	uint64_t cur_num;
	try { if (!in) throw new error_file(); }
	catch (error_file *e) { std::cout << e->what(); return 1; };
	while (in >> cur_num) {
		f.SetData(cur_num);
		f.GetFactorization(out);
		f.FreeMemory();
	}
	std::cout << "\nFinished!";
	in.close();
	out.close();
	return 0;
}