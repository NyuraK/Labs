#ifndef _FACTORIZATION
#define _FACTORIZATION
#include<cstdint>
#include<vector>
#include<fstream>
#include<string>
#include<thread>
#include<iostream>
#include<thread>
#include"Exceptions.h"
class Factorization {
private:
	std::thread thr;
	uint64_t Number;
	std::vector<std::uint64_t> SetOfMultipliers;
	std::string inputfile, outputfile;
	bool running = false;

	void start();
	void loop() throw (error_file);
	void GetFactorization(std::ofstream &) const;
	void factorize(uint64_t n, uint64_t unused);
	uint64_t BackFactorization() const;
	void FreeMemory();
public:
	Factorization(char*, char*);
	~Factorization();
	void stop();
};
#endif // !_FACTORIZATION