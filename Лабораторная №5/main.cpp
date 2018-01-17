#include "Factorization.h"

int main(int argc, char* argv[]) {
	try { if (argc != 3) throw new error_arguments(); }
	catch (error_arguments *e) { std::cout << e->what(); return 1; };
	Factorization f(argv[1], argv[2]);
	std::string line;
	if (std::getline(std::cin, line) && line == "exit") {
		f.stop();
		return 0;
	}
	f.stop();
	return 0;
}
