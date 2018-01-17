#ifndef _FACTORIZATION
#define _FACTORIZATION
#include<cstdint>
#include<set>
#include<fstream>
#include<string>
#include"Exceptions.h"
class Factorization {
private:
	uint64_t Number;
	std::set<std::uint64_t> SetOfMultipliers;
public:
	Factorization() = default;
	~Factorization() = default;
	void GetFactorization(std::ofstream &) const;
	void FindFactorization(std::uint64_t, std::uint64_t);
	void SetData(std::uint64_t);
	uint64_t BackFactorization();
	void FreeMemory();
};
#endif // !_FACTORIZATION