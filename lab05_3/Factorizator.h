#ifndef _FACTORIZATOR
#define _FACTORIZATOR
#include<cstdint>
#include<vector>
#include<fstream>
#include<string>
#include<thread>
#include<iostream>
#include<thread>
#include<mutex>
#include<condition_variable>
#include"exceptions.h"


class Factorizator {
private:
	
public:
	void factorize(std::vector<std::uint64_t> &SetOfMultipliers, uint64_t number);
	uint64_t BackFactorizaton(std::vector<std::uint64_t> SetOfMultipliers) const;
	
};
#endif // !_FACTORIZATOR